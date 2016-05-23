#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	FILE *fp ;
    int index, data;
    char* inp;
    int buf_size = 1024;
    char word[50];
    char meaning[100];
    fp = fopen("eng_voc_sm.txt", "r");
	char* token = NULL;
    inp = malloc(buf_size+5);

    while(fgets(inp,buf_size,fp)){
        if(strlen(inp) != 1){
            printf("------- \n");
            printf("�Է¹��� ���� : %s\n" , inp);
			printf("���ڿ��� ���� : %d \n" , strlen(inp));
            token = strtok(inp, ">");
            int index = 0;
            while(token != NULL){
            	//printf("token = %s\n", token);
            	
            	if(index == 0){
            		strcpy(word, token);
				}else{
					strcpy(meaning, token);
				}
				token = strtok(NULL,">");
				index++;
			}
			printf("word : %s", word);
			printf("meaning : %s", meaning);
			
			
            printf("------- \n");
        }
    }
    fclose(fp);
}
