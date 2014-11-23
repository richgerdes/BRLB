#include "queue.h"
#include "hashtable.h"

int main(int argc, char* argv[]){

	Queue* queue = QCreate(5);
	if(queue == NULL)
		return 0;
	
	int *ptr = malloc(sizeof(int));
	*ptr = 1;
	
	if(!QPush(queue, ptr))
		printf("failed\n");
	
	ptr = malloc(sizeof(int));
	*ptr = 2;
	
	if(!QPush(queue, ptr))
		printf("failed\n");
	
	ptr = malloc(sizeof(int));
	*ptr = 3;
	
	if(!QPush(queue, ptr))
		printf("failed\n");
	
	ptr = malloc(sizeof(int));
	*ptr = 4;
	
	if(!QPush(queue, ptr))
		printf("failed\n");
	
	ptr = malloc(sizeof(int));
	*ptr = 5;
	
	if(!QPush(queue, ptr))
		printf("failed\n");
	
	ptr = malloc(sizeof(int));
	*ptr = 6;
	
	if(!QPush(queue, ptr))
		printf("failed\n");
		
	free(ptr);
	
	ptr = QPop(queue);
	
	while(ptr != NULL){
		printf("%d\n",*ptr);
		free(ptr);
		ptr = QPop(queue);
	}
	
	QDestroy(queue);
	free(ptr);
	
	return 0;
}