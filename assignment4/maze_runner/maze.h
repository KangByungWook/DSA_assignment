#ifndef maze_h
#define maze_h

#include <stdio.h>
#include <stdlib.h>

// sleep를 위한 헤더파일 
#include <windows.h>

#include "stack.h"

#define COL_SIZE 10
#define ROW_SIZE 10

// 이동시 좌표 변화 정보가 담긴 데이터 타입
// 예를들어 북쪽으로 이동하는 경우 ver = -1, hor = 0; 
typedef struct offset{
	int ver;
	int hor;
}offset;



// 동,서,남,북 네가지 이동방향을 offset 행렬로 만듬
// offset 행렬 요소의 인덱스는 움직임의 우선순위를 의미
// 북 -> 동 -> 남 -> 서 순서로 우선순위 적용
offset moves[4] = {{-1, 0}, {0 , 1}, {1, 0}, {0, -1}};

// 기본 지도값
// TODO 파일로부터 지도값 읽어오기. 
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

// 헤더 파일의 maze_map을 출력해주는 함수
// TODO 파일에서 입력받을 경우 함수 구조를 변경해야할 필요성. 
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

// 지도와 현재 위치를 기반으로 이동방향을 리턴받는 함수 
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
	// 현재 위치로부터 움직일 방향을 판단
	int dir = decide_direction(current_location);
	
	// 다음으로 갈 row 
	int next_row = current_location.row+moves[dir].ver;
	// 다음 위치의 col 
	int next_col = current_location.col+moves[dir].hor;
	
	
	
	//더이상 움직일 곳이 없는 경우 
	//스택 pop후 top에 위치한 trace정보로 이동 판단 
	if(dir == -1){
		if(arrival_before_dragon_catch == 1){
			printf("현재 위치에 2를 표시합니다\n");
			maze_map[stack[top].row][stack[top].col] = 2;
		}
		Pop(&top);
		
		printf("뒤로가기 : ");
		printf("현재 위치: (%d, %d)\n", stack[top].row, stack[top].col); 
		
		// 용을 잡지 않고 도착지에 도착한 경우 뒤로 가면서 해당 자리에 2를 표시 
		
		
		
		print_maze_map(maze_map_original, 10, 10, stack[top].row, stack[top].col);
		Sleep(300);
		system("cls");
		return -1;
	} 
	//움직일 곳이 있는 경우
	//스택에 다음 이동 위치정보를 push 
	else{
		
		if(arrival_before_dragon_catch == 1){
			printf("arrival_before_dragon_catch를 0으로 바꿈\n");
			arrival_before_dragon_catch = 0;	
		} 
		trace new_data = {next_row, next_col,dir};
		Push(&top, new_data);
		
		// 이동 위치 1로 바꿔주기
		printf("전진 : ");
		printf("현재 위치: (%d, %d)\n", stack[top].row, stack[top].col); 
		if(maze_map[next_row][next_col]==99){
			dragon_catch = 1;
			printf("용을 잡았습니다\n");
		}
		// 도착지에 도착한 경우 
		if(maze_map[next_row][next_col] == 100){
			// 용을 잡지 않고 목적지에 도착한 경우
			if(!dragon_catch){
				arrival_before_dragon_catch = 1;
				printf("용을 잡지 않고 목적지에 도착했습니다\n되돌아가십시오");
				
				Pop(&top);
				printf("뒤로가기 : ");
				printf("현재 위치: (%d, %d)\n", stack[top].row, stack[top].col); 
				
				// 용을 잡지 않고 도착지에 도착한 경우 뒤로 가면서 해당 자리에 2를 표시 
				if(arrival_before_dragon_catch == 1){
					printf("현재 위치에 2를 표시합니다\n");
					maze_map[stack[top].row][stack[top].col] = 2;
				} 
				
				print_maze_map(maze_map_original, 10, 10, stack[top].row, stack[top].col);
				Sleep(300);
				system("cls");
				
				return -1;
			} 
			printf("게임이 종료됩니다\n"); 
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
