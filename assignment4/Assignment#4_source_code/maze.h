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

// 지나간 곳을 1 또는 2로 바꿀 지도 
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

// maze_map의 복사본, 값이 변하지 않는 지도				   
// 자신의 위치가 표시된 지도를 출력하기 위함 
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

// 용을 잡았는지 알려주는 인덱스
// 디폴트값 0 
// 용을 잡았을때 1로 바뀐다 
int dragon_catch = 0; 

// 헨젤과 그레텔에서 모티프를 얻음
// 용을 잡지 않고 목적지에 도착했을 경우
// 스택에서 push하기 직전까지 pop하면서 현재 위치에 쿠키(2로 표시)를 떨어뜨림  
int cookie = 0;

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
	
	// 쿠키를 떨어뜨리고 있을 떄에는 2(쿠키)와 100(도착점)도 갈 수 없는 곳으로 인식 
	if(cookie){ 
		while((maze_map[current_location.row + moves[dir].ver][current_location.col + moves[dir].hor] == 1 || maze_map[current_location.row + moves[dir].ver][current_location.col + moves[dir].hor] == 2 || maze_map[current_location.row + moves[dir].ver][current_location.col + moves[dir].hor] == 100) && dir < 4)dir++;
	}
	else{
		while(maze_map[current_location.row + moves[dir].ver][current_location.col + moves[dir].hor] == 1 && dir < 4)dir++;
	}
	
	// 더이상 갈 곳이 없는 경우에는 -1리턴	
	if(dir == 4)return -1;
	// 갈 곳이 있는 경우 해당 방향 숫자를 리턴 
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
		// 쿠키를 떨어뜨려야 하는 상황인 경우
		// 즉 용을 잡지 않고 목적지에 도착한 경우에 최초 push까지 pop하는 경우 
		if(cookie == 1){
			maze_map[stack[top].row][stack[top].col] = 2;
		}
		Pop(&top);
		
		
		// 맵을 출력 
		print_maze_map(maze_map_original, 10, 10, stack[top].row, stack[top].col);
		Sleep(300);
		// 콘솔창 클리어 
		system("cls");
		return -1;
	} 
	
	//움직일 곳이 있는 경우
	//스택에 다음 이동 위치정보를 push 
	else{
		
		if(cookie == 1){
			cookie = 0;	
		} 
		trace new_data = {next_row, next_col,dir};
		Push(&top, new_data);
		
		// 이동 위치 1로 바꿔주기
		if(maze_map[next_row][next_col]==99){
			// 드래곤을 죽이고 maze_map_original의 드래곤 위치를 1로 바꿔주기
			maze_map_original[next_row][next_col] = 0; 
			dragon_catch = 1;
			printf("용 : 캬ㅑ아ㅏㄹㅇ남라ㅏ아ㅏㅏㅇ아ㅏ아ㅏ\n");
			Sleep(1000);
			printf("야생의 리자몽(이)가 나타났다!!\n"); 
			Sleep(1000);
			
			int cmd = 0;
			while(cmd != 1){
				printf("-----------------------\n");
				printf("1. 마스터볼을 사용한다\n");
				printf("2. 도망친다.\n");
				printf("-----------------------\n");
				printf("어떻게 하시겠습니까? : ");
				scanf("%d", &cmd);
				switch(cmd){
					
					case 1:
						printf("받아라 마스터볼!!\n");
						Sleep(3000);
						printf("야생의 리자몽(을)를 잡았습니다\n");
						Sleep(3000);
						break;
					case 2:
						printf("리자몽(이)가 역장을 사용했습니다\n");
						Sleep(3000);
						printf("용사 : 이런..빠져나갈수가 없군...\n");
						Sleep(3000);
						break;
					default:
						printf("1과 2중에 선택해주세요.\n");
						break;
				}
			}
			system("cls");
		}
		// 도착지에 도착한 경우 
		if(maze_map[next_row][next_col] == 100){
			// 용을 잡지 않고 목적지에 도착한 경우
			if(!dragon_catch){
				cookie = 1;
				printf("촌장 : 용사여 그대는 아직 용을 잡지 못했는가?\n");
				Sleep(3000);
				printf("용사 : 용...이라니요?\n");
				Sleep(3000);
				printf("촌장 : 이 미로 어딘가에 우리 마을사람들을 괴롭히는 무시무시한 용이 살고 있다네.\n");
				Sleep(3000);
				printf("촌장 : 부디 용을 처리해주게나.\n");
				Sleep(3000);
				printf("용사 : 알겠습니다 촌장님\n");
				Sleep(3000);
				system("cls");
				Pop(&top);
				
				// 용을 잡지 않고 도착지에 도착한 경우 뒤로 가면서 해당 자리에 2를 표시 
				// 
				if(cookie == 1){
					printf("현재 위치에 2를 표시합니다\n");
					maze_map[stack[top].row][stack[top].col] = 2;
				} 
				
				// 자신의 위치가 표시된 지도를 출력 
				print_maze_map(maze_map_original, 10, 10, stack[top].row, stack[top].col);
				Sleep(300);
				system("cls");
				
				return -1;
			} 
			printf("촌장 : 오오 용사여...\n");
			Sleep(2000);
			printf("촌장 : 우리 마을의 골칫덩어리였던 리자몽을 잡아주다니 정말 고맙군...\n");
			Sleep(2000);
			printf("촌장 : 감사의 의미로 사례를 하고 싶은데...\n");
			Sleep(2000);
			printf("용사 : 제가 할일을 했을 뿐입니다.\n");
			Sleep(2000);
			printf("촌장 : 여기서 하루밤만 묵고..\n");
			Sleep(500);
			printf("용사 : 그럼 전 이만...\n");
			Sleep(2000);
			printf("그 후로 용사는 더이상 마을에 나타나지 않았다.\n");
			Sleep(2000);
			printf("들리는 소문에 의하면 세계 최강의 4천왕을 무찌르고 포켓몬 마스터가 되었다고 한다.\n");
			Sleep(2000);
			printf("끝\n");
			return 0;
		}
		
		// 자신의 위치가 표시된 지도 출력 
		print_maze_map(maze_map_original, 10, 10, stack[top].row, stack[top].col);
		Sleep(300);
		system("cls");
		
		// maze_map에서 자신이 이동할 위치에 1을 표시 
		maze_map[next_row][next_col] = 1; 
		return 1;
	} 
}
#endif
