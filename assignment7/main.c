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
	for(i=0 ; i<nMAX ; )                    //번호가 6개 생성될 때까지 돈다.
    {	
    	int nTemp = rand()%nMAX;                  //0~44 범위의 번호를 생성한다.
    	
	    
        if( bCheckExistOfNum[nTemp] == FALSE )  //중복 여부 판단
        {
        	bCheckExistOfNum[nTemp] = TRUE;     //번호가 중복 생성되지 않게 존재 여부를 true로 한다.
            list[i] = nTemp+1;             //+1을 안해주면 범위가 0~44이다.
            ++i;                                //증감 연산을 for문에서 하지 않고 여기서 한다.
        }
        else{
        	if(bCheckExistOfNum[nTemp + (nMAX-32767)] == FALSE){
        		bCheckExistOfNum[nTemp + (nMAX-32767)] = TRUE;     //번호가 중복 생성되지 않게 존재 여부를 true로 한다.
            	list[i] = nTemp + (nMAX-32767) +1;             //+1을 안해주면 범위가 0~44이다.
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
    for(i=0 ; i<nMAX ; )                    //번호가 6개 생성될 때까지 돈다.
    {	
    	int nTemp = rand()%nMAX;                  //0~44 범위의 번호를 생성한다.
    	
	    
        if( bCheckExistOfNum[nTemp] == FALSE )  //중복 여부 판단
        {
        	bCheckExistOfNum[nTemp] = TRUE;     //번호가 중복 생성되지 않게 존재 여부를 true로 한다.
            randomNum[i] = nTemp+1;             //+1을 안해주면 범위가 0~44이다.
            ++i;                                //증감 연산을 for문에서 하지 않고 여기서 한다.
        }
        else{
        	if(bCheckExistOfNum[nTemp + (nMAX-32767)] == FALSE){
        		bCheckExistOfNum[nTemp + (nMAX-32767)] = TRUE;     //번호가 중복 생성되지 않게 존재 여부를 true로 한다.
            	randomNum[i] = nTemp + (nMAX-32767) +1;             //+1을 안해주면 범위가 0~44이다.
          		++i;                                //증감 연산을 for문에서 하지 않고 여기서 한다.
			}
		}
        
    }
    
    for(i = 0 ; i < nMAX; i++){
  		printf("%d ", randomNum[i]);
	  }
	  printf("\n");
	startTime = clock();
    insertSort(randomNum, nMAX);
    endTime = clock();
  	for(i = 0 ; i < nMAX; i++){
  		printf("%d ", randomNum[i]);
	  }
	  printf("\n");
   	
   	gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //계산
	printf("총 걸린 시간 %f\n", gap);
   	printf("%d",MAX);
   	
   	
   	
    return 0;
}

