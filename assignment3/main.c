//
//  main.c
//  sparse_matrix
//
//  Created by KangByung wook on 2016. 3. 18..
//  Copyright �� 2016�� KangByung wook. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 50

typedef struct triple{
    int row;
    int col;
    int value;
}triple;

// �������� ��ġ�����ִ� �Լ� 
triple* fast_transpose(triple a[]);

// ������ ������ ���� �Ϲ���� ���·� ������ִ� �Լ� 
void display_sparse_matrix(triple *a);

// ������ ���� ���� �� ���Ϸ� �����ϴ� �Լ� 
void add_matrix(triple a[], triple b[]);

// ������ ���� ���� �� ���Ϸ� �����ϴ� �Լ� 
void sub_matrix(triple a[], triple b[]);

// ������ ���� ���� �� ���Ϸ� �����ϴ� �Լ� 
void mul_matrix(triple a[], triple b[]);

// ���Ϸκ��� ������ ������ �о���� �Լ�
// 'A' : A.txt 'B' : B.txt 
triple* get_sparse_matrix_from_file(char file_name);

// ����â ����ϴ� �Լ� 
int notice();


int main(int argc, const char * argv[]) {
    
	// A.txt���Ϸκ��� ������ �о� ta�� ���� 
    triple *ta = get_sparse_matrix_from_file('A');
    
    // B.txt ���Ϸκ��� ������ �о� tb�� ���� 
    triple *tb = get_sparse_matrix_from_file('B');
    triple *tmp;
    
    // ta�� ��ġ��Ų�� ta_transpose�� ���� 
    triple* ta_transpose = fast_transpose(ta);
    
    // tb�� ��ġ��Ų�� tb_transpose�� ���� 
    triple* tb_transpose = fast_transpose(tb);
    
    int cmd;
    int i;
    FILE *fp;
    while(1){
    	cmd = notice();
    	if(cmd == 0)break;
    	switch(cmd){
    		// A�� ��ġ��Ű�� ��� 
    		case 1:
    			tmp = fast_transpose(ta);
    			
				fp = fopen("TransA.txt", "w");
		        for(i = 0 ; i < tmp[0].value+1 ; i++){
		            fprintf(fp, "%d %d %d\n", tmp[i].col, tmp[i].row, tmp[i].value);
		        }
		
		        fclose(fp);
		    	printf("��ġ ��� : \n");
		    	display_sparse_matrix(tmp);
		    	printf("�� ������ TransA.txt ���Ͽ� ����Ǿ����ϴ�\n");
    			break;
    		// B�� ��ġ��Ű�� ��� 
    		case 2:
    			tmp = fast_transpose(tb);
    			
				fp = fopen("TransB.txt", "w");
		        for(i = 0 ; i < tmp[0].value+1 ; i++){
		            fprintf(fp, "%d %d %d\n", tmp[i].col, tmp[i].row, tmp[i].value);
		        }
		
		        fclose(fp);
		    	printf("��ġ ��� : \n");
		    	display_sparse_matrix(tmp);
		    	printf("�� ������ TransB.txt ���Ͽ� ����Ǿ����ϴ�\n");
    			break;
    		// ��ġ�� A�� B�� ���� 
    		case 3:
    			add_matrix(ta_transpose, tb_transpose);
    			break;
    		// ��ġ�� A�� B�� ����  
    		case 4:
    			sub_matrix(ta_transpose, tb_transpose);
    			break;
    		// ��ġ�� A�� B�� ����  
    		case 5:
    			mul_matrix(ta_transpose, tb_transpose);
    			break;
    		default:
    			break;
    	}
	}    
    return 0;
}

int notice(){
	printf("-----------------------------\n");
	printf("1. A.txt ���� transpose!!\n");
	printf("2. B.txt ���� transpose!!\n");
	printf("3. ��ġ ��ĳ��� ���ϱ�\n");
	printf("4. ��ġ ��ĳ��� ����\n");
	printf("5. ��ġ ��ĳ��� ���ϱ�\n");
	printf("(0���� �Է��ϸ� ���α׷��� ����˴ϴ�.)\n");
	printf("-----------------------------\n");
	printf("������ �Ͻðڽ��ϱ�? : "); 
	int cmd;
	scanf("%d", &cmd);
	return cmd; 
};

triple* fast_transpose(triple a[])
{
    /* a�� ��ġ���� b�� ���� */
    int row_terms[a[0].col],starting_pos[a[0].row];
    int i,j,num_cols=a[0].col, num_terms=a[0].value;
    FILE *fp;
    
    triple* b = (triple*)malloc(sizeof(triple)*(a[0].value+1));
    b[0].row=num_cols;b[0].col=a[0].row;
    b[0].value=num_terms;
    
    
    
    if(num_terms>0) /*0�� �ƴ� ��� */
    {
        for(i=0;i<num_cols;i++)
            row_terms[i]=0;
        for(i=1;i<=num_terms;i++)
            row_terms[a[i].col]++;
        starting_pos[0]=1;
        for(i=1;i<num_cols;i++)
            starting_pos[i]=starting_pos[i-1]+row_terms[i-1];
        for(i=1;i<=num_terms;i++)
        {
            j=starting_pos[a[i].col]++;
            b[j].row=a[i].col;
            b[j].col=a[i].row;
            b[j].value=a[i].value;
        }
    }
    
    return b;
}

triple* get_sparse_matrix_from_file(char file_name){
    FILE *fp = NULL;
    int index = 0;
    char s[50];
    char *ptr = NULL;
    triple *ta = (triple*)malloc(sizeof(triple)*SIZE);
    
    switch (file_name) {
        case 'A':
            fp = fopen("A.txt", "r");
            break;
        case 'B':
            fp = fopen("B.txt", "r");
            break;
        default:
            fp = NULL;
            break;
    }
	
	
    while (fgets(s, 50, fp) != NULL) {
        ptr = strtok(s, " ");
        ta[index].col = atoi(ptr);
        ptr = strtok(NULL, " ");
        ta[index].row = atoi(ptr);
		ptr = strtok(NULL, " ");
		ta[index].value = atoi(ptr);
		index++;
    }
    
    fclose(fp);
    
    return ta;
}

void display_sparse_matrix(triple *a){
    int i, j;
    int num_col = a[0].col, num_row = a[0].row, cnt = a[0].value;
    int matrix[num_col][num_row];
    
    for(i = 0 ; i < num_col ; i++){
        for(j = 0 ; j < num_row; j++){
            matrix[i][j] = 0;
        }
    }
    for(i = 1 ; i <= cnt ; i++){
        matrix[a[i].col][a[i].row] = a[i].value;
    }
    
    for(i = 0 ; i < num_col; i++){
        if(i == 0)printf("     ");
        printf("%5d", i);
    }
    printf("\n");
    for(i = 0 ; i < num_row ; i++){
        printf("%5d",i);
        for(j = 0 ; j < num_col; j++){
            printf("%5d",matrix[j][i]);
        }
        printf("\n");
    }
}

void add_matrix(triple a[], triple b[]){
    int i,j,index;
    triple *ta = (triple*)malloc(sizeof(triple)*(a[0].value+1));
    
    int num_col = a[0].col, num_row = a[0].row;
	int result_matrix[num_col][num_row], matrix_a[num_col][num_row], matrix_b[num_col][num_row];
	
	// 1. ��ȿ�� �������� ����
    if(a[0].col != b[0].col || a[0].row != b[0].row){
        printf("���� ������ �Ұ����մϴ�\n");
        return;
    }
    
    // 2. ���� ����
    printf("������ �����մϴ�\n");
    for(i = 0 ; i < num_row; i++){
        for(j = 0 ; j < num_col; j++){
            matrix_a[j][i] = 0;
        }
    }
    for(i = 1 ; i < a[0].value ; i++){
        matrix_a[a[i].col][a[i].row] = a[i].value;
    }
    
    
    
    for(i = 0 ; i < num_row; i++){
        for(j = 0 ; j < num_col; j++){
            matrix_b[j][i] = 0;
        }
    }
    for(i = 1 ; i < b[0].value ; i++){
        matrix_b[b[i].col][b[i].row] = b[i].value;
    }
    
    
    for(i = 0 ; i < num_row ; i++){
        for(j = 0; j < num_col; j++){
            result_matrix[j][i] = matrix_a[j][i] + matrix_b[j][i];
        }
    }
    
    
    ta[0].col = num_col;
    ta[0].row = num_row;
    int cnt = 0;
    for(i = 0; i<num_row; i++){
        for(j=0; j<num_col; j++){
            if(result_matrix[j][i]){
                ta[++cnt].row = i;
                ta[cnt].col = j;
                ta[cnt].value = result_matrix[j][i];
            }
        }
    }
    ta[0].value = cnt;
    
    FILE* fp = fopen("Add.txt", "w");
        for(i = 0 ; i < cnt+1 ; i++){
            fprintf(fp, "%d %d %d\n", ta[i].col, ta[i].row, ta[i].value);
        }

        fclose(fp);
    printf("���� ��� : \n");
    display_sparse_matrix(ta);
    printf("�� ������ Add.txt ���Ͽ� ����Ǿ����ϴ�\n");
};


void sub_matrix(triple a[], triple b[]){
    int i,j,index;
    triple *ta = (triple*)malloc(sizeof(triple)*(a[0].value+1));
    
    int num_col = a[0].col, num_row = a[0].row;
	int result_matrix[num_col][num_row], matrix_a[num_col][num_row], matrix_b[num_col][num_row];
	
	// 1. ��ȿ�� �������� ����
    if(a[0].col != b[0].col || a[0].row != b[0].row){
        printf("������ �Ұ����մϴ�\n");
        return;
    }
    
    // 2. ���� ����
    printf("������ �����մϴ�\n");
    for(i = 0 ; i < num_row; i++){
        for(j = 0 ; j < num_col; j++){
            matrix_a[j][i] = 0;
        }
    }
    for(i = 1 ; i < a[0].value ; i++){
        matrix_a[a[i].col][a[i].row] = a[i].value;
    }
    
    
    
    for(i = 0 ; i < num_row; i++){
        for(j = 0 ; j < num_col; j++){
            matrix_b[j][i] = 0;
        }
    }
    for(i = 1 ; i < b[0].value ; i++){
        matrix_b[b[i].col][b[i].row] = b[i].value;
    }
    
    
    for(i = 0 ; i < num_row ; i++){
        for(j = 0; j < num_col; j++){
            result_matrix[j][i] = matrix_a[j][i] - matrix_b[j][i];
        }
    }
    
    
    ta[0].col = num_col;
    ta[0].row = num_row;
    int cnt = 0;
    for(i = 0; i<num_row; i++){
        for(j=0; j<num_col; j++){
            if(result_matrix[j][i]){
                ta[++cnt].row = i;
                ta[cnt].col = j;
                ta[cnt].value = result_matrix[j][i];
            }
        }
    }
    ta[0].value = cnt;
    
    FILE* fp = fopen("Sub.txt", "w");
        for(i = 0 ; i < cnt+1 ; i++){
            fprintf(fp, "%d %d %d\n", ta[i].col, ta[i].row, ta[i].value);
        }

        fclose(fp);
    printf("���� ��� : \n");
    display_sparse_matrix(ta);
   	printf("�� ����� sub.txt ���Ͽ� ����Ǿ����ϴ�.\n"); 
};
// ���� 
void mul_matrix(triple a[], triple b[]){
	int i,j,k;
    int num_col = a[0].col, num_row = a[0].row;
    int result_col = b[0].col, result_row = a[0].row;
    
    int result_matrix[result_col][result_row], matrix_a[num_col][num_row], matrix_b[num_col][num_row];
    
    triple *ta = (triple*)malloc(sizeof(triple)*SIZE);
    
	// 1. ��ȿ�� �������� ����
    if(a[0].col != b[0].row){
        printf("���� ������ �Ұ����մϴ�\n");
        return;
    }
    
    // 2. ���� ����
    printf("������ �����մϴ�\n");
    for(i = 0 ; i < a[0].row; i++){
        for(j = 0 ; j < a[0].col; j++){
            matrix_a[j][i] = 0;
        }
    } 
    for(i = 0 ; i < a[0].value ; i++){
        matrix_a[a[i].col][a[i].row] = a[i].value;
    }
    
    
    // b��� �ʱ�ȭ 
    for(i = 0 ; i < b[0].row; i++){
        for(j = 0 ; j < b[0].col; j++){
            matrix_b[j][i] = 0;
        }
    }
    for(i = 0 ; i < b[0].value ; i++){
        matrix_b[b[i].col][b[i].row] = b[i].value;
    }
    
    // ��� ��� �ʱ�ȭ 
    for(i = 0 ; i < result_row; i++){
        for(j = 0 ; j < result_col; j++){
            result_matrix[j][i] = 0;
        }
    }
    
    for(i = 0 ; i < result_row; i++){
        for(j = 0; j < result_col; j++){
        	for(k =0 ; k < num_col; k++){
        		result_matrix[j][i] += matrix_a[k][i] * matrix_b[j][k];
			}
        }
    }
    
    ta[0].col = result_col;
    ta[0].row = result_row;
    int cnt = 0;
    for(i = 0; i<result_row; i++){
        for(j=0; j<result_col; j++){
            if(result_matrix[i][j]){
                ta[++cnt].row = i;
                ta[cnt].col = j;
                ta[cnt].value = result_matrix[i][j];
            }
        }
    }
    ta[0].value = cnt;
    
    FILE* fp = fopen("Mul.txt", "w");
        for(i = 0 ; i < cnt+1 ; i++){
            fprintf(fp, "%d %d %d\n", ta[i].col, ta[i].row, ta[i].value);
        }

        fclose(fp);
    printf("���� ��� : \n");
    display_sparse_matrix(ta);
    printf("�� ������ Mul.txt ���Ͽ� ����Ǿ����ϴ�.\n");
}
