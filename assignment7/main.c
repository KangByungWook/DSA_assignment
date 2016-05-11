#include <stdio.h>
#include <stdlib.h>       //srand
#include <time.h>     //time
#include "sort.c"
  
//#define _MAX 6
#define FALSE 0
#define TRUE 1
#define nMAX 20000
  
int main( )
{
    //변수 생성 및 초기화 부분
    srand( (unsigned)time(NULL) );              //srand로 초기화
  
    int nLottoNum[nMAX];               //생성된 로또 번호를 저장할 변수
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
            nLottoNum[i] = nTemp+1;             //+1을 안해주면 범위가 0~44이다.
            ++i;                                //증감 연산을 for문에서 하지 않고 여기서 한다.
        }
    }
    
    for(i = 0 ; i < nMAX; i++){
  		printf("%d ", nLottoNum[i]);
	  }
	  printf("\n");
	startTime = clock();
    bubbleSort(nLottoNum, nMAX);
    endTime = clock();
  	for(i = 0 ; i < nMAX; i++){
  		printf("%d ", nLottoNum[i]);
	  }
	  printf("\n");
   	
   	gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //계산
	printf("총 걸린 시간 %f\n", gap);
   	printf("%d",MAX);
   	
   	
   	
    return 0;
}

void BubbleSort( int *nArr, int nArrSize )
{	
	int i,j;
    for( i=0 ; i<nArrSize-1 ; i++ )
    {
        for( j=0 ; j<nArrSize-(i+1) ; j++ )
        {
            if( nArr[j] > nArr[j+1] )    //꺽쇠 방향으로 오름 차순, 내름 차순 결정
            {//값 교환 부분
                int temp = nArr[j];
                nArr[j] = nArr[j+1];
                nArr[j+1] = temp;
            }
        }
    }
}

