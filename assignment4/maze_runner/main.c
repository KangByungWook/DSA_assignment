#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "stack.h"
#include "maze.h"

int main(){
	
	// 8x8 지도의 정보가 담긴 텍스트파일을 읽어와서 maze_map과 maze_map_original에 저장 
	initialize_map();
	
	int i, j, move_status;
	
	printf("미로찾기를 시작합니다\n");
	Sleep(2000);
	// 콘솔창 클리어 
	system("cls");
		
	// 시작 위치 세팅 
	trace start = {1,1,0};
	// maze_map의 시작 위치를 1로 바꿈 
	maze_map[start.row][start.col] = 1;
	print_maze_map(maze_map_original, 10, 10, 1, 1);
	Sleep(300);
	// 콘솔창 클리어
	system("cls");
	Push(&top, start);
	
	// 스택이 비거나 용을 잡고 목표점에 도착할때까지 움직인다. 
	do{
		move_status = move(stack[top]);	
	}
	while(move_status != 0 && !isEmpty(stack));
	
	// 스택이 비어있는 경우
	// 즉 해답이 없는 경우 
	if(isEmpty(stack)){
		printf("도저히 방법이 없습니다\n");
	}
	
	return 0;	
}
