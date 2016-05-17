#include <stdio.h>
#include "bfs.h"

int main(){
	int i = 0 ;
	Graph g;
	
	init(&g);
	
	for(i = 0 ; i < MAX_VERTICES;i++) visited[i] = FALSE;
	for( i = 0 ; i < MAX_VERTICES ; i++)insertVertex(&g, i);
	
	insertEdge(&g,0,1);
	insertEdge(&g,0,2);
	insertEdge(&g,0,4);
	insertEdge(&g,1,2);
	insertEdge(&g,2,3);
	insertEdge(&g,2,4);
	insertEdge(&g,3,4);
	
	bfs(&g, 0);
	
}
