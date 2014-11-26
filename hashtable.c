#include "hashtable.h"

HTNode* HTNodeCreate(void* key, void* value, HTNode* next){
	HTNode* n = (HTNode*) malloc(sizeof(HTNode));
	if(n == NULL)
		return NULL;
	
	n->key = key;
	n->value = value;
	n->next = next;
	
	return n;
}

Hashtable* HTCreate(int size, HashFct hashfct, FreeFct freefct, CmpFct cmpfct){
	Hashtable* ht = (Hashtable*) malloc(sizeof(Hashtable));
	if(ht == NULL)
		return NULL;
	
	ht->size = size;
	ht->nodes = (HTNode**) malloc(sizeof(HTNode*) * size);
	
	int i = 0;
	for(i = 0; i < ht->size; i++){
		ht->nodes[i] = NULL;
	}
	ht->hashfct = hashfct;
	ht->freefct = freefct;
	ht->cmpfct = cmpfct;
	
	return ht;
}

void HTNodeDestroy(HTNode* node, FreeFct freefct){
	if(node == NULL)
		return;
	
	freefct(node->value);
	node->value = NULL;
	node->next = NULL;
	
	free(node);
}

void HTNodeDestroyR(HTNode* node, FreeFct freefct){
	if(node == NULL)
		return;
	
	HTNodeDestroyR(node->next, freefct);
	node->next = NULL;
	HTNodeDestroy(node, freefct);
	
}

void HTDestroy(Hashtable* ht){
	if(ht == NULL)
		return;
	
	int i = 0;
	for(i = 0; i < ht->size; i++){
		HTNodeDestroyR(ht->nodes[i], ht->freefct);
		ht->nodes[i] = NULL;
	}
	
	free(ht->nodes);
	ht->nodes = NULL;
	ht->size = 0;
	
	free(ht);
}


void HTAdd(Hashtable* ht, void* value, void* key){
	int i = ht->hashfct(key);
	
	HTNode* curr = ht->nodes[i];
	
	if(curr == NULL){
		ht->nodes[i] = HTNodeCreate(key,value,NULL);
		return;
	}
	
	while(curr!= NULL && !(ht->cmpfct(curr->key,key))==0){
		curr = curr->next;
	}
	
	if(curr == NULL){
		ht->nodes[i] = HTNodeCreate(key,value,ht->nodes[i]);
		return;
	}
}

void* HTGet(Hashtable* ht, void* key){
	int i = ht->hashfct(key);
	
	HTNode* curr = ht->nodes[i];
	
	if(curr == NULL){
		return NULL;
	}
	
	while(!(ht->cmpfct(curr->key,key))==0){
		curr = curr->next;
	}
	
	if(curr == NULL){
		return NULL;
	}
	
	return curr->value;
}

LLNode* HTDumpList(Hashtable* ht){
	if(ht == NULL)
		return NULL;
		
	int i = 0;
	LLNode* head = NULL;
	for(i = 0; i < ht->size; i++){
		HTNode* n = ht->nodes[i];
		while(n != NULL){
			LLNode* new = malloc(sizeof(LLNode));
			new->next = head;
			new->value = n->value;
			head = new;
			n = n->next;
		}
	}
	
	return head;
	
}
