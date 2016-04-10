#ifndef stack_h
#define stack_h

#include <stdio.h>
#define MAX 100
typedef struct element{
	// postFix연산시에 숫자값을 넣을 변수 
	float fnum;
	
	// infix를 postFix로 변환할때 읽어온 문자열 값을 넣을 변수 
	char oper[20];
	
	// oper가 연산자인 경우 해당 연산자의 우선순위 
    int precedence;
}element;

// 스택 배열 선언 
element stack[MAX];

// top위치 -1로 초기화. 
int top = -1;

int isEmpty(element* stack);
int isFull(element* stack);
int Push(int *ptop, element item);
int Pop(int *ptop);
int PrintStack();

// 스택이 비어있는지 검증하는 함수
// 비어있을 경우 1, 아닐 경우 0 반환 
int isEmpty(element *stack){
    if(top < 0){
        return 1;
    }
    else
        return 0;
}

// 스택이 꽉찼는지 검증하는 함수
// 꽉찼을 경우 1, 아닐 겨웅 0 반환 
int isFull(element *stack){
    if(top >= MAX - 1)
        return 1;
    else
        return 0;
}

// 스택을 프린트해주는 함수 
int PrintStack(){
    int i;
    for(i = top ; i > -1 ; i--){
        printf("%s\n", stack[i].oper);
    }
    return 1;
}

// 스택의 top에 element 변수를 push 
int Push(int *ptop, element item){
    int isfull = 0;
    isfull = isFull(stack);
    if(isfull == 1){
        return 0;
    }
    else{
        stack[++*ptop] = item;
        return 1;
    }
    
}

// 스택의 top을 pop해주는 함수. 
int Pop(int *ptop){
    int isempty = isEmpty(stack);
    if(isempty == 1){
        return 0;
    }
    else{
        stack[--*ptop];
        return 1;
    }
}




#endif /* stack_h */

