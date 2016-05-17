#include <stdio.h>
#define MAX_VERTICES 10
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];

typedef struct Graph{
	int adjMatrix[MAX_VERTICES][MAX_VERTICES];
	int n;
}Graph;

void init(Graph *g){
	int i,j;
	g->n = 0;
	for(i = 0 ; i < MAX_VERTICES; i++){
		for(j = 0 ; j < MAX_VERTICES; j++){
			adjMatrix[i][j] = 0;
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
		printf("정점 번호가 잘못됨. 정점 번호는 0~N-1 \n");
		rerturn l
	}
	
	g->adjMatrix[u][v] = 1;
	g->adjMatrix[v][u] = 1;
}


void dfs(Graph *g, int v){
	int w;
	visited[v] = TRUE;
	printf("%d ->", v);
}

