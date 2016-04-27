#ifndef MY_OPER_STACK
#define MY_OPER_STACK

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0 

// 문자 스택
// 연산자 또는 피연산자를 담아두는 스택 
char oper_stack[MAX_STACK_SIZE];

// 스택의 top을 -1로 초기화 
int top = -1;

// 스택이 비어있는지 판단 
int is_empty(int *ptop){
	return *ptop == -1 ? TRUE:FALSE;	
}

// 스택이 가득차있는지 판단 
int is_full(int *ptop){
	return (*ptop == MAX_STACK_SIZE - 1) ? TRUE : FALSE;	
}

// 스택의 길이를 가져옴 
int get_length(int *ptop){
	return *ptop+1;
}

// 스택에 push하는 함수 
void push(char oper, int *ptop){
	if(is_full(ptop)){
		printf("스택이 꽉 찼습니다.\n");
		return;
	}
	oper_stack[++*ptop] = oper;
}

// 스택에서 pop하는 함수 
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

// 스택의 top에 있는 문자를 가져오는 함수 
char get_top(int *ptop){
	return oper_stack[*ptop];
}


#endif
