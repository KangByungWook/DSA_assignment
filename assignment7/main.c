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
        	if(i >= 32767 && bCheckExistOfNum[nTemp + (number-32767)] == FALSE){
        		bCheckExistOfNum[nTemp + (number-32767)] = TRUE;     //��ȣ�� �ߺ� �������� �ʰ� ���� ���θ� true�� �Ѵ�.
            	list[i] = nTemp + (number-32767) +1;             //+1�� �����ָ� ������ 0~44�̴�.
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
//   	gap=(float)(endTime-startTime)/(CLOCKS_PER_SEC); //���
//	printf("�� �ɸ� �ð� %f\n", gap);
   	
   	
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
        
        switch(sort_code){
            case 1:
                printf("���� 10000�� ����\n");
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

