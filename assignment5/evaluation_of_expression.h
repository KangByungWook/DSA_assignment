#ifndef EVALUATATION_OF_EXPRESSON
#define EVALUATATION_OF_EXPRESSON

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define TRUE 1
#define FALSE 0


//postFix : prefix���� ��ȯ�� postfix ���ڿ��� ����Ǵ� �ּ� 
char postFix[100];
int postFixBuffIndex = 0;

    

int get_precedence(char *oper){
	if(*oper == ')') return 0;
	else if(!strcmp(oper, "AND") || !strcmp(oper, "OR"))return 1;
	else if(*oper == '+' || *oper == '-') return 2;
	else if(*oper == '*' || *oper == '/') return 3;
	else if(*oper == '(' || *oper == ')') return 4;
	else return -1;
}

int is_operator(char *str){
	if(*str == '+' || *str == '-' || *str == '*' || *str == '/' || *str == '(' || *str == ')' || *str == 'A' || *str == 'O')return TRUE;
	else return FALSE;
}


char* prefix_to_postfix(char *str){
	char tmp[100];
	int num_of_char, len, i, start_index;
	len=strlen(str);
	element newElement;
    for(i=0;i<len;i++)
    {   
		start_index = i;
        num_of_char = 1; 
    	//������ ���	
        if('0'<=str[i] && str[i]<='9'){
        	// �ڿ� ���ڰ� �� �ִ� ���(2���ڸ� �̻�) 
        	while('0'<=str[i+1] && str[i+1]<='9'){
        		num_of_char++;
        		i++;
        	};
        	// ���� ���ڿ��� ����� tmp �� ���� ���ڿ��� ���� 
			strncpy(tmp, str+start_index,num_of_char);
			// ������ �޸� ������ null���� ���� 
			tmp[num_of_char] = '\0';
			
			strcat(postFix, tmp);
			strcat(postFix, " ");
			
			//printf("%d", atoi(tmp));
        }
        //�������� ���  
        else{
        	// ������ �ڸ� ���� 1�̻��� AND �Ǵ� OR�� ���. 
			while(('0'> str[i+1] || str[i+1] > '9') && str[i+1] != ' '){
				// �׷��� )* �� ���� ���� ������ �ϳ��̹Ƿ� ���� ó��.
				// �� �ϳ��� ���� �ȵ� 
        		if(is_operator(str+i+1))break;
        		
        		num_of_char++;
        		i++;
        	};
			strncpy(tmp, str+start_index,num_of_char);
			
        	tmp[num_of_char] = '\0';
        	// tmp�� ( �Ǵ� ) �� ��� ó�� 
        	while(!isEmpty(stack) && stack[top].precedence >= get_precedence(tmp)){
        		
        		// "(" �Ǵ� ")"�� ��� postFix�� �ݿ����� �ʴ´�. 
        		if(strcmp(stack[top].oper, ")") && strcmp(stack[top].oper, "(")){
        			//printf("%s", stack[top].oper);	
					strcat(postFix, stack[top].oper);
					strcat(postFix, " ");	
				}
        		
				
        		Pop(&top);
			}
			strcpy(newElement.oper,tmp);
			
			//"("�� ��� ������ ���ÿ� ������ �켱������ ���� ������ ���� ������ �켱������ ���� ������ 
			if(!strcmp(tmp,"(")) newElement.precedence = 0;
			else newElement.precedence = get_precedence(tmp);
			Push(&top, newElement);
        	}
	}
    while(!isEmpty(stack)){
    	// "(" �Ǵ� ")"�� ��� postFix�� �ݿ����� �ʴ´�. 
		if(strcmp(stack[top].oper, ")") && strcmp(stack[top].oper, "(")){
			//printf("%s", stack[top].oper);	
			strcat(postFix, stack[top].oper);
			strcat(postFix, " ");	
		}
		Pop(&top);
	}
	return postFix;	
}

float calculate_postfix(char *str){
	char tmp[100];
	int num_of_char, len, i, start_index;
	float first_operand, second_operand, result = 0;
	len=strlen(str);
	element newElement;
    for(i=0;i<len;i++)
    {   
    	// ������ ��� �ǳʶ� 
    	if(str[i]==32){
    		continue;	
		}
    	
		start_index = i;
        num_of_char = 1; 
    	//������ ���	
        if('0'<=str[i] && str[i]<='9'){
        	// �ڿ� ���ڰ� �� �ִ� ���(2���ڸ� �̻�) 
        	while('0'<=str[i+1] && str[i+1]<='9'){
        		num_of_char++;
        		i++;
        	};
        	// ���� ���ڿ��� ����� tmp �� ���� ���ڿ��� ���� 
			strncpy(tmp, str+start_index,num_of_char);
			// ������ �޸� ������ null���� ���� 
			tmp[num_of_char] = '\0';
			
			newElement.fnum = atof(tmp);
			
			// ������ ��쿡�� ���ÿ� push 
			Push(&top,newElement);
			
        }
        //�������� ���  
        else{
        	// ������ �ڸ� ���� 1�̻��� AND �Ǵ� OR�� ���. 
			while(('0'> str[i+1] || str[i+1] > '9') && str[i+1] != ' '){
				// �׷��� )* �� ���� ���� ������ �ϳ��̹Ƿ� ���� ó��.
				// �� �ϳ��� ���� �ȵ� 
        		if(is_operator(str+i+1))break;
        		
        		num_of_char++;
        		i++;
        	};
			strncpy(tmp, str+start_index,num_of_char);
			
        	tmp[num_of_char] = '\0';
        	
        	second_operand = stack[top].fnum;
        	Pop(&top);
        	first_operand = stack[top].fnum;
        	Pop(&top);
        	
        	if(!strcmp(tmp, "+"))result = first_operand+second_operand;
        	else if(!strcmp(tmp, "-"))result = first_operand-second_operand;
        	else if(!strcmp(tmp, "*"))result = first_operand*second_operand;
        	else if(!strcmp(tmp, "/"))result = first_operand/second_operand;
        	else if(!strcmp(tmp,"AND")){
        		result = first_operand && second_operand;
			}
        	else if(!strcmp(tmp,"OR")){
        		result = first_operand || second_operand;
			}
        	newElement.fnum = result;
        	Push(&top, newElement);
        }
    }
    return result;
}

#endif
