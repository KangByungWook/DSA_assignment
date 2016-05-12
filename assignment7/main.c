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
	for(i=0 ; i<number ; )                    //��ȣ�� 6�� ������ ������ ����.
    {	
    	int nTemp = rand()%number;                  //0~44 ������ ��ȣ�� �����Ѵ�.
    	
	    
        if( bCheckExistOfNum[nTemp] == FALSE )  //�ߺ� ���� �Ǵ�
        {
        	bCheckExistOfNum[nTemp] = TRUE;     //��ȣ�� �ߺ� �������� �ʰ� ���� ���θ� true�� �Ѵ�.
            list[i] = nTemp+1;             //+1�� �����ָ� ������ 0~44�̴�.
            ++i;                                //���� ������ for������ ���� �ʰ� ���⼭ �Ѵ�.
        }
        else{
        	if(number > 32767 && bCheckExistOfNum[nTemp + (number-32767 - 1)] == FALSE){
        		bCheckExistOfNum[nTemp + (number-32767) - 1] = TRUE;     //��ȣ�� �ߺ� �������� �ʰ� ���� ���θ� true�� �Ѵ�.
            	list[i] = nTemp + (number-32767);             //+1�� �����ָ� ������ 0~44�̴�.
          		++i;                                //���� ������ for������ ���� �ʰ� ���⼭ �Ѵ�.
			}
		}
        
    }
}

void do_sort(int sort_code, int* randomNum, int* bCheckExistOfNum,  int number, HeapType *Heap_ptr){
	time_t startTime,endTime;
	int i; 
	float gap;
	switch(sort_code){
		//���� ������ ��� 
		case 1:
			printf("���� %d�� ����\n", number);
            generate_random_number(randomNum, bCheckExistOfNum, number);
            startTime = clock();
			insertSort(randomNum, number);
			endTime = clock();
			for(i = 0 ; i < number; i++){
				if(i >= 1 && randomNum[i] - randomNum[i-1] != 1)printf("�̻��� �κ� �߰� %d��° ���� %d & %d��° ���� %d", i , randomNum[i], i-1, randomNum[i-1] );
				if(i >= 1 && randomNum[i] - randomNum[i-1] == 0)printf("�ߺ��߻� %d��° ���� %d & %d��° ���� %d\n", i , randomNum[i], i-1, randomNum[i-1]);
			}
			if(randomNum[0] != 1)printf("0��° ���ڰ� 1�� �ƴ�\n");
			printf("\n");
		   	gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //���
			printf("�� �ɸ� �ð� %f\n", gap);
			Sleep(3000);
			break;
		// ���� ������ ��� 
		case 2:
			printf("���� %d�� ����\n", number);
            generate_random_number(randomNum, bCheckExistOfNum, number);
            startTime = clock();
			selectionSort(randomNum, number);
			endTime = clock();
			for(i = 0 ; i < number; i++){
				printf("%d ", randomNum[i]);
			}
			printf("\n");
			gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //���
			printf("�� �ɸ� �ð� %f\n", gap);
			Sleep(3000);
			break;
		case 3:
			printf("���� %d�� ����\n", number);
            generate_random_number(randomNum, bCheckExistOfNum, number);
            startTime = clock();
			mergeSort(randomNum, 0, number);
			endTime = clock();
			for(i = 0 ; i < number; i++){
				printf("%d ", randomNum[i]);
			}
			printf("\n");
			gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //���
			printf("�� �ɸ� �ð� %f\n", gap);
			Sleep(3000);
			break;
		case 4:
			printf("���� %d�� ����\n", number);
            generate_random_number(randomNum, bCheckExistOfNum, number);
            startTime = clock();
            Heap_Sort(randomNum, 0);
			endTime = clock();
			
			for(i = 0 ; i < number; i++){
				printf("%d ", randomNum[i]);
			}
			printf("\n");
			gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //���
			printf("�� �ɸ� �ð� %f\n", gap);
			Sleep(3000);
			break;
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
    char cmd[10];
    int sort_code = 0;
    HeapType *Heap_ptr = (HeapType*)malloc(sizeof(HeapType));
//    generate_random_number(randomNum, bCheckExistOfNum, nMAX);
//    startTime = clock();
//    insertSort(randomNum, nMAX);
//    endTime = clock();
//  	for(i = 0 ; i < nMAX; i++){
//  		printf("%d ", randomNum[i]);
//	  }
//	printf("\n");
//   	

   	
   	
   	while(1){
        printf("1. ��������\n");
        printf("2. ��������\n");
        printf("3. �պ�����\n");
        printf("4. �� ����\n");
        printf("q : ����\n");
        printf("������ �Ͻðڽ��ϱ�? : ");
        scanf("%s", cmd);
        if(!strcmp(cmd,"1")){
            printf("�������� ����!\n");
            sort_code = 1;
        }
        else if(!strcmp(cmd,"2")){
            printf("�������� ����!\n");
            sort_code = 2;
        }
        else if(!strcmp(cmd,"3")){
            printf("�պ����� ����!\n");
            sort_code = 3;
        }
        else if(!strcmp(cmd,"4")){
            printf("������ ����!\n");
            sort_code = 4;
        }
        else if(!strcmp(cmd,"q")) break;
        else{
            printf("�ùٸ� �ڵ带 �Է����ּ���\n");
            continue;
        }
        
        //do_sort(sort_code, randomNum, bCheckExistOfNum, 10000, Heap_ptr);
        //do_sort(sort_code, randomNum, bCheckExistOfNum, 20000, Heap_ptr);
        //do_sort(sort_code, randomNum, bCheckExistOfNum, 30000, Heap_ptr);
        do_sort(sort_code, randomNum, bCheckExistOfNum, 40000, Heap_ptr);
        //do_sort(sort_code, randomNum, bCheckExistOfNum, 50000, Heap_ptr);
        // do_sort(sort_code, randomNum, bCheckExistOfNum, 60000, Heap_ptr);
        
        
        
        
        
    }
   	
    return 0;
}

