#ifndef EVAL_EXPRESSION
#define EVAL_EXPRESSION
#define TRUE 1
#define FALSE 0
#define MAX_STRING_SIZE 100

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

char postFix[MAX_STRING_SIZE];

// 해당 문자가 연산자인지 판단하는 함수. 
int is_oper(char oper){
	if(oper == '+' || oper == '-' || oper == '*' || oper == '/' || oper == '(' || oper == ')')return TRUE;
	return FALSE;
}

// 연산자의 우선순위를 반환해주는 함수 
int get_precedence(char oper){
	if(oper == '+' || oper == '-')return 1;
	else if(oper == '*' || oper == '/')return 2;
	else if(oper == '(' || oper == ')')return 0;
	else -1;
}

// infix문자열을 postfix문자열로 바꿔주는 함수 
int infix_to_postfix(char* equation){
	char *ptr = equation;
	char top_oper, tmp;
	int index = 0, precedence;
	while(*ptr != '\0'){
		//연산자인 경우 
		if(is_oper(*ptr)){
			// ( 가 올 경우 무조건 스택에 푸쉬 
			if(*ptr == '('){
				push(*ptr, &top);
			}
			// ) 가 올 경우 ( 가 나타날때까지 계속 pop하고 )는 푸쉬하지 않는다 
			else if(*ptr == ')'){
				precedence = get_precedence(*ptr);
				top_oper = get_top(&top);
				while(!is_empty(&top) && get_precedence(top_oper) >= precedence){
					tmp = pop(&top);
					if(tmp == '(')break;
					postFix[index++] = tmp;
					top_oper = get_top(&top);
				}
			}
			// 여는 괄호 또는 닫는 괄호가 아닌 경우 자기 자신보다 같거나 높은 우선순위에 있는 연산자를 스택에서 pop하고
			// 자기 자신을 스택에 push한다 
			else{
				precedence = get_precedence(*ptr);
				top_oper = get_top(&top);
				while(!is_empty(&top) && get_precedence(top_oper) >= precedence){
					tmp = pop(&top);
					if(tmp == '(')break;
					postFix[index++] = tmp;
					top_oper = get_top(&top);
				}
				push(*ptr, &top);	 	
			}
			
		}
		//피연산자인 경우 postFix에 바로 넣는다 
		else{
			postFix[index++] = *ptr;
		} 
		ptr++;
	}
	//남은 연산자 모두 출력
	while(!is_empty(&top)){
		tmp = pop(&top);
		postFix[index++] = tmp;
	} 
	//마지막에 널문자 추가 
	postFix[index] = '\0';
	
}


#endif
