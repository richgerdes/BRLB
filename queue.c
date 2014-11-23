#include "queue.h"

QNode* QNodeCreate(void* value){
	QNode* n = (QNode*) malloc(sizeof(QNode));
	if(n == NULL)
		return NULL;
	
	n->value = value;
	n->next = NULL;
	
	return n;
}

Queue* QCreate(int size){
	Queue* q = (Queue*) malloc(sizeof(Queue));
	if(q == NULL)
		return NULL;
	
	
	q->first = NULL;
	q->last = NULL;
	q->size = size;
	q->count = 0;
	pthread_mutex_init(&(q->lock), NULL);
	
	return q;
	
}

void QNodeDestroy(QNode* node){
	if(node == NULL)
		return;
		
	node->value = NULL;
	node->next = NULL;
	free(node);
}

void QNodeDestroyR(QNode* node){
	if(node == NULL)
		return;
		
	QNodeDestroyR(node->next);
	node->next = NULL;
	QNodeDestroy(node);
}

void QDestroy(Queue* queue){
	if(queue == NULL)
		return;
	
	queue->last = NULL;
	QNodeDestroyR(queue->first);
	queue->first = NULL;
	queue->size = 0;
	queue->count = 0;
	pthread_mutex_destroy(&(queue->lock));
	free(queue);
}


int QPush(Queue* queue, void* data){

	if(queue == NULL)
		return 0;

	pthread_mutex_lock(&(queue->lock));
	
	if(queue->size == queue->count){
		pthread_mutex_unlock(&(queue->lock));
		return 0;
	}
	
	QNode* n = QNodeCreate(data);
	
	if(queue->first == NULL){
		queue->first = n;
		queue->last = n;
		queue->count++;
	
		pthread_mutex_unlock(&(queue->lock));
		
		return 1;
	}
	
	if(queue->last != NULL){
		QNode* curr = queue->first;
		while(curr->next != NULL)
			curr = curr->next;
		queue->last = curr;
	}
	
	queue->last->next = n;
	queue->last = n;
	queue->count++;
	
	pthread_mutex_unlock(&(queue->lock));
		
	return 1;
}

void* QPop(Queue* queue){

	pthread_mutex_lock(&(queue->lock));
	
	if(queue->count == 0){
		pthread_mutex_unlock(&(queue->lock));
		return NULL;
	}

	if(queue->first == NULL){
		queue->count = 0;
		pthread_mutex_unlock(&(queue->lock));
		return NULL;
	}
	
	QNode* first = queue->first;
	queue->first = first->next;
	if(queue->first == NULL)
		queue->last = NULL;
	queue->count--;
	
	void* data = first->value;
	free(first);
		
	pthread_mutex_unlock(&(queue->lock));
	
	return data;

}


int QFull(Queue* queue){
	if(queue->count == queue->size)
		return 1;
	return 0;
}
