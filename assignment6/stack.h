#ifndef MY_OPER_STACK
#define MY_OPER_STACK

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0 

char oper_stack[MAX_STACK_SIZE];
int top = -1;

int is_empty(int *ptop){
	return *ptop == -1 ? TRUE:FALSE;	
}
int is_full(int *ptop){
	return (*ptop == MAX_STACK_SIZE - 1) ? TRUE : FALSE;	
}
int get_length(int *ptop){
	return *ptop+1;
}
void push(char oper, int *ptop){
	if(is_full(ptop)){
		printf("스택이 꽉 찼습니다.\n");
		return;
	}
	oper_stack[++*ptop] = oper;
}

char pop(int *ptop){
	char tmp;
	if(is_empty(ptop)){
		printf("스택이 비어있습니다\n");
		return NULL;
	}
	tmp = oper_stack[*ptop];
	--(*ptop);
	return tmp;
}

void print_element(int *ptop){
	int i;
	for(i = 0 ; i < *ptop + 1; i++){
		printf("%c ", oper_stack[i]);
	}
	printf("\n");
}

char get_top(int *ptop){
	return oper_stack[*ptop];
}


#endif
