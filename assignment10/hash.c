#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR 10
#define MAX_ELEMENT 100

typedef struct element{
	char key[MAX_CHAR];
	int value;
}element;

element hash_table[MAX_ELEMENT];

int transform(char key[]){
	int number = 0;
	char* c_ptr = key;
	while(*c_ptr){
		number += *c_ptr++;
	}
	return number;
}

int hash(element e){
	return transform(e.key) % MAX_ELEMENT;
}

void hash_table_insert(element table[], element e){
	int index = hash(e);
	if(!strcmp(table[index].key, e.key)){
		printf("key duplicated\n");
		exit(1);
	}
	while(!(table+index)){
		index  = (index+1) % MAX_ELEMENT;
		if(index == hash(e)){
			printf("hash table is full\n");
			exit(1);
		}
	}
	table[index] = e;
}

int main(){
	element tmp;
	strcpy(tmp.key,"wowwowzzz");
	tmp.value = 2;
	hash_table_insert(hash_table, tmp);
	printf("%d\n", hash(tmp));
	printf("%d", hash_table[hash(tmp)].value);
}
