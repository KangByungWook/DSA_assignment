#include <stdio.h>
#include <stdlib.h>       //srand
#include <time.h>     //time
#include <windows.h>
#include "sort.c"
  
//#define _MAX 6
#define FALSE 0
#define TRUE 1
#define nMAX 60000


// 중복없는 난수를 생성하는 함수
// 저장될 리스트(list)와 중복을 체크하는 리스트(bCheckExistOfNum), 그리고 총 갯수(number)를 매개변수로 받는다 
void generate_random_number(int* list,int* bCheckExistOfNum,  int number){
	int i;
	for(i = 0 ; i < number ; i++){				// list와 bCheckExistOfNum 배열 요소 0으로 초기화 
		bCheckExistOfNum[i] = 0;
		list[i] = 0;
	}
	for(i=0 ; i<number ; )                    //번호가 number개 생성될 때까지 돈다.
    {	
    	int nTemp = rand()%number;                  //0부터 number까지의 번호를 생성한다.
    	
	    
        if( bCheckExistOfNum[nTemp] == FALSE )  //중복 여부 판단
        {
        	bCheckExistOfNum[nTemp] = TRUE;     //번호가 중복 생성되지 않게 존재 여부를 true로 한다.
            list[i] = nTemp+1;
            ++i;                                //증감 연산을 for문에서 하지 않고 여기서 한다.
        }
        else{
        	// 난수가 0부터 32767까지 밖에 생성이 되지 않기 때문에 따로 처리해준다. 
        	if(number > 32767 && bCheckExistOfNum[nTemp + (number-32767 - 1)] == FALSE){	
        		bCheckExistOfNum[nTemp + (number-32767) - 1] = TRUE;     //번호가 중복 생성되지 않게 존재 여부를 true로 한다.
            	list[i] = nTemp + (number-32767);
          		++i;                                //증감 연산을 for문에서 하지 않고 여기서 한다.
			}
		}
        
    }
    for(i = 0 ; i < number; i++){				// 생성된 난수를 출력한다. 
    	printf("%d ", list[i]);
	}
}

// 정해진 정렬을 수행하고 수행 시간을 리턴해주는 함수 
float do_sort(int sort_code, int* randomNum, int* bCheckExistOfNum,  int number){
	time_t startTime,endTime;	// 함수 수행 시작시간, 종료시간 
	int i; 
	float gap;					// 총 함수 수행시간 
	switch(sort_code){			// 정렬 코드에 따라서 다른 정렬을 수행한다 
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
			selectionSort(randomNum, number);		// 선택 정렬 실행. 
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
		// 합병 정렬의 경우	
		case 3:
			printf("난수 %d개를 생성 중입니다...\n", number);
			Sleep(3000);
            generate_random_number(randomNum, bCheckExistOfNum, number);
            printf("\n난수가 %d개 생성되었습니다.\n", number);
            Sleep(3000);
            printf("정렬 알고리즘을 시작합니다..\n");
            startTime = clock();
			mergeSort(randomNum, 0, number);			// 합병 정렬 실행. 
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
		// 힙 정렬의 경우	
		case 4:
			printf("난수 %d개를 생성 중입니다...\n", number);
			Sleep(3000);
            generate_random_number(randomNum, bCheckExistOfNum, number);
            printf("\n난수가 %d개 생성되었습니다.\n", number);
            Sleep(3000);
            printf("정렬 알고리즘을 시작합니다..\n");
            startTime = clock();
			Heap_Sort(randomNum, number);			// 힙 정렬 실행. 
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
    srand( (unsigned)time(NULL) );              //srand로 초기화
  	
    int randomNum[nMAX];              		 //생성된 난수를 저장할 변수
    int bCheckExistOfNum[nMAX] = {0};    	 //생성된 난수가 중복인지 체크할 변수(인덱스)
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
        // 삽입 정렬의 경우 
        if(!strcmp(cmd,"1")){
            printf("삽입정렬 선택!\n");
            strcpy(sorting_name, "삽입정렬");
            sort_code = 1;
        }
        // 선택 정렬의 경우 
        else if(!strcmp(cmd,"2")){
            printf("선택정렬 선택!\n");
            strcpy(sorting_name, "선택정렬");
            sort_code = 2;
        }
        // 합병 정렬의 경우 
        else if(!strcmp(cmd,"3")){
            printf("합병정렬 선택!\n");
            strcpy(sorting_name, "합병정렬");
            sort_code = 3;
        }
        // 힙 정렬의 경우 
        else if(!strcmp(cmd,"4")){
            printf("힙정렬 선택!\n");
            strcpy(sorting_name, "힙정렬");
            sort_code = 4;
        }
        else if(!strcmp(cmd,"q")) break;			// q를 입력하면 종료 
        else{
            printf("올바른 코드를 입력해주세요\n");
            continue;
        }
        
        // 각각 10000개, 20000개, 30000개, 40000개, 50000개, 60000개인 경우를 실행한다.  
        for(i = 0 ; i< 6; i++){
        	gap_result_list[i] = do_sort(sort_code, randomNum, bCheckExistOfNum, (i+1)*10000);
		}
        
        // 실험 결과를 출력한다. 
        system("cls");			// 커맨드 창 클리어 
        printf("-----------%s 실험 결과--------------\n",sorting_name);
        for(i = 0 ; i < 6 ; i++){
        	printf("%d개 정렬 수행 시간 : %f초\n", (i+1)*10000, gap_result_list[i]);
        }
        printf("---------------------------------------\n");
        
        
    }
   	
    return 0;
}

