//
//  main.c
//  sparse_matrix
//
//  Created by KangByung wook on 2016. 3. 18..
//  Copyright ⓒ 2016년 KangByung wook. All rights reserved.
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

// 희소행렬을 전치시켜주는 함수 
triple* fast_transpose(triple a[]);

// 희소행렬 정보를 보기 일반행렬 형태로 출력해주는 함수 
void display_sparse_matrix(triple *a);

// 희소행렬 덧셈 연산 후 파일로 저장하는 함수 
void add_matrix(triple a[], triple b[]);

// 희소행렬 뺄셈 연산 후 파일로 저장하는 함수 
void sub_matrix(triple a[], triple b[]);

// 희소행렬 곱셈 연산 후 파일로 저장하는 함수 
void mul_matrix(triple a[], triple b[]);

// 파일로부터 희소행렬 정보를 읽어오는 함수
// 'A' : A.txt 'B' : B.txt 
triple* get_sparse_matrix_from_file(char file_name);

// 선택창 출력하는 함수 
int notice();


int main(int argc, const char * argv[]) {
    
	// A.txt파일로부터 정보를 읽어 ta에 저장 
    triple *ta = get_sparse_matrix_from_file('A');
    
    // B.txt 파일로부터 정보를 읽어 tb에 저장 
    triple *tb = get_sparse_matrix_from_file('B');
    triple *tmp;
    
    // ta를 전치시킨후 ta_transpose에 저장 
    triple* ta_transpose = fast_transpose(ta);
    
    // tb를 전치시킨후 tb_transpose에 저장 
    triple* tb_transpose = fast_transpose(tb);
    
    int cmd;
    int i;
    FILE *fp;
    while(1){
    	cmd = notice();
    	if(cmd == 0)break;
    	switch(cmd){
    		// A를 전치시키는 경우 
    		case 1:
    			tmp = fast_transpose(ta);
    			
				fp = fopen("TransA.txt", "w");
		        for(i = 0 ; i < tmp[0].value+1 ; i++){
		            fprintf(fp, "%d %d %d\n", tmp[i].col, tmp[i].row, tmp[i].value);
		        }
		
		        fclose(fp);
		    	printf("전치 결과 : \n");
		    	display_sparse_matrix(tmp);
		    	printf("위 정보가 TransA.txt 파일에 저장되었습니다\n");
    			break;
    		// B를 전치시키는 경우 
    		case 2:
    			tmp = fast_transpose(tb);
    			
				fp = fopen("TransB.txt", "w");
		        for(i = 0 ; i < tmp[0].value+1 ; i++){
		            fprintf(fp, "%d %d %d\n", tmp[i].col, tmp[i].row, tmp[i].value);
		        }
		
		        fclose(fp);
		    	printf("전치 결과 : \n");
		    	display_sparse_matrix(tmp);
		    	printf("위 정보가 TransB.txt 파일에 저장되었습니다\n");
    			break;
    		// 전치한 A와 B를 더함 
    		case 3:
    			add_matrix(ta_transpose, tb_transpose);
    			break;
    		// 전치한 A와 B를 뺄셈  
    		case 4:
    			sub_matrix(ta_transpose, tb_transpose);
    			break;
    		// 전치한 A와 B를 곱셈  
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
	printf("1. A.txt 파일 transpose!!\n");
	printf("2. B.txt 파일 transpose!!\n");
	printf("3. 전치 행렬끼리 더하기\n");
	printf("4. 전치 행렬끼리 빼기\n");
	printf("5. 전치 행렬끼리 곱하기\n");
	printf("(0번을 입력하면 프로그램이 종료됩니다.)\n");
	printf("-----------------------------\n");
	printf("무엇을 하시겠습니까? : "); 
	int cmd;
	scanf("%d", &cmd);
	return cmd; 
};

triple* fast_transpose(triple a[])
{
    /* a를 전치시켜 b에 저장 */
    int row_terms[a[0].col],starting_pos[a[0].row];
    int i,j,num_cols=a[0].col, num_terms=a[0].value;
    FILE *fp;
    
    triple* b = (triple*)malloc(sizeof(triple)*(a[0].value+1));
    b[0].row=num_cols;b[0].col=a[0].row;
    b[0].value=num_terms;
    
    
    
    if(num_terms>0) /*0이 아닌 행렬 */
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
	
	// 1. 유효한 연산인지 검증
    if(a[0].col != b[0].col || a[0].row != b[0].row){
        printf("덧셈 연산이 불가능합니다\n");
        return;
    }
    
    // 2. 덧셈 수행
    printf("덧셈을 수행합니다\n");
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
    printf("덧셈 결과 : \n");
    display_sparse_matrix(ta);
    printf("위 정보가 Add.txt 파일에 저장되었습니다\n");
};


void sub_matrix(triple a[], triple b[]){
    int i,j,index;
    triple *ta = (triple*)malloc(sizeof(triple)*(a[0].value+1));
    
    int num_col = a[0].col, num_row = a[0].row;
	int result_matrix[num_col][num_row], matrix_a[num_col][num_row], matrix_b[num_col][num_row];
	
	// 1. 유효한 연산인지 검증
    if(a[0].col != b[0].col || a[0].row != b[0].row){
        printf("연산이 불가능합니다\n");
        return;
    }
    
    // 2. 뺄셈 수행
    printf("뺄셈을 수행합니다\n");
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
    printf("뺄셈 결과 : \n");
    display_sparse_matrix(ta);
   	printf("위 결과가 sub.txt 파일에 저장되었습니다.\n"); 
};
// 곱셈 
void mul_matrix(triple a[], triple b[]){
	int i,j,k;
    int num_col = a[0].col, num_row = a[0].row;
    int result_col = b[0].col, result_row = a[0].row;
    
    int result_matrix[result_col][result_row], matrix_a[num_col][num_row], matrix_b[num_col][num_row];
    
    triple *ta = (triple*)malloc(sizeof(triple)*SIZE);
    
	// 1. 유효한 연산인지 검증
    if(a[0].col != b[0].row){
        printf("곱셈 연산이 불가능합니다\n");
        return;
    }
    
    // 2. 곱셈 수행
    printf("곱셈을 수행합니다\n");
    for(i = 0 ; i < a[0].row; i++){
        for(j = 0 ; j < a[0].col; j++){
            matrix_a[j][i] = 0;
        }
    } 
    for(i = 0 ; i < a[0].value ; i++){
        matrix_a[a[i].col][a[i].row] = a[i].value;
    }
    
    
    // b행렬 초기화 
    for(i = 0 ; i < b[0].row; i++){
        for(j = 0 ; j < b[0].col; j++){
            matrix_b[j][i] = 0;
        }
    }
    for(i = 0 ; i < b[0].value ; i++){
        matrix_b[b[i].col][b[i].row] = b[i].value;
    }
    
    // 결과 행렬 초기화 
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
    printf("곱셈 결과 : \n");
    display_sparse_matrix(ta);
    printf("위 정보가 Mul.txt 파일에 저장되었습니다.\n");
}
