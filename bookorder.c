#include "bookorder.h"

Customer* CustomerCreate(int id, double balance, char* name){

}

ONode* ONodeCreate(Order* order, ONode* next){

}

Order* OrderCreate(char* title, double price, int coustomer){

}


void CustomerDestroy(Customer* c{

}

void ONodeDestroy(ONode* n){

}

void OrderDestroy(Order* o){

}

 //adds new onode to completed list
void CustomerAddCompleted(Customer* c, Order* o){
	pthread_mutex_lock(&(c->lock));
	
	//code here
	
	pthread_mutex_unlock(&(c->lock));
}

 //adds new onodes to failed list
void CustomerAddFailed(Customer* c, Order* o){
	pthread_mutex_lock(&(c->lock));
	
	//code here
	
	pthread_mutex_unlock(&(c->lock));
}
