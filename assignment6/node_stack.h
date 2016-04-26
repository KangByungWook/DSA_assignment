#ifndef MY_NODE_STACK
#define MY_NODE_STACK

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0 

typedef struct eval_node *node_ptr;
typedef struct eval_node{
	char data;
	node_ptr left_child, right_child;
}eval_node;

node_ptr node_ptr_stack[MAX_STACK_SIZE];
int node_ptr_stack_top = -1;


int node_stack_is_empty(int *ptop){
	return *ptop == -1 ? TRUE:FALSE;	
}
int node_stack_is_full(int *ptop){
	return (*ptop == MAX_STACK_SIZE - 1) ? TRUE : FALSE;	
}
int node_stack_get_length(int *ptop){
	return *ptop+1;
}
void node_stack_push(node_ptr oper, int *ptop){
	if(is_full(ptop)){
		printf("스택이 꽉 찼습니다.\n");
		return;
	}
	node_ptr_stack[++*ptop] = oper;
}

node_ptr node_stack_pop(int *ptop){
	node_ptr tmp;
	if(is_empty(ptop)){
		printf("스택이 비어있습니다\n");
		return NULL;
	}
	tmp = node_ptr_stack[*ptop];
	--(*ptop);
	return tmp;
}

void node_stack_print_element(int *ptop){
	int i;
	for(i = 0 ; i < *ptop + 1; i++){
		printf("%c ", node_ptr_stack[i]);
	}
	printf("\n");
}

node_ptr node_stack_get_top(int *ptop){
	return node_ptr_stack[*ptop];
}


#endif
