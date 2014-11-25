#include "hashtable.h"
#include "queue.h"
#include "bookorder.h"
#include "extra.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

Queue* threads;
Hashtable* orderQueues;
Hashtable* customers;
int flag_finished;

void* consumer(void* _vqueue){
		//cast _vqueue into queue
		while(!flag_finished){
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

		orderQueues = HTAdd(26,hashStr,QueueDestroy,cmpKeyStr);
		customers = HTAdd(10,hashInt,CustomerDestroy,cmpKeyInt);
		threads = QueueCreate(20);
		flag_finished = 0;

		static const char filename[] = "categories.txt";
		FILE *file = fopen ( filename, "r" );
		if ( file != NULL ){
			char categorie[1000]; 
			while(fgets( categorie, sizeof categorie, file ) != NULL){
				fputs (categorie, stdout );
				Queue *q = QCreate(20);
				printf("after creating q\n");
				HTAdd(orderQueues, q , categorie);
				printf("after adding to hashtable\n");
				pthread_t* thread = malloc(sizeof(pthread_t));
				printf("after mallocing thread\n");
				pthread_create(thread, NULL, &consumer, q);
				printf("after pthread create\n");
				QPush(threads, thread);
				printf("after pushing to the q");
			}
			fclose ( file );
		}else{
			perror ( filename ); 
		}
		flag_finished = 1;
		pthread_t *thread = QPop(threads);
		
		while(thread != NULL){
			pthread_join(*thread, NULL);		
		}
		
		return 0;

		//init objects
		//read in categories
		//	for each category
		//		make a queue
		//		add queue to orderQueues
		//		create pthread_t thread
		//		pthread_create(thread, NULL, &consumer, queue
		//		add thread to threads
		//read in database
		//	for each customer
		//		make customer
		//		add customer to customers
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
