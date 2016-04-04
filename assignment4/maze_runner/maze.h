#ifndef maze_h
#define maze_h

#include <stdio.h>
#include <stdlib.h>

// sleep�� ���� ������� 
#include <windows.h>

#include "stack.h"

#define COL_SIZE 10
#define ROW_SIZE 10

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
				   {1,1,0,1,1,1,1,100,1,1}, 
				   {1,1,0,0,0,0,1,1,1,1}, 
				   {1,1,1,1,1,0,0,0,0,1},
				   {1,1,1,1,1,1,1,1,1,1}} ;
int maze_map_original[10][10] = {{1,1,1,1,1,1,1,1,1,1}, 
							   {1,0,1,1,1,1,1,1,1,1}, 
							   {1,0,0,0,0,0,0,0,1,1}, 
							   {1,1,1,0,1,1,1,1,1,1}, 
							   {1,1,1,0,1,1,1,1,1,1}, 
							   {1,1,0,0,0,0,0,0,0,1}, 
							   {1,1,0,1,1,1,1,100,1,1}, 
							   {1,1,0,0,0,0,1,1,1,1}, 
							   {1,1,1,1,1,0,0,0,0,1},
							   {1,1,1,1,1,1,1,1,1,1}} ;
int dragon_catch = 0; 
int arrival_before_dragon_catch = 0;

// ��� ������ maze_map�� ������ִ� �Լ�
// TODO ���Ͽ��� �Է¹��� ��� �Լ� ������ �����ؾ��� �ʿ伺. 
void print_maze_map(int (*map)[COL_SIZE], int height, int width, int current_row, int current_col){
	int tmp_map[height][width];
	int i,j;
	for(i = 0 ; i < height ; i++){
		for(j = 0 ; j < width; j++){
			tmp_map[i][j] = map[i][j];
			if(i == current_row && j == current_col)tmp_map[i][j] = 77;
			printf("%3d ", tmp_map[i][j]);
		}
		printf("\n");
	}
	
}

// ������ ���� ��ġ�� ������� �̵������� ���Ϲ޴� �Լ� 
int decide_direction(trace current_location){
	int dir = 0;
	
	if(arrival_before_dragon_catch){ 
		while((maze_map[current_location.row + moves[dir].ver][current_location.col + moves[dir].hor] == 1 || maze_map[current_location.row + moves[dir].ver][current_location.col + moves[dir].hor] == 2 || maze_map[current_location.row + moves[dir].ver][current_location.col + moves[dir].hor] == 100) && dir < 4)dir++;
	}
	else{
		while(maze_map[current_location.row + moves[dir].ver][current_location.col + moves[dir].hor] == 1 && dir < 4)dir++;
	}
		
	
	if(dir == 4)return -1;
	else return dir;
} 

int move(trace current_location){
	// ���� ��ġ�κ��� ������ ������ �Ǵ�
	int dir = decide_direction(current_location);
	
	// �������� �� row 
	int next_row = current_location.row+moves[dir].ver;
	// ���� ��ġ�� col 
	int next_col = current_location.col+moves[dir].hor;
	
	
	
	//���̻� ������ ���� ���� ��� 
	//���� pop�� top�� ��ġ�� trace������ �̵� �Ǵ� 
	if(dir == -1){
		if(arrival_before_dragon_catch == 1){
			printf("���� ��ġ�� 2�� ǥ���մϴ�\n");
			maze_map[stack[top].row][stack[top].col] = 2;
		}
		Pop(&top);
		
		printf("�ڷΰ��� : ");
		printf("���� ��ġ: (%d, %d)\n", stack[top].row, stack[top].col); 
		
		// ���� ���� �ʰ� �������� ������ ��� �ڷ� ���鼭 �ش� �ڸ��� 2�� ǥ�� 
		
		
		
		print_maze_map(maze_map_original, 10, 10, stack[top].row, stack[top].col);
		Sleep(300);
		system("cls");
		return -1;
	} 
	//������ ���� �ִ� ���
	//���ÿ� ���� �̵� ��ġ������ push 
	else{
		
		if(arrival_before_dragon_catch == 1){
			printf("arrival_before_dragon_catch�� 0���� �ٲ�\n");
			arrival_before_dragon_catch = 0;	
		} 
		trace new_data = {next_row, next_col,dir};
		Push(&top, new_data);
		
		// �̵� ��ġ 1�� �ٲ��ֱ�
		printf("���� : ");
		printf("���� ��ġ: (%d, %d)\n", stack[top].row, stack[top].col); 
		if(maze_map[next_row][next_col]==99){
			dragon_catch = 1;
			printf("���� ��ҽ��ϴ�\n");
		}
		// �������� ������ ��� 
		if(maze_map[next_row][next_col] == 100){
			// ���� ���� �ʰ� �������� ������ ���
			if(!dragon_catch){
				arrival_before_dragon_catch = 1;
				printf("���� ���� �ʰ� �������� �����߽��ϴ�\n�ǵ��ư��ʽÿ�");
				
				Pop(&top);
				printf("�ڷΰ��� : ");
				printf("���� ��ġ: (%d, %d)\n", stack[top].row, stack[top].col); 
				
				// ���� ���� �ʰ� �������� ������ ��� �ڷ� ���鼭 �ش� �ڸ��� 2�� ǥ�� 
				if(arrival_before_dragon_catch == 1){
					printf("���� ��ġ�� 2�� ǥ���մϴ�\n");
					maze_map[stack[top].row][stack[top].col] = 2;
				} 
				
				print_maze_map(maze_map_original, 10, 10, stack[top].row, stack[top].col);
				Sleep(300);
				system("cls");
				
				return -1;
			} 
			printf("������ ����˴ϴ�\n"); 
			return 0;
		}
		print_maze_map(maze_map_original, 10, 10, stack[top].row, stack[top].col);
		Sleep(300);
		system("cls");
		maze_map[next_row][next_col] = 1; 
		return 1;
	} 
}
#endif
