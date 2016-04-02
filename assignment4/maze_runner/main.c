#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "maze.h"

int main(){
	int i, j;
	for(i = 0 ; i < 4 ; i++){
		printf("%d순위 : %d %d\n", i, moves[i].ver, moves[i].hor);
	}
	
	print_maze_map();
	
	printf("미로찾기를 시작합니다\n");
	
	trace start = {1,1,0};
	maze_map[start.row][start.col] = 1;
	Push(&top, start);
	int move_status = move(stack[top]);
	while(move_status != 0){
		move_status = move(stack[top]);
	}
	
	return 0;	
}
