#ifndef MY_NODE_STACK
#define MY_NODE_STACK

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0 

// 노드를 가리키는 노드포인터 타입  
typedef struct eval_node *node_ptr;

// 트리의 노드 구조체 선언 
typedef struct eval_node{
	char data;
	float result;
	node_ptr left_child, right_child;
}eval_node;

// 노드포인터 타입 스택
// 트리를 만들때 사용함 
node_ptr node_ptr_stack[MAX_STACK_SIZE];

// top의 초기 위치는 -1 
int node_ptr_stack_top = -1;

// 노드스택이 비어있는지 판단 
int node_stack_is_empty(int *ptop){
	return *ptop == -1 ? TRUE:FALSE;	
}

// 노드스택이 꽉 찼는지 판단. 
int node_stack_is_full(int *ptop){
	return (*ptop == MAX_STACK_SIZE - 1) ? TRUE : FALSE;	
} 

// 노드스택의 길이를 구하는 함수 
int node_stack_get_length(int *ptop){
	return *ptop+1;
}

// 노드 스택 push 
void node_stack_push(node_ptr oper, int *ptop){
	if(is_full(ptop)){
		printf("스택이 꽉 찼습니다.\n");
		return;
	}
	node_ptr_stack[++*ptop] = oper;
}

// 노드 스택 pop 
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

// 노스 스택의 top에 위치한 요소를 가져온다. 
node_ptr node_stack_get_top(int *ptop){
	return node_ptr_stack[*ptop];
}


#endif
