#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "maze.h"

int main(){
	int i, j, move_status;
	
	print_maze_map(maze_map_original, 10, 10, 3, 3);
	
	printf("�̷�ã�⸦ �����մϴ�\n");
	
	// ���� ��ġ ���� 
	trace start = {1,1,0};
	maze_map[start.row][start.col] = 1;
	Push(&top, start);
	
	do{
		move_status = move(stack[top]);	
	}
	while(move_status != 0 && !isEmpty(stack));
	
	if(isEmpty(stack)){
		printf("������ ����� �����ϴ�\n");
	}
	else{
		printf("������ ������ ���ƽ��ϴ�.\n");
	}
	
	return 0;	
}
