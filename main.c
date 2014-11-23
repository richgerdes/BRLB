#include "hashtable.h"
#include "queue.h"
#include "bookorder.h"

Queue* threads;
Hashtable* orderQueues;
Hashtable* customers;
int flag_finished;

int main(int argc, char* argv[]){
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