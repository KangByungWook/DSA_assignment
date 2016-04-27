#ifndef MY_NODE_STACK
#define MY_NODE_STACK

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0 

// ��带 ����Ű�� ��������� Ÿ��  
typedef struct eval_node *node_ptr;

// Ʈ���� ��� ����ü ���� 
typedef struct eval_node{
	char data;
	float result;
	node_ptr left_child, right_child;
}eval_node;

// ��������� Ÿ�� ����
// Ʈ���� ���鶧 ����� 
node_ptr node_ptr_stack[MAX_STACK_SIZE];

// top�� �ʱ� ��ġ�� -1 
int node_ptr_stack_top = -1;

// ��彺���� ����ִ��� �Ǵ� 
int node_stack_is_empty(int *ptop){
	return *ptop == -1 ? TRUE:FALSE;	
}

// ��彺���� �� á���� �Ǵ�. 
int node_stack_is_full(int *ptop){
	return (*ptop == MAX_STACK_SIZE - 1) ? TRUE : FALSE;	
} 

// ��彺���� ���̸� ���ϴ� �Լ� 
int node_stack_get_length(int *ptop){
	return *ptop+1;
}

// ��� ���� push 
void node_stack_push(node_ptr oper, int *ptop){
	if(is_full(ptop)){
		printf("������ �� á���ϴ�.\n");
		return;
	}
	node_ptr_stack[++*ptop] = oper;
}

// ��� ���� pop 
node_ptr node_stack_pop(int *ptop){
	node_ptr tmp;
	if(is_empty(ptop)){
		printf("������ ����ֽ��ϴ�\n");
		return NULL;
	}
	tmp = node_ptr_stack[*ptop];
	--(*ptop);
	return tmp;
}

// �뽺 ������ top�� ��ġ�� ��Ҹ� �����´�. 
node_ptr node_stack_get_top(int *ptop){
	return node_ptr_stack[*ptop];
}


#endif
