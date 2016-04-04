#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "maze.h"

int main(){
	int i, j, move_status;
	
	print_maze_map(maze_map_original, 10, 10, 3, 3);
	
	printf("미로찾기를 시작합니다\n");
	
	// 시작 위치 세팅 
	trace start = {1,1,0};
	maze_map[start.row][start.col] = 1;
	Push(&top, start);
	
	do{
		move_status = move(stack[top]);	
	}
	while(move_status != 0 && !isEmpty(stack));
	
	if(isEmpty(stack)){
		printf("도저히 방법이 없습니다\n");
	}
	else{
		printf("게임을 무사히 마쳤습니다.\n");
	}
	
	return 0;	
}
