#ifndef maze_h
#define maze_h

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

// �̵��� ��ǥ ��ȭ ������ ��� ������ Ÿ��
// ������� �������� �̵��ϴ� ��� ver = -1, hor = 0; 
typedef struct offset{
	int ver;
	int hor;
}offset;



// ��,��,��,�� �װ��� �̵������� offset ��ķ� ����
// offset ��� ����� �ε����� �������� �켱������ �ǹ�
// �� -> �� -> �� -> �� ������ �켱���� ����
offset moves[4] = {{-1, 0}, {0 , 1}, {1, 0}, {0, -1}};

// �⺻ ������
// TODO ���Ϸκ��� ������ �о����. 
int maze_map[10][10] = {{1,1,1,1,1,1,1,1,1,1}, 
				   {1,0,1,1,1,1,1,1,1,1}, 
				   {1,0,0,0,0,0,0,0,1,1}, 
				   {1,1,1,0,1,1,1,1,1,1}, 
				   {1,1,1,0,1,1,1,1,1,1}, 
				   {1,1,0,0,0,0,0,0,0,1}, 
				   {1,1,0,1,1,1,1,99,1,1}, 
				   {1,1,0,0,0,0,1,1,1,1}, 
				   {1,1,1,1,1,0,0,0,100,1},
				   {1,1,1,1,1,1,1,1,1,1}} ;
int dragon_catch = 0; 
int arrival_befor_dragon_catch = 0;
// ��� ������ maze_map�� ������ִ� �Լ�
// TODO ���Ͽ��� �Է¹��� ��� �Լ� ������ �����ؾ��� �ʿ伺. 
void print_maze_map(){
	int i,j;
	for(i = 0 ; i < 10 ; i++){
		for(j = 0 ; j < 10; j++){
			printf("%3d ", maze_map[i][j]);
		}
		printf("\n");
	}
}

// ������ ���� ��ġ�� ������� �̵������� ���Ϲ޴� �Լ� 
int decide_direction(trace current_location){
	int dir = 0;
	while(maze_map[current_location.row + moves[dir].ver][current_location.col + moves[dir].hor] == 1 && dir < 4)dir++;
	if(dir == 4)return -1;
	else return dir;
} 

int move(trace current_location){
	// ���� ��ġ�κ��� ������ ������ �Ǵ�
	int dir = decide_direction(current_location);
	int next_row = current_location.row+moves[dir].ver;
	int next_col = current_location.col+moves[dir].hor;
	
	// �������� ������ ��� 
	if(maze_map[next_row][next_col] == 100){
		printf("�������� �����߽��ϴ�\n"); 
		return 0;
	}
	
	//���̻� ������ ���� ���� ��� 
	//���� pop�� top�� ��ġ�� trace������ �̵� �Ǵ� 
	if(dir == -1){
		Pop(&top);
		printf("�ڷΰ��� : ");
		printf("���� ��ġ: (%d, %d)\n", stack[top].row, stack[top].col); 
		return -1;
	} 
	//������ ���� �ִ� ���
	//���ÿ� ���� �̵� ��ġ������ push 
	else{
		trace new_data = {next_row, next_col,dir};
		Push(&top, new_data);
		// �̵� ��ġ 1�� �ٲ��ֱ�
		printf("���� : ");
		printf("���� ��ġ: (%d, %d)\n", stack[top].row, stack[top].col); 
		if(maze_map[next_row][next_col]==99){
			printf("���� ��ҽ��ϴ�\n");
		}
	
		maze_map[next_row][next_col] = 1; 
		return 1;
	} 
}
#endif
