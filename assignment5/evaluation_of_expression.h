#ifndef EVALUATATION_OF_EXPRESSON
#define EVALUATATION_OF_EXPRESSON

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define TRUE 1
#define FALSE 0


//postFix : prefix에서 변환된 postfix 문자열이 저장되는 주소 
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
    	//숫자인 경우	
        if('0'<=str[i] && str[i]<='9'){
        	// 뒤에 숫자가 더 있는 경우(2의자리 이상) 
        	while('0'<=str[i+1] && str[i+1]<='9'){
        		num_of_char++;
        		i++;
        	};
        	// 숫자 문자열이 저장될 tmp 에 숫자 문자열을 저장 
			strncpy(tmp, str+start_index,num_of_char);
			// 마지막 메모리 공간에 null문자 삽입 
			tmp[num_of_char] = '\0';
			
			strcat(postFix, tmp);
			strcat(postFix, " ");
			
			//printf("%d", atoi(tmp));
        }
        //연산자인 경우  
        else{
        	// 연산자 자리 수가 1이상인 AND 또는 OR인 경우. 
			while(('0'> str[i+1] || str[i+1] > '9') && str[i+1] != ' '){
				// 그러나 )* 와 같은 경우는 각각이 하나이므로 따로 처리.
				// 즉 하나로 보면 안됨 
        		if(is_operator(str+i+1))break;
        		
        		num_of_char++;
        		i++;
        	};
			strncpy(tmp, str+start_index,num_of_char);
			
        	tmp[num_of_char] = '\0';
        	// tmp가 ( 또는 ) 인 경우 처리 
        	while(!isEmpty(stack) && stack[top].precedence >= get_precedence(tmp)){
        		
        		// "(" 또는 ")"인 경우 postFix에 반영하지 않는다. 
        		if(strcmp(stack[top].oper, ")") && strcmp(stack[top].oper, "(")){
        			//printf("%s", stack[top].oper);	
					strcat(postFix, stack[top].oper);
					strcat(postFix, " ");	
				}
        		
				
        		Pop(&top);
			}
			strcpy(newElement.oper,tmp);
			
			//"("인 경우 들어갈때는 스택에 들어갈때는 우선순위가 가장 높지만 들어가고 나서는 우선순위가 가장 낮아짐 
			if(!strcmp(tmp,"(")) newElement.precedence = 0;
			else newElement.precedence = get_precedence(tmp);
			Push(&top, newElement);
        	}
	}
    while(!isEmpty(stack)){
    	// "(" 또는 ")"인 경우 postFix에 반영하지 않는다. 
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
    	// 공백의 경우 건너뜀 
    	if(str[i]==32){
    		continue;	
		}
    	
		start_index = i;
        num_of_char = 1; 
    	//숫자인 경우	
        if('0'<=str[i] && str[i]<='9'){
        	// 뒤에 숫자가 더 있는 경우(2의자리 이상) 
        	while('0'<=str[i+1] && str[i+1]<='9'){
        		num_of_char++;
        		i++;
        	};
        	// 숫자 문자열이 저장될 tmp 에 숫자 문자열을 저장 
			strncpy(tmp, str+start_index,num_of_char);
			// 마지막 메모리 공간에 null문자 삽입 
			tmp[num_of_char] = '\0';
			
			newElement.fnum = atof(tmp);
			
			// 숫자인 경우에는 스택에 push 
			Push(&top,newElement);
			
        }
        //연산자인 경우  
        else{
        	// 연산자 자리 수가 1이상인 AND 또는 OR인 경우. 
			while(('0'> str[i+1] || str[i+1] > '9') && str[i+1] != ' '){
				// 그러나 )* 와 같은 경우는 각각이 하나이므로 따로 처리.
				// 즉 하나로 보면 안됨 
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
