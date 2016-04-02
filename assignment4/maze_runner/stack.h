#ifndef stack_h
#define stack_h

#include <stdio.h>
#define MAX 100
// ���ÿ� �׾Ƶ� �̵� ����. 
typedef struct trace{
	// y�� ��ǥ 
	int row;
	// x�� ��ǥ 
	int col;
	
	// �� ����
	// �� ��� �������κ��� �Դ���
	// ��Ʈ��ŷ �� �ش� ������ �����ϱ� ���� 
	// 0: ����, 1:����, 2: ����, 3: ����  
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
        printf("������ �� á���ϴ�\n");
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
        printf("������ ����ֽ��ϴ�\n");
        return 0;
    }
    else{
        stack[--*ptop];
        return 1;
    }
}

#endif
