#ifndef stack_h
#define stack_h

#include <stdio.h>
#define MAX 100
typedef struct element{
	// postFix����ÿ� ���ڰ��� ���� ���� 
	float fnum;
	
	// infix�� postFix�� ��ȯ�Ҷ� �о�� ���ڿ� ���� ���� ���� 
	char oper[20];
	
	// oper�� �������� ��� �ش� �������� �켱���� 
    int precedence;
}element;

// ���� �迭 ���� 
element stack[MAX];

// top��ġ -1�� �ʱ�ȭ. 
int top = -1;

int isEmpty(element* stack);
int isFull(element* stack);
int Push(int *ptop, element item);
int Pop(int *ptop);
int PrintStack();

// ������ ����ִ��� �����ϴ� �Լ�
// ������� ��� 1, �ƴ� ��� 0 ��ȯ 
int isEmpty(element *stack){
    if(top < 0){
        return 1;
    }
    else
        return 0;
}

// ������ ��á���� �����ϴ� �Լ�
// ��á�� ��� 1, �ƴ� �ܿ� 0 ��ȯ 
int isFull(element *stack){
    if(top >= MAX - 1)
        return 1;
    else
        return 0;
}

// ������ ����Ʈ���ִ� �Լ� 
int PrintStack(){
    int i;
    for(i = top ; i > -1 ; i--){
        printf("%s\n", stack[i].oper);
    }
    return 1;
}

// ������ top�� element ������ push 
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

// ������ top�� pop���ִ� �Լ�. 
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

