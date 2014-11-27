#define _BSD_SOURCE
#include "hashtable.h"
#include "queue.h"
#include "bookorder.h"
#include "extras.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Queue* threads;
Hashtable* orderQueues;
Hashtable* customers;
int flag_finished;

void* consumer(void* _vqueue){

	Queue* queue = (Queue*) _vqueue;
	int waited  =0;
	//printf("I am a thread\n");
	while(1){
		//pop order from queue
		void* _vorder = QPop(queue);
		//if order == null
		if(_vorder == NULL){
			if(flag_finished)
				break;
			if(!waited){
				printf("Consumer waiting. Queue Empty.\n");
				waited = 1;
			}
			usleep(1000);
			continue;
		}
		if(waited){
			printf("Consumer Continuing.\n");
			waited = 0;
		}
		//get customer
		Order* order = (Order*) _vorder;
		int* iptr = malloc(sizeof(int));
		*iptr = order->customer;
		Customer* customer = (Customer*) HTGet(customers,iptr);
		free(iptr);
		if(customer == NULL){
			usleep(1000);
			continue;
		}else if(customer->balance >= order->price){
			CustomerAddCompleted(customer, order);
		}else{
			CustomerAddFailed(customer, order);
		}
	}

	return NULL;
}

int main(int argc, char* argv[]){

		orderQueues = HTCreate(26,hashStr,FreeQueue,cmpKeyStr);
		customers = HTCreate(10,hashInt,FreeCustomer,cmpKeyInt);
		threads = QCreate(20);
		flag_finished = 0;
		
		//init objects
		//read in categories
		//	for each category 
		//		make a queue
		//		add queue to orderQueues
		//		create pthread_t thread
		//		pthread_create(thread, NULL, &consumer, queue
		//		add thread to threads

		static const char filename[] = "categories.txt";
		FILE *file = fopen ( filename, "r" );
		if ( file != NULL ){
			char buff[1000]; 
			char* categorie;
			while(fgets( buff, sizeof buff, file ) != NULL){
				//fputs (categorie, stdout );
				categorie = strtok(buff, "\r");
				char* key = malloc(sizeof(char) * strlen(categorie) + 1);
				memset(key, 0, sizeof(char) * (strlen(categorie) + 1));
				memcpy(key, categorie, sizeof(char) * strlen(categorie));
				Queue *q = QCreate(20);
				HTAdd(orderQueues, q , key);
				pthread_t* thread = malloc(sizeof(pthread_t));
				pthread_create(thread, NULL, &consumer, q);
				QPush(threads, thread);
			}
			fclose ( file );
		}else{
			perror ( filename ); 
		}
		//read in database
		//	for each customer
		//		make customer
		//		add customer to customers
		static const char filename1[] = "database.txt";
		FILE *fp = fopen ( filename1, "r" );
		if ( fp != NULL ){
			char database[1000]; 
			char s[2] = "|";
			char *token, *name, *address, *state, *zip;
			int i = 0;
			int* ptr;
			int id;
			double balance;
			Customer *cus;
			while(fgets( database, sizeof database, fp ) != NULL){
				token = strtok(database, s);
				while( token != NULL ){
					//printf( " %s\n", token );
					if(i == 0){
						name = token;
					}else if(i == 1){
						id = atoi(token);
						ptr = malloc(sizeof(int));
						*ptr = id;
					}else if(i == 2){
						balance = atof(token);
					}else if(i == 3){
						address = token;
					}else if(i == 4){
						state = token;
					}else if(i == 5){
						zip = token;
					}
					token = strtok(NULL, s);
					i++;
				}
				cus = CustomerCreate(id, balance, name, address, state, zip);
				HTAdd(customers,cus, ptr);
				i = 0;
			}
			fclose (fp);
		}else{
			perror (filename1); 
		}
		//read in book orders
		//	for each order
		//		make order
		//		get correct queue
		//		add order to queue
		static const char filename2[] = "orders.txt";
		FILE *fp1 = fopen ( filename2, "r" );
		if ( fp1 != NULL ){
			char orders[1000]; 
			char s[3] = "|\r\n";
			int i = 0; int id;
			double price;
			Order *order;
			void* value;
			char *token, *title, *categorie;
			while(fgets( orders, sizeof orders, fp1 ) != NULL){
				token = strtok(orders, s);
				while( token != NULL ){
					//printf( " %s\n", token );
					if(i == 0){
						title = token;
					}else if(i == 1){
						price = atof(token);
					}else if(i == 2){
						id = atoi(token);
					}else if(i == 3){
						categorie = token;
					}
					token = strtok(NULL, s);
					i++; 
				}
				i = 0;
				order = OrderCreate(title, price, id);
				value = HTGet(orderQueues, categorie);
				if(value != NULL){
					if(!QPush((Queue*) value, order)){
						printf("Producer waiting. A queue is full\n");
						while(!QPush((Queue*) value, order)){
							usleep(1000);
						}
						printf("Producer Continuing.\n");
					}
				}
			}
			fclose (fp1);
		}else{
			perror (filename2); 
		}
		//set finish flag
		//wait for queues
		//	pop thread in threads
		//		pthread_join(thread);		
		flag_finished = 1;
		pthread_t *thread = QPop(threads);
		
		while(thread != NULL){
			pthread_join(*thread, NULL);
			free(thread);
			thread = QPop(threads);
		}
		//output data
		double revenue = 0;
		LLNode* curr = HTDumpList(customers);
		while(curr != NULL){
			Customer* cus = curr->value;
			if(cus == NULL){
				curr = curr->next;
				continue;
			}
			printf("=== BEGIN CUSTOMER INFO ===\n");
			printf("### BALANCE ###\n");
			printf("Customer name: %s\n", cus->name);
			printf("Customer ID number: %d\n", cus->id);
			printf("Remaining credit balance after all purchases (a dollar amount): %.2f\n", cus->balance);
			printf("### SUCCESSFUL ORDERS ###\n");
			
			ONode* ocurr = cus->completed;
			while(ocurr!=NULL){
				Order* order = ocurr->order;
				if(order != NULL){
					printf("%s|%.2f|%.2f\n",order->title, order->price, order->remaining);
					revenue += order->price;
				}
				ocurr = ocurr->next;
			}
			
			printf("### REJECTED ORDERS ###\n");
			
			ocurr = cus->failed;
			while(ocurr!=NULL){
				Order* order = ocurr->order;
				if(order != NULL)
					printf("%s|%.2f\n",order->title, order->price);
				ocurr = ocurr->next;
			}
			
			printf("=== END CUSTOMER INFO ===\n");
			LLNode* tmp = curr;
			curr = curr->next;
			free(tmp);
			if(curr != NULL)
				printf("\n");
		}
		
		printf("\nTotal Revenue Gained: %.2f\n\n",revenue);
		
		//free objects
		HTDestroy(customers);
		HTDestroy(orderQueues);
		QDestroy(threads);
		return 0;
}
