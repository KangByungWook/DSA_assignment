#ifndef stack_h
#define stack_h

#include <stdio.h>
#define MAX 100
// 스택에 쌓아둘 이동 정보. 
typedef struct trace{
	// y축 좌표 
	int row;
	// x축 좌표 
	int col;
	
	// 온 방향
	// 즉 어느 방향으로부터 왔는지
	// 백트래킹 시 해당 방향을 제외하기 위함 
	// 0: 북쪽, 1:동쪽, 2: 남쪽, 3: 서쪽  
	int dir;
}trace;
trace stack[MAX];
int top = -1;

int isEmpty(trace* stack);
int isFUll(trace* stack);
int Push(int *ptop, trace item);
int Pop(int *ptop);
int PrintStack();

int isEmpty(trace *stack){
    if(top < 0){
        return 1;
    }
    else
        return 0;
}

int isFull(trace *stack){
    if(top >= MAX - 1)
        return 1;
    else
        return 0;
}

int PrintStack(){
    int i;
//    for(i = top ; i > -1 ; i--){
//        printf("%d\n", stack[i].key);
//    }
    return 1;
}

int Push(int *ptop, trace item){
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

#endif
