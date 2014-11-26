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
			char *token;
			int i = 0;
			while(fgets( database, sizeof database, fp ) != NULL){
				token = strtok(database, s);
				while( token != NULL ){
					//printf( " %s\n", token );
					if(i == 0){
					char *name = token;
					printf("This is the name: %s\n", name);
					}else if(i == 1){
					int id = atoi(token);
					printf("This is the id: %d\n", id);
					}else if(i == 2){
					double balance = atof(token);
					printf("This is the balance: %f\n", balance );
					}
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

		//read in book orders
		//	for each order
		//		make order
		//		get correct queue
		//		add order to queue
		//set finish flag
		//wait for queues
		//	pop thread in threads
		//		pthread_join(thread);
		//output data
		//free objects
}
