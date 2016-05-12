#include <stdio.h>
#include <stdlib.h>       //srand
#include <time.h>     //time
#include <windows.h>
#include "sort.c"
  
//#define _MAX 6
#define FALSE 0
#define TRUE 1
#define nMAX 60000



void generate_random_number(int* list,int* bCheckExistOfNum,  int number){
	int i;
	for(i = 0 ; i < number ; i++){
		bCheckExistOfNum[i] = 0;
		list[i] = 0;
	}
	for(i=0 ; i<number ; )                    //번호가 6개 생성될 때까지 돈다.
    {	
    	int nTemp = rand()%number;                  //0~44 범위의 번호를 생성한다.
    	
	    
        if( bCheckExistOfNum[nTemp] == FALSE )  //중복 여부 판단
        {
        	bCheckExistOfNum[nTemp] = TRUE;     //번호가 중복 생성되지 않게 존재 여부를 true로 한다.
            list[i] = nTemp+1;             //+1을 안해주면 범위가 0~44이다.
            ++i;                                //증감 연산을 for문에서 하지 않고 여기서 한다.
        }
        else{
        	if(number > 32767 && bCheckExistOfNum[nTemp + (number-32767 - 1)] == FALSE){
        		bCheckExistOfNum[nTemp + (number-32767) - 1] = TRUE;     //번호가 중복 생성되지 않게 존재 여부를 true로 한다.
            	list[i] = nTemp + (number-32767);             //+1을 안해주면 범위가 0~44이다.
          		++i;                                //증감 연산을 for문에서 하지 않고 여기서 한다.
			}
		}
        
    }
    for(i = 0 ; i < number; i++){
    	printf("%d ", list[i]);
	}
}

float do_sort(int sort_code, int* randomNum, int* bCheckExistOfNum,  int number){
	time_t startTime,endTime;
	int i; 
	float gap;
	switch(sort_code){
		//삽입 정렬의 경우 
		case 1:
			printf("난수 %d개를 생성 중입니다...\n", number);
			Sleep(3000);
            generate_random_number(randomNum, bCheckExistOfNum, number);
            printf("\n난수가 %d개 생성되었습니다.\n", number);
            Sleep(3000);
            printf("정렬 알고리즘을 시작합니다..\n");
            startTime = clock();
			insertSort(randomNum, number);
			endTime = clock();
			printf("정렬 알고리즘이 완료되었습니다.\n");
			gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //계산
			printf("총 수행 시간 : %f초\n", gap);
			Sleep(3000);
			printf("정렬된 결과를 출력합니다.\n");
			Sleep(3000);
			for(i = 0 ; i < number ; i++){
				printf("%d ", randomNum[i]);
			}
			printf("\n정렬이 완료되었습니다.\n");
			Sleep(3000); 
			return gap;
		// 선택 정렬의 경우 
		case 2:
			printf("난수 %d개를 생성 중입니다...\n", number);
			Sleep(3000);
            generate_random_number(randomNum, bCheckExistOfNum, number);
            printf("\n난수가 %d개 생성되었습니다.\n", number);
            Sleep(3000);
            printf("정렬 알고리즘을 시작합니다..\n");
            startTime = clock();
			selectionSort(randomNum, number);
			endTime = clock();
			printf("정렬 알고리즘이 완료되었습니다.\n");
			gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //계산
			printf("총 수행 시간 : %f초\n", gap);
			Sleep(3000);
			printf("정렬된 결과를 출력합니다.\n");
			Sleep(3000);
			for(i = 0 ; i < number ; i++){
				printf("%d ", randomNum[i]);
			}
			printf("\n정렬이 완료되었습니다.\n");
			Sleep(3000); 
			return gap;
			
		case 3:
			printf("난수 %d개를 생성 중입니다...\n", number);
			Sleep(3000);
            generate_random_number(randomNum, bCheckExistOfNum, number);
            printf("\n난수가 %d개 생성되었습니다.\n", number);
            Sleep(3000);
            printf("정렬 알고리즘을 시작합니다..\n");
            startTime = clock();
			mergeSort(randomNum, 0, number);
			endTime = clock();
			printf("정렬 알고리즘이 완료되었습니다.\n");
			gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //계산
			printf("총 수행 시간 : %f초\n", gap);
			Sleep(3000);
			printf("정렬된 결과를 출력합니다.\n");
			Sleep(3000);
			for(i = 0 ; i < number ; i++){
				printf("%d ", randomNum[i]);
			}
			printf("\n정렬이 완료되었습니다.\n");
			Sleep(3000); 
			return gap;
			
		case 4:
			printf("난수 %d개를 생성 중입니다...\n", number);
			Sleep(3000);
            generate_random_number(randomNum, bCheckExistOfNum, number);
            printf("\n난수가 %d개 생성되었습니다.\n", number);
            Sleep(3000);
            printf("정렬 알고리즘을 시작합니다..\n");
            startTime = clock();
			Heap_Sort(randomNum, number);
			endTime = clock();
			printf("정렬 알고리즘이 완료되었습니다.\n");
			gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //계산
			printf("총 수행 시간 : %f초\n", gap);
			Sleep(3000);
			printf("정렬된 결과를 출력합니다.\n");
			Sleep(3000);
			for(i = 0 ; i < number ; i++){
				printf("%d ", randomNum[i]);
			}
			printf("\n정렬이 완료되었습니다.\n");
			Sleep(3000); 
			return gap;
	}
}



int main( )
{
    //변수 생성 및 초기화 부분
    srand( (unsigned)time(NULL) );              //srand로 초기화
  	
    int randomNum[nMAX];               //생성된 로또 번호를 저장할 변수
    int bCheckExistOfNum[nMAX] = {0};     //생성된 번호가 중복인지 체크할 변수(인덱스)
    int i,j;
    
  	float gap;
  	float gap_result_list[6];
  	float max_gap = 0;
   	time_t startTime=0, endTime=0;
    //번호 생성 부분 
    char cmd[10], sorting_name[20];
    int sort_code = 0;
   	
   	while(1){
        printf("1. 삽입정렬\n");
        printf("2. 선택정렬\n");
        printf("3. 합병정렬\n");
        printf("4. 힙 정렬\n");
        printf("q : 종료\n");
        printf("무엇을 하시겠습니까? : ");
        scanf("%s", cmd);
        if(!strcmp(cmd,"1")){
            printf("삽입정렬 선택!\n");
            strcpy(sorting_name, "삽입정렬");
            sort_code = 1;
        }
        else if(!strcmp(cmd,"2")){
            printf("선택정렬 선택!\n");
            strcpy(sorting_name, "선택정렬");
            sort_code = 2;
        }
        else if(!strcmp(cmd,"3")){
            printf("합병정렬 선택!\n");
            strcpy(sorting_name, "합병정렬");
            sort_code = 3;
        }
        else if(!strcmp(cmd,"4")){
            printf("힙정렬 선택!\n");
            strcpy(sorting_name, "힙정렬");
            sort_code = 4;
        }
        else if(!strcmp(cmd,"q")) break;
        else{
            printf("올바른 코드를 입력해주세요\n");
            continue;
        }
        
        for(i = 0 ; i< 6; i++){
        	gap_result_list[i] = do_sort(sort_code, randomNum, bCheckExistOfNum, (i+1)*10000);
		}
        
        system("cls");
        printf("-----------%s 실험 결과--------------\n",sorting_name);
        for(i = 0 ; i < 6 ; i++){
        	printf("%d개 정렬 수행 시간 : %f초\n", (i+1)*10000, gap_result_list[i]);
        }
        printf("---------------------------------------\n");
        
        
    }
   	
    return 0;
}

