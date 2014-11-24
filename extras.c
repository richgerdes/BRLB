#include "extras.h"

int hashInt(void* v){
	return *((int*) v) % 10;
}

int cmpKeyInt(void* v, void* w){
	return (*((int*) v) <  *((int*) w));
}

int hashStr(void* v){
	char* c = (char*) v;


	char ch = c[0];

	if(ch >= 'A' && ch <= 'Z'){
		return ch - 'A';
	}else if(ch >= 'a' && ch <= 'z'){
		return ch - 'a';
	}else{
		return -1;
	}
}

int cmpKeyStr(void* v, void* w){
	return (strcmp(v, w));
}

