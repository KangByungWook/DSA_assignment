#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "stack.h"
#include "maze.h"

int main(){
	int i, j, move_status;
	
	printf("�̷�ã�⸦ �����մϴ�\n");
	Sleep(3000);
	system("cls");
		
	// ���� ��ġ ���� 
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
		printf("������ ����� �����ϴ�\n");
	}
	
	return 0;	
}
