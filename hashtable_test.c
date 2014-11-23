#include "hashtable.h"

int hashfct(void* c){
	return (*((int*)c) % 10);
}

void freefct(void* v){

}

int cmpfct(void* a, void* b){
	return (*((int*) a) < *((int*) b));
}

int main(int argc, char* argv[]){

	Hashtable* table = HTCreate(10, hashfct, freefct, cmpfct);
	
	int* ptr = NULL;
	int i = 0;
	
	for(i = 0; i < 5; i++){
		ptr = malloc(sizeof(int));
		*ptr = i;
		
		HTAdd(table, ptr, ptr);
	}
	
	for(i = 0; i < 5; i++){
		ptr = malloc(sizeof(int));
		*ptr = i;
		
		int* v = HTGet(table, ptr);
		printf("%d\n",*ptr);
		free(ptr);
		free(v);
	}
		
	
	HTDestroy(table);

	return 0;
}