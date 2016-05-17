#include <stdio.h>
#define MAX_SIZE 1000
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10

int visited[10];

typedef struct Queue{
	int queue[MAX_SIZE+1];
	int rear;
	int front;

}Queue;

typedef struct Graph{
	int adjMatrix[MAX_VERTICES][MAX_VERTICES];
	int n;
}Graph;

void initQueue(Queue* q){
	q->front = q->rear = 0;
}

int isFull(Queue* q){
		if((q->rear + 1)%MAX_SIZE == q->front)return 1;
		else return 0;
	}
}

int isEmpty(Queue* q){
	if(q->front == q->rear)return 1;
	else return 0;
}

void enqueue(Queue* q, int data){
	if(isFull(q)){
		printf("Queue is Full\n");
		exit(0);
	}
	else{
		q->rear = (q->rear+1)%MAX_SIZE;
		q->queue[q->rear] = data;
	}
}

int dequeue(Queue *q){
	int temp = 01;
	
	if(isEmpty(q)){
		printf("Queue is Empty\n");
		exit(0);
	}
	else{
		q->front = (q->front + 1) % MAX_SIZE;
	}
	return q->queue[q->front];
}

void bfs(Graph *g, int v){
	int w;;
	Queue q;
	initQueue(&q);
	
	visited[v] = TRUE;
	printf("%d->", v);
	while(!isEmpty(&q)){
		
	}
}

