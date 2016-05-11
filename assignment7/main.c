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
    //���� ���� �� �ʱ�ȭ �κ�
    srand( (unsigned)time(NULL) );              //srand�� �ʱ�ȭ
  
    int nLottoNum[nMAX];               //������ �ζ� ��ȣ�� ������ ����
    int bCheckExistOfNum[nMAX] = {0};     //������ ��ȣ�� �ߺ����� üũ�� ����(�ε���)
  	int i;
  	float gap;
   	time_t startTime=0, endTime=0;
    //��ȣ ���� �κ� 
    for(i=0 ; i<nMAX ; )                    //��ȣ�� 6�� ������ ������ ����.
    {
        int nTemp = rand()%nMAX;                  //0~44 ������ ��ȣ�� �����Ѵ�.
  
        if( bCheckExistOfNum[nTemp] == FALSE )  //�ߺ� ���� �Ǵ�
        {
            bCheckExistOfNum[nTemp] = TRUE;     //��ȣ�� �ߺ� �������� �ʰ� ���� ���θ� true�� �Ѵ�.
            nLottoNum[i] = nTemp+1;             //+1�� �����ָ� ������ 0~44�̴�.
            ++i;                                //���� ������ for������ ���� �ʰ� ���⼭ �Ѵ�.
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
   	
   	gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //���
	printf("�� �ɸ� �ð� %f\n", gap);
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
            if( nArr[j] > nArr[j+1] )    //���� �������� ���� ����, ���� ���� ����
            {//�� ��ȯ �κ�
                int temp = nArr[j];
                nArr[j] = nArr[j+1];
                nArr[j+1] = temp;
            }
        }
    }
}

