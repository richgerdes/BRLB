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
		//cast _vqueue into queue
		printf("I am a thread\n");
		while(!flag_finished){
				usleep(1000);
				//pop order from queue
				//if order == null
				//	continue;
				//get customer
				//if customer->balance > order->price
				//	CustomerAddCompleted(customer, order)
				//else
				//	CustomerAddFailed(customer, order)

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
			char categorie[1000]; 
			while(fgets( categorie, sizeof categorie, file ) != NULL){
				//fputs (categorie, stdout );
				Queue *q = QCreate(20);
				HTAdd(orderQueues, q , categorie);
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
						ptr = id;
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
				i = 0;
			}
			fclose ( file );
		}else{
			perror ( filename ); 
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
			char s[2] = "|";
			int i = 0;
			char *token;
			while(fgets( orders, sizeof orders, fp1 ) != NULL){
				token = strtok(orders, s);
				while( token != NULL ){
					//printf( " %s\n", token );
					token = strtok(NULL, s);
					i++;
				}
				i = 0;
			}
			fclose ( file );
		}else{
			perror ( filename ); 
		}
		flag_finished = 1;
		pthread_t *thread = QPop(threads);
		
		while(thread != NULL){
			pthread_join(*thread, NULL);
			thread = QPop(threads);
		}
		
		return 0;
		//set finish flag
		//wait for queues
		//	pop thread in threads
		//		pthread_join(thread);
		//output data
		//free objects
}
