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

// ������ ���� 1 �Ǵ� 2�� �ٲ� ���� 
int maze_map[10][10] = {{1,1,1,1,1,1,1,1,1,1}, 
				   {1,1,1,1,1,1,1,1,1,1}, 
				   {1,1,1,1,1,1,1,1,1,1}, 
				   {1,1,1,1,1,1,1,1,1,1}, 
				   {1,1,1,1,1,1,1,1,1,1}, 
				   {1,1,1,1,1,1,1,1,1,1}, 
				   {1,1,1,1,1,1,1,1,1,1}, 
				   {1,1,1,1,1,1,1,1,1,1}, 
				   {1,1,1,1,1,1,1,1,1,1},
				   {1,1,1,1,1,1,1,1,1,1}} ;

// maze_map�� ���纻, ���� ������ �ʴ� ����				   
// �ڽ��� ��ġ�� ǥ�õ� ������ ����ϱ� ���� 
int maze_map_original[10][10] = {{1,1,1,1,1,1,1,1,1,1}, 
				   {1,1,1,1,1,1,1,1,1,1}, 
				   {1,1,1,1,1,1,1,1,1,1}, 
				   {1,1,1,1,1,1,1,1,1,1}, 
				   {1,1,1,1,1,1,1,1,1,1}, 
				   {1,1,1,1,1,1,1,1,1,1}, 
				   {1,1,1,1,1,1,1,1,1,1}, 
				   {1,1,1,1,1,1,1,1,1,1}, 
				   {1,1,1,1,1,1,1,1,1,1},
				   {1,1,1,1,1,1,1,1,1,1}} ;
void initialize_map(){
	FILE *fp = fopen("map.txt", "r");

	int tmp,i,j;
	
	for(i = 0; i < 8; i++){
		for(j = 0 ; j < 8; j++){
			fscanf(fp, "%d", &tmp);	
			maze_map[i+1][j+1] = tmp;
			maze_map_original[i+1][j+1] = tmp;
		}
	}
	fclose(fp);	
}						   

// ���� ��Ҵ��� �˷��ִ� �ε���
// ����Ʈ�� 0 
// ���� ������� 1�� �ٲ�� 
int dragon_catch = 0; 

// ������ �׷��ڿ��� ��Ƽ���� ����
// ���� ���� �ʰ� �������� �������� ���
// ���ÿ��� push�ϱ� �������� pop�ϸ鼭 ���� ��ġ�� ��Ű(2�� ǥ��)�� ����߸�  
int cookie = 0;

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
	
	// ��Ű�� ����߸��� ���� ������ 2(��Ű)�� 100(������)�� �� �� ���� ������ �ν� 
	if(cookie){ 
		while((maze_map[current_location.row + moves[dir].ver][current_location.col + moves[dir].hor] == 1 || maze_map[current_location.row + moves[dir].ver][current_location.col + moves[dir].hor] == 2 || maze_map[current_location.row + moves[dir].ver][current_location.col + moves[dir].hor] == 100) && dir < 4)dir++;
	}
	else{
		while(maze_map[current_location.row + moves[dir].ver][current_location.col + moves[dir].hor] == 1 && dir < 4)dir++;
	}
	
	// ���̻� �� ���� ���� ��쿡�� -1����	
	if(dir == 4)return -1;
	// �� ���� �ִ� ��� �ش� ���� ���ڸ� ���� 
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
		// ��Ű�� ����߷��� �ϴ� ��Ȳ�� ���
		// �� ���� ���� �ʰ� �������� ������ ��쿡 ���� push���� pop�ϴ� ��� 
		if(cookie == 1){
			maze_map[stack[top].row][stack[top].col] = 2;
		}
		Pop(&top);
		
		
		// ���� ��� 
		print_maze_map(maze_map_original, 10, 10, stack[top].row, stack[top].col);
		Sleep(300);
		// �ܼ�â Ŭ���� 
		system("cls");
		return -1;
	} 
	
	//������ ���� �ִ� ���
	//���ÿ� ���� �̵� ��ġ������ push 
	else{
		
		if(cookie == 1){
			cookie = 0;	
		} 
		trace new_data = {next_row, next_col,dir};
		Push(&top, new_data);
		
		// �̵� ��ġ 1�� �ٲ��ֱ�
		if(maze_map[next_row][next_col]==99){
			// �巡���� ���̰� maze_map_original�� �巡�� ��ġ�� 1�� �ٲ��ֱ�
			maze_map_original[next_row][next_col] = 0; 
			dragon_catch = 1;
			printf("�� : ļ���Ƥ��������󤿾Ƥ������Ƥ��Ƥ�\n");
			Sleep(1000);
			printf("�߻��� ���ڸ�(��)�� ��Ÿ����!!\n"); 
			Sleep(1000);
			
			int cmd = 0;
			while(cmd != 1){
				printf("-----------------------\n");
				printf("1. �����ͺ��� ����Ѵ�\n");
				printf("2. ����ģ��.\n");
				printf("-----------------------\n");
				printf("��� �Ͻðڽ��ϱ�? : ");
				scanf("%d", &cmd);
				switch(cmd){
					
					case 1:
						printf("�޾ƶ� �����ͺ�!!\n");
						Sleep(3000);
						printf("�߻��� ���ڸ�(��)�� ��ҽ��ϴ�\n");
						Sleep(3000);
						break;
					case 2:
						printf("���ڸ�(��)�� ������ ����߽��ϴ�\n");
						Sleep(3000);
						printf("��� : �̷�..������������ ����...\n");
						Sleep(3000);
						break;
					default:
						printf("1�� 2�߿� �������ּ���.\n");
						break;
				}
			}
			system("cls");
		}
		// �������� ������ ��� 
		if(maze_map[next_row][next_col] == 100){
			// ���� ���� �ʰ� �������� ������ ���
			if(!dragon_catch){
				cookie = 1;
				printf("���� : ��翩 �״�� ���� ���� ���� ���ߴ°�?\n");
				Sleep(3000);
				printf("��� : ��...�̶�Ͽ�?\n");
				Sleep(3000);
				printf("���� : �� �̷� ��򰡿� �츮 ����������� �������� ���ù����� ���� ��� �ִٳ�.\n");
				Sleep(3000);
				printf("���� : �ε� ���� ó�����ְԳ�.\n");
				Sleep(3000);
				printf("��� : �˰ڽ��ϴ� �����\n");
				Sleep(3000);
				system("cls");
				Pop(&top);
				
				// ���� ���� �ʰ� �������� ������ ��� �ڷ� ���鼭 �ش� �ڸ��� 2�� ǥ�� 
				// 
				if(cookie == 1){
					printf("���� ��ġ�� 2�� ǥ���մϴ�\n");
					maze_map[stack[top].row][stack[top].col] = 2;
				} 
				
				// �ڽ��� ��ġ�� ǥ�õ� ������ ��� 
				print_maze_map(maze_map_original, 10, 10, stack[top].row, stack[top].col);
				Sleep(300);
				system("cls");
				
				return -1;
			} 
			printf("���� : ���� ��翩...\n");
			Sleep(2000);
			printf("���� : �츮 ������ ��ĩ������� ���ڸ��� ����ִٴ� ���� ����...\n");
			Sleep(2000);
			printf("���� : ������ �ǹ̷� ��ʸ� �ϰ� ������...\n");
			Sleep(2000);
			printf("��� : ���� ������ ���� ���Դϴ�.\n");
			Sleep(2000);
			printf("���� : ���⼭ �Ϸ�㸸 ����..\n");
			Sleep(500);
			printf("��� : �׷� �� �̸�...\n");
			Sleep(2000);
			printf("�� �ķ� ���� ���̻� ������ ��Ÿ���� �ʾҴ�.\n");
			Sleep(2000);
			printf("�鸮�� �ҹ��� ���ϸ� ���� �ְ��� 4õ���� ����� ���ϸ� �����Ͱ� �Ǿ��ٰ� �Ѵ�.\n");
			Sleep(2000);
			printf("��\n");
			return 0;
		}
		
		// �ڽ��� ��ġ�� ǥ�õ� ���� ��� 
		print_maze_map(maze_map_original, 10, 10, stack[top].row, stack[top].col);
		Sleep(300);
		system("cls");
		
		// maze_map���� �ڽ��� �̵��� ��ġ�� 1�� ǥ�� 
		maze_map[next_row][next_col] = 1; 
		return 1;
	} 
}
#endif
