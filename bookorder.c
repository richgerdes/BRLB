#include "bookorder.h"

Customer* CustomerCreate(int id, double balance, char* name, char* address, char* state, char* zip){
	Customer* c = (Customer*) malloc(sizeof(Customer));
	if(c == NULL)
		return NULL;

	c->id = id;
	c->balance = balance;
	c->name = (char*) malloc(sizeof(char) * strlen(name));
	memset(c->name,'\0',sizeof(char) * strlen(name));
	memcpy(c->name, name, sizeof(char) * strlen(name));
	c->address = (char*) malloc(sizeof(char) * strlen(address));
	memset(c->address,'\0',sizeof(char) * strlen(address));
	memcpy(c->address, address, sizeof(char) * strlen(address));
	c->state = (char*) malloc(sizeof(char) * strlen(state));
	memset(c->state,'\0',sizeof(char) * strlen(state));
	memcpy(c->state, state, sizeof(char) * strlen(state));
	c->zip = (char*) malloc(sizeof(char) * strlen(zip));
	memset(c->zip,'\0',sizeof(char) * strlen(zip));
	memcpy(c->zip, zip, sizeof(char) * strlen(zip));
	c->completed = NULL;
	c->failed = NULL;
	pthread_mutex_init(&(c->lock), NULL);
	
	return c;
}

ONode* ONodeCreate(Order* order, ONode* next){
	ONode* o = (ONode*) malloc(sizeof(ONode));
	if(o == NULL)
		return NULL;
		
	o->order = order;
	o->next = next;
	
	return o;
}

Order* OrderCreate(char* title, double price, int customer){
	Order* o = (Order*) malloc(sizeof(Order));
	if(o == NULL)
		return NULL;
		
	o->title = (char*) malloc(sizeof(char) * strlen(title));
	memset(o->title,'\0',sizeof(char) * strlen(title));
	memcpy(o->title, title, sizeof(char) * strlen(title));
	o->price = price;
	o->customer = customer;
	
	return o;
}


void CustomerDestroy(Customer* c){
	if(c == NULL)
		return;
		
	free(c->name);
	c->id = 0;
	c->balance = 0;
	ONodeDestroy(c->completed);
	c->completed = NULL;
	ONodeDestroy(c->failed);
	c->failed = NULL;
	pthread_mutex_destroy(&(c->lock));
	
}

void ONodeDestroy(ONode* n){
	if(n == NULL)
		return;
		
	OrderDestroy(n->order);
	n->order = NULL;
	ONodeDestroy(n->next);
	n->next = NULL;
	free(n);
}

void OrderDestroy(Order* o){
	if(o == NULL)
		return;
	
	free(o->title);
	o->price = 0;
	o->customer = 0;
}

 //adds new onode to completed list
void CustomerAddCompleted(Customer* c, Order* o){
	pthread_mutex_lock(&(c->lock));
	
	//code here
	ONode* new = ONodeCreate(o,c->completed);
	if(new != NULL)
		c->completed = new;
	
	pthread_mutex_unlock(&(c->lock));
}

 //adds new onodes to failed list
void CustomerAddFailed(Customer* c, Order* o){
	pthread_mutex_lock(&(c->lock));
	
	//code here
	ONode* new = ONodeCreate(o,c->failed);
	if(new != NULL)
		c->failed = new;
	
	pthread_mutex_unlock(&(c->lock));
}
