#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "stack.h"
#include "maze.h"

int main(){
	
	// 8x8 ������ ������ ��� �ؽ�Ʈ������ �о�ͼ� maze_map�� maze_map_original�� ���� 
	initialize_map();
	
	int i, j, move_status;
	
	printf("�̷�ã�⸦ �����մϴ�\n");
	Sleep(2000);
	// �ܼ�â Ŭ���� 
	system("cls");
		
	// ���� ��ġ ���� 
	trace start = {1,1,0};
	// maze_map�� ���� ��ġ�� 1�� �ٲ� 
	maze_map[start.row][start.col] = 1;
	print_maze_map(maze_map_original, 10, 10, 1, 1);
	Sleep(300);
	// �ܼ�â Ŭ����
	system("cls");
	Push(&top, start);
	
	// ������ ��ų� ���� ��� ��ǥ���� �����Ҷ����� �����δ�. 
	do{
		move_status = move(stack[top]);	
	}
	while(move_status != 0 && !isEmpty(stack));
	
	// ������ ����ִ� ���
	// �� �ش��� ���� ��� 
	if(isEmpty(stack)){
		printf("������ ����� �����ϴ�\n");
	}
	
	return 0;	
}
