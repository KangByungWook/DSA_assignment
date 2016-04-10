#ifndef EVALUATATION_OF_EXPRESSON
#define EVALUATATION_OF_EXPRESSON

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define TRUE 1
#define FALSE 0


//postFix : infix���� ��ȯ�� postfix ���ڿ��� ����Ǵ� �ּ� 
char postFix[100];
//postFix ���ڿ��� �о�ö� ����ϴ� �ε���, �о���� ���ڰ� ���ڿ��� ��� ��ġ���ִ��� �˷��ִ� �ε���. 
int postFixBuffIndex = 0;

// �����ڸ� �Ű������� �޾Ƽ� �켱������ ��ȯ���ִ� �Լ�. 
int get_precedence(char *oper){
	if(*oper == ')') return 0; // �ݴ� ��ȣ : �켱���� 0 
	else if(!strcmp(oper, "AND") || !strcmp(oper, "OR"))return 1; // AND �Ǵ� OR�� ��� �켱���� 1 
	else if(*oper == '+' || *oper == '-') return 2; // + �Ǵ� - �� ��� �켱���� 2 
	else if(*oper == '*' || *oper == '/') return 3; // * �Ǵ� / �� ��� �켱���� 3 
	else if(*oper == '(') return 4; //  ���� ��ȣ : �켱���� 4, ������ 4�� ������ �� ���ķδ� �켱������ 0���� ������. 
	else return -1; // �����ڰ� �ƴ� ��� -1 ���� 
}

// �ش� ��ġ�� char ������ ���������� �ƴ��� �˷��ִ� �Լ�. 
int is_operator(char *str){
	if(*str == '+' || *str == '-' || *str == '*' || *str == '/' || *str == '(' || *str == ')' || *str == 'A' || *str == 'O')return TRUE;
	else return FALSE;
}


// infix������ ���ڿ��� �޾Ƽ� postFix�� �ٲ��ְ� postFix���ڿ��� ���� �ּҸ� ��ȯ���ִ� �Լ� 
char* infix_to_postfix(char *str){
	// ������ �Ǵ� �ǿ����ڸ� �����س��� �ӽ� ���ڿ� ���� 
	char tmp[100];
	int num_of_char, len, i, start_index;
	
	// �Ű������� ���� ���ڿ��� ����. 
	len=strlen(str);
	
	// ���ÿ� ���� element���� ���� 
	// element ����ü�� stack.h�� ����. 
	element newElement;
	
	// �Ű������� ���� ���ڿ��� ��ĭ�� �д´� 
    for(i=0;i<len;i++)
    {   
		// �о�� ���ڰ� ���۵Ǵ� ����. 
		start_index = i;
		
		// �о�� ������ ���� 
        num_of_char = 1; 
        
    	//�ش� ��ġ�� ���ڰ� ������ ���	
        if('0'<=str[i] && str[i]<='9'){
        	
			// �ڿ� ���ڰ� �� �ִ� ���(2���ڸ� �̻�) 
        	while('0'<=str[i+1] && str[i+1]<='9'){
        		// �о�� ���ڰ� ���ڸ��� �̻��� ��� num_of_char 1�� ����. 
        		num_of_char++;
        		
        		// for���� ����ǰ� �������� �о�� �κ��� ��ġ�� 1�� ����.
        		i++;
        	};
        	// ���� ���ڿ��� ����� tmp �� ���� ���ڿ��� ���� 
			strncpy(tmp, str+start_index,num_of_char);
			// ������ �޸� ������ null���� ���� 
			tmp[num_of_char] = '\0';
			
			// postFix ���ڿ��� �о�� ������ ���ڿ��� �ڿ� �ٿ��� 
			strcat(postFix, tmp);
			
			// �����̽��� �ٿ���.
			// ���߿� ����Ҷ� ���� �Ǵ� �����ڳ��� �����ϱ� ����. 
			strcat(postFix, " ");
			
			//printf("%d", atoi(tmp));
        }
        
		//�ش� ��ġ�� ���ڰ� �������� ���  
        else{
        	// ������ �ڸ� ���� 1�̻��� AND �Ǵ� OR�� ���. 
			while(('0'> str[i+1] || str[i+1] > '9') && str[i+1] != ' '){
				// �׷��� )* �� ���� ���� ������ �ϳ��̹Ƿ� ���� ó��.
				// �� �ϳ��� ���� �ȵ� 
				// is_operator : �ش� ��ġ�� ���ڰ� ���������� �ƴ��� �Ǵ��ϴ� �Լ�. 
        		if(is_operator(str+i+1))break;
        		
        		// �о�� ���ڿ��� ������ 1�� ���� 
        		num_of_char++;
        		
        		// �������� ���� ���ڿ��� ��ġ�� �� i���� 1�� ���� 
        		i++;
        	};
        	
			// tmp������ �о�� ������ ���ڿ��� �ִ´�. 
			strncpy(tmp, str+start_index,num_of_char);
			
			// tmp������ ������ ��ġ�� null���� ���� 
        	tmp[num_of_char] = '\0';
        	
        	// ������ ��ų� �켱������ �ڽź��� ���� �����ڰ� ���ö����� ������ ���ÿ��� pop. 
        	while(!isEmpty(stack) && stack[top].precedence >= get_precedence(tmp)){
        		// tmp�� "(' �Ǵ� ')' �� ��� ó��.
        		// "(" �Ǵ� ")"�� ��� postFix�� �ݿ����� �ʴ´�.  
        		if(strcmp(stack[top].oper, ")") && strcmp(stack[top].oper, "(")){
        			//printf("%s", stack[top].oper);
        			
					// stack�� top�� pop�ϱ� ���� ���� top�� element �������� ������ ������ �о�� postFix���ڿ��� �ٿ��ش�. 
					strcat(postFix, stack[top].oper);
					
					// ������ ���� �����̽��� �־��ش�. 
					strcat(postFix, " ");	
				}
        		// ���ÿ��� pop�Ѵ�. 
        		Pop(&top);
			}
			// newElement���� tmp�� �о�� ������ ������ �ִ´�. 
			strcpy(newElement.oper,tmp);
			
			//"("�� ��� ������ ���ÿ� ������ �켱������ ���� ������ ���� ������ �켱������ ���� ������ 
			if(!strcmp(tmp,"(")) newElement.precedence = 0;
			// "("�� �ƴ� ���� ���������� �켱������ �޾ƿ´� 
			else newElement.precedence = get_precedence(tmp);
			
			// newElement�� ���ÿ� push�Ѵ�. 
			Push(&top, newElement);
        }
	}
	
	// ���ÿ� ���� �����ڸ� �� �����´�. 
    while(!isEmpty(stack)){
    	// "(" �Ǵ� ")"�� ��� postFix�� �ݿ����� �ʴ´�. 
		if(strcmp(stack[top].oper, ")") && strcmp(stack[top].oper, "(")){
			//printf("%s", stack[top].oper);
			
			// stack�� top�� pop�ϱ� ���� ���� top�� element �������� ������ ������ �о�� postFix���ڿ��� �ٿ��ش�. 	
			strcat(postFix, stack[top].oper);
			
			// ������ ���� �����̽��� �־��ش�. 
			strcat(postFix, " ");	
		}
		// stack�� top�� �ִ� �κ��� pop�Ѵ�. 
		Pop(&top);
	}
	return postFix;	
}

// postFix���ڿ��� �Ű������� �޾Ƽ� ��� ����� float������ ������ ��ȯ���ִ� �Լ�. 
float calculate_postfix(char *str){
	// �о�� ���� �ӽ÷� ������ ���ڿ� 
	char tmp[100];
	int num_of_char, len, i, start_index;
	
	// ���� ����� �� �� �ǿ����� ����, �� �ǿ������� ���� ����� ������ result 
	float first_operand, second_operand, result = 0;
	
	// �޾ƿ� ���ڿ��� ���� 
	len=strlen(str);
	
	// ���ÿ� ���� element����
	// stack.h�� element����. 
	element newElement;
    for(i=0;i<len;i++)
    {   
    	// ������ ��� �ǳʶ� 
    	if(str[i]==32){
    		continue;	
		}
    	
    	// ���ڿ����� �о�� ������ ���� ��ġ 
		start_index = i;
		
		// ���ڿ����� �о�� ������ ���� 
        num_of_char = 1; 
        
    	// �ش� ��ġ�� ���ڰ� ������ ���	
        if('0'<=str[i] && str[i]<='9'){
        	// �ڿ� ���ڰ� �� �ִ� ���(2���ڸ� �̻�) 
        	while('0'<=str[i+1] && str[i+1]<='9'){
        		// �о�� ������ ���� 1 ���� 
        		num_of_char++;
        		
        		// ������ ���� ������ ��ġ�� 1���� 
        		i++;
        	};
        	// ���� ���ڿ��� ����� tmp �� ���� ���ڿ��� ���� 
			strncpy(tmp, str+start_index,num_of_char);
			// ������ �޸� ������ null���� ���� 
			tmp[num_of_char] = '\0';
			
			// �о�� ���� ���ڿ��� float������ ��ȯ�Ͽ� newElement�� fnum������ �ִ´�  
			newElement.fnum = atof(tmp);
			
			// ���ÿ� push 
			Push(&top,newElement);
			
        }
        //�о�� ���ڰ� �������� ���  
        else{
        	// ������ �ڸ� ���� 1�̻��� AND �Ǵ� OR�� ���. 
			while(('0'> str[i+1] || str[i+1] > '9') && str[i+1] != ' '){
				// �׷��� )* �� ���� ���� ������ �ϳ��̹Ƿ� ���� ó��.
				// �� �ϳ��� ���� �ȵ� 
        		if(is_operator(str+i+1))break;
        		
        		// �о�� ������ ���� 1 ����
        		num_of_char++;
        		
        		// ������ ���� ������ ��ġ�� 1���� 
        		i++;
        	};
        	// �о�� ���ڿ��� tmp ������ ����. 
			strncpy(tmp, str+start_index,num_of_char);
			
			// tmp ���ڿ��� ������ ��ġ�� null���� �־��ش� 
        	tmp[num_of_char] = '\0';
        	
        	// pop�ϱ� ���� top element�� fnum�� rhs �ǿ����ڿ� ����  
        	second_operand = stack[top].fnum;
        	// ���� top�� pop 
        	Pop(&top);
        	
        	// pop�ϱ� ���� top element�� fnum�� lhs �ǿ����ڿ� ����  
        	first_operand = stack[top].fnum;
        	// ���� top�� pop 
        	Pop(&top);
        	
        	// �о�� �������� ���ڿ����� ���� �� �ǿ����ڸ� �ٸ��� ó���Ͽ� result�� �ִ´� 
        	if(!strcmp(tmp, "+"))result = first_operand+second_operand;
        	else if(!strcmp(tmp, "-"))result = first_operand-second_operand;
        	else if(!strcmp(tmp, "*"))result = first_operand*second_operand;
        	else if(!strcmp(tmp, "/"))result = first_operand/second_operand;
        	else if(!strcmp(tmp,"AND"))result = first_operand && second_operand;
			else if(!strcmp(tmp,"OR"))result = first_operand || second_operand;
			
			// newElement�� fnum�� ������� �־ 
        	newElement.fnum = result;
        	// ���ÿ� push���ش� 
        	Push(&top, newElement);
        }
    }
    // ������ �����ִ� ������ ����. 
    Pop(&top);
    
    // result : ���ÿ� ���������� �����ִ� �ϳ��� element�� fnum 
    // result�� ��ȯ�Ѵ�. 
    return result;
}

// �Է¹��� infix ���� �����ϴ� �Լ�
// �Ŀ� ������ ���ٸ� -1�� ����
// ������ �ִٸ� ������ �ִ� �κ��� index�� ���� 
int equation_validation(char *equation){
	int i, not_valid_index = -1;
	
	// ���ڿ��� ��ĭ�� �Űܴٴϸ� ��ȿ�� ���ڰ� �ԷµǾ����� üũ 
	for(i = 0; i < strlen(equation); i++){
		// �������� ���� 
		if('0' <= equation[i] &&equation[i] <= '9')continue;
		
		// ������ �Ǵ� ��ȣ���� ���� 
		if(equation[i] == '*' || equation[i] == '/' || equation[i] == '+' || equation[i] == '-' || equation[i] == '(' || equation[i] == ')')continue;
		
		// AND���� ���� 
		if(equation[i] == 'A'){
			if(equation[i+1] == 'N' && equation[i+2] == 'D'){
				i = i+2;
				continue;	
			}
		}
		
		//OR���� ���� 
		if(equation[i] == 'O'){
			if(equation[i+1] == 'R'){
				i++;
				continue;	
			}
		}
		not_valid_index = i;
		break;
	}
	return not_valid_index;
}
#endif
