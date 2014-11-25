#ifndef BOOKORDER
#define BOOKORDER
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

typedef struct _customer Customer;
typedef struct _onode ONode;
typedef struct _order Order;

struct _customer{
	int id;
	double balance;
	char* name;
	char* address;
	char* state;
	char* zip;
	ONode* completed;
	ONode* failed;
	pthread_mutex_t lock;
};

struct _onode{
	Order* order;
	ONode* next;
};

struct _order{
	char* title;
	double price;
	int customer;
};


Customer* CustomerCreate(int id, double balance, char* name, char* address, char* state, char* zip);
ONode* ONodeCreate(Order* order, ONode* next);s
Order* OrderCreate(char* title, double price, int customer);

void CustomerDestroy(Customer* c);
void ONodeDestroy(ONode* n);
void OrderDestroy(Order* o);

void CustomerAddCompleted(Customer* c, Order* o); //adds new onode to completed list
void CustomerAddFailed(Customer* c, Order* o); //adds new onodes to failed list

#endif