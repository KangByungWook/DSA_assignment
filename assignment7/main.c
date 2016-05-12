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
    for(i = 0 ; i < number; i++){
    	printf("%d ", list[i]);
	}
}

float do_sort(int sort_code, int* randomNum, int* bCheckExistOfNum,  int number){
	time_t startTime,endTime;
	int i; 
	float gap;
	switch(sort_code){
		//���� ������ ��� 
		case 1:
			printf("���� %d���� ���� ���Դϴ�...\n", number);
			Sleep(3000);
            generate_random_number(randomNum, bCheckExistOfNum, number);
            printf("\n������ %d�� �����Ǿ����ϴ�.\n", number);
            Sleep(3000);
            printf("���� �˰����� �����մϴ�..\n");
            startTime = clock();
			insertSort(randomNum, number);
			endTime = clock();
			printf("���� �˰����� �Ϸ�Ǿ����ϴ�.\n");
			gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //���
			printf("�� ���� �ð� : %f��\n", gap);
			Sleep(3000);
			printf("���ĵ� ����� ����մϴ�.\n");
			Sleep(3000);
			for(i = 0 ; i < number ; i++){
				printf("%d ", randomNum[i]);
			}
			printf("\n������ �Ϸ�Ǿ����ϴ�.\n");
			Sleep(3000); 
			return gap;
		// ���� ������ ��� 
		case 2:
			printf("���� %d���� ���� ���Դϴ�...\n", number);
			Sleep(3000);
            generate_random_number(randomNum, bCheckExistOfNum, number);
            printf("\n������ %d�� �����Ǿ����ϴ�.\n", number);
            Sleep(3000);
            printf("���� �˰����� �����մϴ�..\n");
            startTime = clock();
			selectionSort(randomNum, number);
			endTime = clock();
			printf("���� �˰����� �Ϸ�Ǿ����ϴ�.\n");
			gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //���
			printf("�� ���� �ð� : %f��\n", gap);
			Sleep(3000);
			printf("���ĵ� ����� ����մϴ�.\n");
			Sleep(3000);
			for(i = 0 ; i < number ; i++){
				printf("%d ", randomNum[i]);
			}
			printf("\n������ �Ϸ�Ǿ����ϴ�.\n");
			Sleep(3000); 
			return gap;
			
		case 3:
			printf("���� %d���� ���� ���Դϴ�...\n", number);
			Sleep(3000);
            generate_random_number(randomNum, bCheckExistOfNum, number);
            printf("\n������ %d�� �����Ǿ����ϴ�.\n", number);
            Sleep(3000);
            printf("���� �˰����� �����մϴ�..\n");
            startTime = clock();
			mergeSort(randomNum, 0, number);
			endTime = clock();
			printf("���� �˰����� �Ϸ�Ǿ����ϴ�.\n");
			gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //���
			printf("�� ���� �ð� : %f��\n", gap);
			Sleep(3000);
			printf("���ĵ� ����� ����մϴ�.\n");
			Sleep(3000);
			for(i = 0 ; i < number ; i++){
				printf("%d ", randomNum[i]);
			}
			printf("\n������ �Ϸ�Ǿ����ϴ�.\n");
			Sleep(3000); 
			return gap;
			
		case 4:
			printf("���� %d���� ���� ���Դϴ�...\n", number);
			Sleep(3000);
            generate_random_number(randomNum, bCheckExistOfNum, number);
            printf("\n������ %d�� �����Ǿ����ϴ�.\n", number);
            Sleep(3000);
            printf("���� �˰����� �����մϴ�..\n");
            startTime = clock();
			Heap_Sort(randomNum, number);
			endTime = clock();
			printf("���� �˰����� �Ϸ�Ǿ����ϴ�.\n");
			gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //���
			printf("�� ���� �ð� : %f��\n", gap);
			Sleep(3000);
			printf("���ĵ� ����� ����մϴ�.\n");
			Sleep(3000);
			for(i = 0 ; i < number ; i++){
				printf("%d ", randomNum[i]);
			}
			printf("\n������ �Ϸ�Ǿ����ϴ�.\n");
			Sleep(3000); 
			return gap;
	}
}



int main( )
{
    //���� ���� �� �ʱ�ȭ �κ�
    srand( (unsigned)time(NULL) );              //srand�� �ʱ�ȭ
  	
    int randomNum[nMAX];               //������ �ζ� ��ȣ�� ������ ����
    int bCheckExistOfNum[nMAX] = {0};     //������ ��ȣ�� �ߺ����� üũ�� ����(�ε���)
    int i,j;
    
  	float gap;
  	float gap_result_list[6];
  	float max_gap = 0;
   	time_t startTime=0, endTime=0;
    //��ȣ ���� �κ� 
    char cmd[10], sorting_name[20];
    int sort_code = 0;
   	
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
            strcpy(sorting_name, "��������");
            sort_code = 1;
        }
        else if(!strcmp(cmd,"2")){
            printf("�������� ����!\n");
            strcpy(sorting_name, "��������");
            sort_code = 2;
        }
        else if(!strcmp(cmd,"3")){
            printf("�պ����� ����!\n");
            strcpy(sorting_name, "�պ�����");
            sort_code = 3;
        }
        else if(!strcmp(cmd,"4")){
            printf("������ ����!\n");
            strcpy(sorting_name, "������");
            sort_code = 4;
        }
        else if(!strcmp(cmd,"q")) break;
        else{
            printf("�ùٸ� �ڵ带 �Է����ּ���\n");
            continue;
        }
        
        for(i = 0 ; i< 6; i++){
        	gap_result_list[i] = do_sort(sort_code, randomNum, bCheckExistOfNum, (i+1)*10000);
		}
        
        system("cls");
        printf("-----------%s ���� ���--------------\n",sorting_name);
        for(i = 0 ; i < 6 ; i++){
        	printf("%d�� ���� ���� �ð� : %f��\n", (i+1)*10000, gap_result_list[i]);
        }
        printf("---------------------------------------\n");
        
        
    }
   	
    return 0;
}

