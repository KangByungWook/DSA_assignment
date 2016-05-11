#ifndef EVAL_EXPRESSION
#define EVAL_EXPRESSION
#define TRUE 1
#define FALSE 0
#define MAX_STRING_SIZE 100

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

char postFix[MAX_STRING_SIZE];

// �ش� ���ڰ� ���������� �Ǵ��ϴ� �Լ�. 
int is_oper(char oper){
	if(oper == '+' || oper == '-' || oper == '*' || oper == '/' || oper == '(' || oper == ')')return TRUE;
	return FALSE;
}

// �������� �켱������ ��ȯ���ִ� �Լ� 
int get_precedence(char oper){
	if(oper == '+' || oper == '-')return 1;
	else if(oper == '*' || oper == '/')return 2;
	else if(oper == '(' || oper == ')')return 0;
	else -1;
}

// infix���ڿ��� postfix���ڿ��� �ٲ��ִ� �Լ� 
int infix_to_postfix(char* equation){
	char *ptr = equation;
	char top_oper, tmp;
	int index = 0, precedence;
	while(*ptr != '\0'){
		//�������� ��� 
		if(is_oper(*ptr)){
			// ( �� �� ��� ������ ���ÿ� Ǫ�� 
			if(*ptr == '('){
				push(*ptr, &top);
			}
			// ) �� �� ��� ( �� ��Ÿ�������� ��� pop�ϰ� )�� Ǫ������ �ʴ´� 
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
			// ���� ��ȣ �Ǵ� �ݴ� ��ȣ�� �ƴ� ��� �ڱ� �ڽź��� ���ų� ���� �켱������ �ִ� �����ڸ� ���ÿ��� pop�ϰ�
			// �ڱ� �ڽ��� ���ÿ� push�Ѵ� 
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
		//�ǿ������� ��� postFix�� �ٷ� �ִ´� 
		else{
			postFix[index++] = *ptr;
		} 
		ptr++;
	}
	//���� ������ ��� ���
	while(!is_empty(&top)){
		tmp = pop(&top);
		postFix[index++] = tmp;
	} 
	//�������� �ι��� �߰� 
	postFix[index] = '\0';
	
}


#endif
