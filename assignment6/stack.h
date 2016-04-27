#ifndef MY_OPER_STACK
#define MY_OPER_STACK

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0 

// ���� ����
// ������ �Ǵ� �ǿ����ڸ� ��Ƶδ� ���� 
char oper_stack[MAX_STACK_SIZE];

// ������ top�� -1�� �ʱ�ȭ 
int top = -1;

// ������ ����ִ��� �Ǵ� 
int is_empty(int *ptop){
	return *ptop == -1 ? TRUE:FALSE;	
}

// ������ �������ִ��� �Ǵ� 
int is_full(int *ptop){
	return (*ptop == MAX_STACK_SIZE - 1) ? TRUE : FALSE;	
}

// ������ ���̸� ������ 
int get_length(int *ptop){
	return *ptop+1;
}

// ���ÿ� push�ϴ� �Լ� 
void push(char oper, int *ptop){
	if(is_full(ptop)){
		printf("������ �� á���ϴ�.\n");
		return;
	}
	oper_stack[++*ptop] = oper;
}

// ���ÿ��� pop�ϴ� �Լ� 
char pop(int *ptop){
	char tmp;
	if(is_empty(ptop)){
		printf("������ ����ֽ��ϴ�\n");
		return NULL;
	}
	tmp = oper_stack[*ptop];
	--(*ptop);
	return tmp;
}

// ������ top�� �ִ� ���ڸ� �������� �Լ� 
char get_top(int *ptop){
	return oper_stack[*ptop];
}


#endif
