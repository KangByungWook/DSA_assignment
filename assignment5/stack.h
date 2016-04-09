//
//  stack.h
//  maze
//
//  Created by KangByung wook on 2016. 4. 2..
//  Copyright ⓒ 2016년 KangByung wook. All rights reserved.
//

#ifndef stack_h
#define stack_h

#include <stdio.h>
#define MAX 100
typedef struct element{
	float fnum;
	char oper[20];
    int precedence;
}element;
element stack[MAX];
int top = -1;

int isEmpty(element* stack);
int isFUll(element* stack);
int Push(int *ptop, element item);
int Pop(int *ptop);
int PrintStack();


int isEmpty(element *stack){
    if(top < 0){
        return 1;
    }
    else
        return 0;
}

int isFull(element *stack){
    if(top >= MAX - 1)
        return 1;
    else
        return 0;
}

int PrintStack(){
    int i;
    for(i = top ; i > -1 ; i--){
        printf("%s\n", stack[i].oper);
    }
    return 1;
}

int Push(int *ptop, element item){
    int isfull = 0;
    isfull = isFull(stack);
    if(isfull == 1){
        printf("스택이 꽉 찼습니다\n");
        return 0;
    }
    else{
        stack[++*ptop] = item;
        return 1;
    }
    
}

int Pop(int *ptop){
    int isempty = isEmpty(stack);
    if(isempty == 1){
        printf("스택이 비어있습니다\n");
        return 0;
    }
    else{
        stack[--*ptop];
        return 1;
    }
}




#endif /* stack_h */

