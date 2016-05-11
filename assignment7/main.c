#include <stdio.h>
#include <stdlib.h>       //srand
#include <time.h>     //time
#include "sort.c"
  
//#define _MAX 6
#define FALSE 0
#define TRUE 1
#define nMAX 60000


void generate_random_number(int* list,int* bCheckExistOfNum,  int number){
	int i;
	for(i = 0 ; i < number ; i++){
		bCheckExistOfNum[i] = 0;
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
        	if(i >= 32767 && bCheckExistOfNum[nTemp + (number-32767)] == FALSE){
        		bCheckExistOfNum[nTemp + (number-32767)] = TRUE;     //번호가 중복 생성되지 않게 존재 여부를 true로 한다.
            	list[i] = nTemp + (number-32767) +1;             //+1을 안해주면 범위가 0~44이다.
          		++i;                                //증감 연산을 for문에서 하지 않고 여기서 한다.
			}
		}
        
    }
}



int main( )
{
    //변수 생성 및 초기화 부분
    srand( (unsigned)time(NULL) );              //srand로 초기화
  
    int randomNum[nMAX];               //생성된 로또 번호를 저장할 변수
    int bCheckExistOfNum[nMAX] = {0};     //생성된 번호가 중복인지 체크할 변수(인덱스)
  	int i;
  	float gap;
   	time_t startTime=0, endTime=0;
    //번호 생성 부분 
    char cmd[10];
    int sort_code = 0;
//    generate_random_number(randomNum, bCheckExistOfNum, nMAX);
//    startTime = clock();
//    insertSort(randomNum, nMAX);
//    endTime = clock();
//  	for(i = 0 ; i < nMAX; i++){
//  		printf("%d ", randomNum[i]);
//	  }
//	printf("\n");
//   	
//   	gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //계산
//	printf("총 걸린 시간 %f\n", gap);
   	
   	
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
            sort_code = 1;
        }
        else if(!strcmp(cmd,"2")){
            printf("선택정렬 선택!\n");
            sort_code = 2;
        }
        else if(!strcmp(cmd,"3")){
            printf("합병정렬 선택!\n");
            sort_code = 3;
        }
        else if(!strcmp(cmd,"4")){
            printf("힙정렬 선택!\n");
            sort_code = 4;
        }
        else if(!strcmp(cmd,"q")) break;
        else{
            printf("올바른 코드를 입력해주세요\n");
            continue;
        }
        
        switch(sort_code){
            case 1:
                printf("난수 10000개 생성\n");
                generate_random_number(randomNum, bCheckExistOfNum, 60000);
                startTime = clock();
    			insertSort(randomNum, 60000);
   				endTime = clock();
				for(i = 0 ; i < 60000; i++){
					printf("%d ", randomNum[i]);
				}
				printf("\n");
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                break;
        }
        
        
    }
   	
    return 0;
}

