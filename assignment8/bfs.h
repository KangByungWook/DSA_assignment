#include <stdio.h>
#define MAX_SIZE 1000
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100

int visited[MAX_VERTICES];


typedef struct Queue{
	int queue[MAX_SIZE+1];
	int rear;
	int front;
}Queue;

typedef struct Graph{
	int adjMatrix[MAX_VERTICES][MAX_VERTICES];
	int n;
}Graph;

void init(Graph *g){
	int i,j;
	g->n = 0;
	for(i = 0 ; i < MAX_VERTICES; i++){
		for(j = 0 ; j < MAX_VERTICES; j++){
			g->adjMatrix[i][j] = 0;
		}
	}
}

void insertVertex(Graph *g, int v){
	if(g->n == MAX_VERTICES){
		printf("정점 개수가 너무 많습니다. 노드 삽입 불가\n");
		return ;
	}
	
	g->n++;
}

void insertEdge(Graph *g, int u, int v){
	if(u >= g->n || v >= g->n){
		printf("정점 번호가 잘못됨.\n");
		return ;
	}
	g->adjMatrix[u][v] = 1;
	g->adjMatrix[v][u] = 1;
}

void initQueue(Queue* q){
	q->front = q->rear = 0;
}

int isFull(Queue* q){
	if((q->rear + 1)%MAX_SIZE == q->front)
		return 1;
	else
		return 0;
}

int isEmpty(Queue* q){
	if(q->front == q->rear)return 1;
	else return 0;
}

void enqueue(Queue* q, int data){
	if(isFull(q)){
		printf("Queue is full\n");
		exit(0);
	}else{
		q->rear = (q->rear+1)%MAX_SIZE;
		q->queue[q->rear] = data;
	}
}

int dequeue(Queue* q){
	int temp = -1;
	
	if(isEmpty(q)){
		printf("Queue is empty\n");
		exit(0);
	}
	else{
		q->front = (q->front+1)%MAX_SIZE;
	}
	return q->queue[q->front];
}

void bfs(Graph *g, int v){
	int w;
	Queue q;
	initQueue(&q);
	
	visited[v] = TRUE;
	printf("%d->", v);
	enqueue(&q,v);
	while(!isEmpty(&q)){
		v = dequeue(&q);
		for(w=0; w < g->n ; w++){
			if(g->adjMatrix[v][w] && !visited[w]){
				visited[w] = TRUE;
				printf("%d->", w);
				enqueue(&q, w);
			}
		}
	}
}

