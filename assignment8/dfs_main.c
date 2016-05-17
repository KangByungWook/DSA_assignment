#include <stdio.h>
#include "dfs.h"

void main(void){
	int i = 0;
	Graph g;
	
	init(&g);
	
	for(i = 0 ; i < MAX_VERTICES;i++) visited[i] = FALSE;
	for( i = 0 ; i < MAX_VERTICES ; i++)insertVertex(&g, i);
	
	insertEdge(&g,0,1);
	insertEdge(&g,0,2);
	insertEdge(&g,1,4);
	insertEdge(&g,4,3);
	insertEdge(&g,4,8);
	insertEdge(&g,7,8);
	insertEdge(&g,3,7);
	insertEdge(&g,3,5);
	insertEdge(&g,5,7);
	insertEdge(&g,2,3);
	insertEdge(&g,2,6);
	dfs(&g, 0);
	
	return 0;
}
