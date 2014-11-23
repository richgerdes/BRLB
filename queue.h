#ifndef QUEUE
#define QUEUE
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct _qnode QNode;
typedef struct _queue Queue;

struct _qnode{
	void* value;
	QNode* next;
};

struct _queue{
	QNode* first;
	QNode* last;
	int size;
	int count; 
	pthread_mutex_t lock;
};

QNode* QNodeCreate(void* value);
Queue* QCreate(int size);

void QNodeDestroy(QNode* node);
void QNodeDestroyR(QNode* node);
void QDestroy(Queue* queue);

int QPush(Queue* queue, void* data);
void* QPop(Queue* queue);

int QFull(Queue* queue);

#endif