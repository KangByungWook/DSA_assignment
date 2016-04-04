#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "stack.h"
#include "maze.h"

int main(){
	int i, j, move_status;
	
	printf("미로찾기를 시작합니다\n");
	Sleep(3000);
	system("cls");
		
	// 시작 위치 세팅 
	trace start = {1,1,0};
	maze_map[start.row][start.col] = 1;
	print_maze_map(maze_map_original, 10, 10, 1, 1);
	Sleep(300);
	system("cls");
	Push(&top, start);
	
	do{
		move_status = move(stack[top]);	
	}
	while(move_status != 0 && !isEmpty(stack));
	
	if(isEmpty(stack)){
		printf("도저히 방법이 없습니다\n");
	}
	
	return 0;	
}
