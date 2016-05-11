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
	for(i=0 ; i<nMAX ; )                    //��ȣ�� 6�� ������ ������ ����.
    {	
    	int nTemp = rand()%nMAX;                  //0~44 ������ ��ȣ�� �����Ѵ�.
    	
	    
        if( bCheckExistOfNum[nTemp] == FALSE )  //�ߺ� ���� �Ǵ�
        {
        	bCheckExistOfNum[nTemp] = TRUE;     //��ȣ�� �ߺ� �������� �ʰ� ���� ���θ� true�� �Ѵ�.
            list[i] = nTemp+1;             //+1�� �����ָ� ������ 0~44�̴�.
            ++i;                                //���� ������ for������ ���� �ʰ� ���⼭ �Ѵ�.
        }
        else{
        	if(bCheckExistOfNum[nTemp + (nMAX-32767)] == FALSE){
        		bCheckExistOfNum[nTemp + (nMAX-32767)] = TRUE;     //��ȣ�� �ߺ� �������� �ʰ� ���� ���θ� true�� �Ѵ�.
            	list[i] = nTemp + (nMAX-32767) +1;             //+1�� �����ָ� ������ 0~44�̴�.
          		++i;                                //���� ������ for������ ���� �ʰ� ���⼭ �Ѵ�.
			}
		}
        
    }
}

int main( )
{
    //���� ���� �� �ʱ�ȭ �κ�
    srand( (unsigned)time(NULL) );              //srand�� �ʱ�ȭ
  
    int randomNum[nMAX];               //������ �ζ� ��ȣ�� ������ ����
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
            randomNum[i] = nTemp+1;             //+1�� �����ָ� ������ 0~44�̴�.
            ++i;                                //���� ������ for������ ���� �ʰ� ���⼭ �Ѵ�.
        }
        else{
        	if(bCheckExistOfNum[nTemp + (nMAX-32767)] == FALSE){
        		bCheckExistOfNum[nTemp + (nMAX-32767)] = TRUE;     //��ȣ�� �ߺ� �������� �ʰ� ���� ���θ� true�� �Ѵ�.
            	randomNum[i] = nTemp + (nMAX-32767) +1;             //+1�� �����ָ� ������ 0~44�̴�.
          		++i;                                //���� ������ for������ ���� �ʰ� ���⼭ �Ѵ�.
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
   	
   	gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //���
	printf("�� �ɸ� �ð� %f\n", gap);
   	printf("%d",MAX);
   	
   	
   	
    return 0;
}

