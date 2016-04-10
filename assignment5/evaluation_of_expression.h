#ifndef EVALUATATION_OF_EXPRESSON
#define EVALUATATION_OF_EXPRESSON

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define TRUE 1
#define FALSE 0


//postFix : infix에서 변환된 postfix 문자열이 저장되는 주소 
char postFix[100];
//postFix 문자열을 읽어올때 사용하는 인덱스, 읽어오는 문자가 문자열의 어디에 위치해있는지 알려주는 인덱스. 
int postFixBuffIndex = 0;

// 연산자를 매개변수로 받아서 우선순위를 반환해주는 함수. 
int get_precedence(char *oper){
	if(*oper == ')') return 0; // 닫는 괄호 : 우선순위 0 
	else if(!strcmp(oper, "AND") || !strcmp(oper, "OR"))return 1; // AND 또는 OR인 경우 우선순위 1 
	else if(*oper == '+' || *oper == '-') return 2; // + 또는 - 인 경우 우선순위 2 
	else if(*oper == '*' || *oper == '/') return 3; // * 또는 / 인 경우 우선순위 3 
	else if(*oper == '(') return 4; //  여는 괄호 : 우선순위 4, 들어갈때는 4로 들어가지만 들어간 이후로는 우선순위가 0으로 떨어짐. 
	else return -1; // 연산자가 아닌 경우 -1 리턴 
}

// 해당 위치의 char 변수가 연산자인지 아닌지 알려주는 함수. 
int is_operator(char *str){
	if(*str == '+' || *str == '-' || *str == '*' || *str == '/' || *str == '(' || *str == ')' || *str == 'A' || *str == 'O')return TRUE;
	else return FALSE;
}


// infix형태의 문자열을 받아서 postFix로 바꿔주고 postFix문자열의 시작 주소를 반환해주는 함수 
char* infix_to_postfix(char *str){
	// 연산자 또는 피연산자를 저장해놓을 임시 문자열 변수 
	char tmp[100];
	int num_of_char, len, i, start_index;
	
	// 매개변수로 받은 문자열의 길이. 
	len=strlen(str);
	
	// 스택에 넣을 element변수 선언 
	// element 구조체는 stack.h에 정의. 
	element newElement;
	
	// 매개변수로 받은 문자열을 한칸씩 읽는다 
    for(i=0;i<len;i++)
    {   
		// 읽어올 문자가 시작되는 지점. 
		start_index = i;
		
		// 읽어올 문자의 갯수 
        num_of_char = 1; 
        
    	//해당 위치의 문자가 숫자인 경우	
        if('0'<=str[i] && str[i]<='9'){
        	
			// 뒤에 숫자가 더 있는 경우(2의자리 이상) 
        	while('0'<=str[i+1] && str[i+1]<='9'){
        		// 읽어올 숫자가 두자리수 이상인 경우 num_of_char 1씩 증가. 
        		num_of_char++;
        		
        		// for문이 종료되고 다음으로 읽어올 부분의 위치도 1씩 증가.
        		i++;
        	};
        	// 숫자 문자열이 저장될 tmp 에 숫자 문자열을 저장 
			strncpy(tmp, str+start_index,num_of_char);
			// 마지막 메모리 공간에 null문자 삽입 
			tmp[num_of_char] = '\0';
			
			// postFix 문자열에 읽어온 숫자의 문자열을 뒤에 붙여줌 
			strcat(postFix, tmp);
			
			// 스페이스를 붙여줌.
			// 나중에 계산할때 숫자 또는 연산자끼리 구분하기 위함. 
			strcat(postFix, " ");
			
			//printf("%d", atoi(tmp));
        }
        
		//해당 위치의 문자가 연산자인 경우  
        else{
        	// 연산자 자리 수가 1이상인 AND 또는 OR인 경우. 
			while(('0'> str[i+1] || str[i+1] > '9') && str[i+1] != ' '){
				// 그러나 )* 와 같은 경우는 각각이 하나이므로 따로 처리.
				// 즉 하나로 보면 안됨 
				// is_operator : 해당 위치의 문자가 연산자인지 아닌지 판단하는 함수. 
        		if(is_operator(str+i+1))break;
        		
        		// 읽어올 문자열의 갯수를 1씩 증가 
        		num_of_char++;
        		
        		// 다음으로 읽을 문자열의 위치가 될 i또한 1씩 증가 
        		i++;
        	};
        	
			// tmp변수에 읽어온 연산자 문자열을 넣는다. 
			strncpy(tmp, str+start_index,num_of_char);
			
			// tmp변수의 마지막 위치에 null문자 삽입 
        	tmp[num_of_char] = '\0';
        	
        	// 스택이 비거나 우선순위가 자신보다 낮은 연산자가 나올때까지 연산자 스택에서 pop. 
        	while(!isEmpty(stack) && stack[top].precedence >= get_precedence(tmp)){
        		// tmp가 "(' 또는 ')' 인 경우 처리.
        		// "(" 또는 ")"인 경우 postFix에 반영하지 않는다.  
        		if(strcmp(stack[top].oper, ")") && strcmp(stack[top].oper, "(")){
        			//printf("%s", stack[top].oper);
        			
					// stack의 top을 pop하기 전에 스택 top의 element 변수에서 연산자 정보를 읽어와 postFix문자열에 붙여준다. 
					strcat(postFix, stack[top].oper);
					
					// 구분을 위해 스페이스를 넣어준다. 
					strcat(postFix, " ");	
				}
        		// 스택에서 pop한다. 
        		Pop(&top);
			}
			// newElement에서 tmp에 읽어온 연산자 정보를 넣는다. 
			strcpy(newElement.oper,tmp);
			
			//"("인 경우 들어갈때는 스택에 들어갈때는 우선순위가 가장 높지만 들어가고 나서는 우선순위가 가장 낮아짐 
			if(!strcmp(tmp,"(")) newElement.precedence = 0;
			// "("가 아닌 경우는 정상적으로 우선순위를 받아온다 
			else newElement.precedence = get_precedence(tmp);
			
			// newElement를 스택에 push한다. 
			Push(&top, newElement);
        }
	}
	
	// 스택에 남은 연산자를 다 꺼내온다. 
    while(!isEmpty(stack)){
    	// "(" 또는 ")"인 경우 postFix에 반영하지 않는다. 
		if(strcmp(stack[top].oper, ")") && strcmp(stack[top].oper, "(")){
			//printf("%s", stack[top].oper);
			
			// stack의 top을 pop하기 전에 스택 top의 element 변수에서 연산자 정보를 읽어와 postFix문자열에 붙여준다. 	
			strcat(postFix, stack[top].oper);
			
			// 구분을 위해 스페이스를 넣어준다. 
			strcat(postFix, " ");	
		}
		// stack의 top에 있는 부분을 pop한다. 
		Pop(&top);
	}
	return postFix;	
}

// postFix문자열을 매개변수로 받아서 계산 결과를 float형태의 변수로 반환해주는 함수. 
float calculate_postfix(char *str){
	// 읽어온 값을 임시로 저장한 문자열 
	char tmp[100];
	int num_of_char, len, i, start_index;
	
	// 연산 대상이 될 두 피연산자 선언, 두 피연산자의 연산 결과를 저장할 result 
	float first_operand, second_operand, result = 0;
	
	// 받아온 문자열의 길이 
	len=strlen(str);
	
	// 스택에 쌓을 element변수
	// stack.h에 element정의. 
	element newElement;
    for(i=0;i<len;i++)
    {   
    	// 공백의 경우 건너뜀 
    	if(str[i]==32){
    		continue;	
		}
    	
    	// 문자열에서 읽어올 문자의 시작 위치 
		start_index = i;
		
		// 문자열에서 읽어올 문자의 길이 
        num_of_char = 1; 
        
    	// 해당 위치의 문자가 숫자인 경우	
        if('0'<=str[i] && str[i]<='9'){
        	// 뒤에 숫자가 더 있는 경우(2의자리 이상) 
        	while('0'<=str[i+1] && str[i+1]<='9'){
        		// 읽어올 문자의 길이 1 증가 
        		num_of_char++;
        		
        		// 다음에 읽을 문자의 위치도 1증가 
        		i++;
        	};
        	// 숫자 문자열이 저장될 tmp 에 숫자 문자열을 저장 
			strncpy(tmp, str+start_index,num_of_char);
			// 마지막 메모리 공간에 null문자 삽입 
			tmp[num_of_char] = '\0';
			
			// 읽어온 숫자 문자열을 float변수로 변환하여 newElement의 fnum변수에 넣는다  
			newElement.fnum = atof(tmp);
			
			// 스택에 push 
			Push(&top,newElement);
			
        }
        //읽어온 문자가 연산자인 경우  
        else{
        	// 연산자 자리 수가 1이상인 AND 또는 OR인 경우. 
			while(('0'> str[i+1] || str[i+1] > '9') && str[i+1] != ' '){
				// 그러나 )* 와 같은 경우는 각각이 하나이므로 따로 처리.
				// 즉 하나로 보면 안됨 
        		if(is_operator(str+i+1))break;
        		
        		// 읽어올 문자의 길이 1 증가
        		num_of_char++;
        		
        		// 다음에 읽을 문자의 위치도 1증가 
        		i++;
        	};
        	// 읽어온 문자열을 tmp 변수에 복사. 
			strncpy(tmp, str+start_index,num_of_char);
			
			// tmp 문자열의 마지막 위치에 null값을 넣어준다 
        	tmp[num_of_char] = '\0';
        	
        	// pop하기 전에 top element의 fnum을 rhs 피연산자에 대입  
        	second_operand = stack[top].fnum;
        	// 스택 top을 pop 
        	Pop(&top);
        	
        	// pop하기 전에 top element의 fnum을 lhs 피연산자에 대입  
        	first_operand = stack[top].fnum;
        	// 스택 top을 pop 
        	Pop(&top);
        	
        	// 읽어온 연산자의 문자열값에 따라 두 피연산자를 다르게 처리하여 result에 넣는다 
        	if(!strcmp(tmp, "+"))result = first_operand+second_operand;
        	else if(!strcmp(tmp, "-"))result = first_operand-second_operand;
        	else if(!strcmp(tmp, "*"))result = first_operand*second_operand;
        	else if(!strcmp(tmp, "/"))result = first_operand/second_operand;
        	else if(!strcmp(tmp,"AND"))result = first_operand && second_operand;
			else if(!strcmp(tmp,"OR"))result = first_operand || second_operand;
			
			// newElement의 fnum에 결과값을 넣어서 
        	newElement.fnum = result;
        	// 스택에 push해준다 
        	Push(&top, newElement);
        }
    }
    // 마지막 남아있는 스택을 제거. 
    Pop(&top);
    
    // result : 스택에 마지막으로 남아있던 하나의 element의 fnum 
    // result를 반환한다. 
    return result;
}

// 입력받은 infix 식을 검증하는 함수
// 식에 문제가 없다면 -1을 리턴
// 문제가 있다면 문제가 있는 부분의 index를 리턴 
int equation_validation(char *equation){
	int i, not_valid_index = -1;
	
	// 문자열을 한칸씩 옮겨다니며 유효한 문자가 입력되었는지 체크 
	for(i = 0; i < strlen(equation); i++){
		// 숫자인지 검증 
		if('0' <= equation[i] &&equation[i] <= '9')continue;
		
		// 연산자 또는 괄호인지 검증 
		if(equation[i] == '*' || equation[i] == '/' || equation[i] == '+' || equation[i] == '-' || equation[i] == '(' || equation[i] == ')')continue;
		
		// AND인지 검증 
		if(equation[i] == 'A'){
			if(equation[i+1] == 'N' && equation[i+2] == 'D'){
				i = i+2;
				continue;	
			}
		}
		
		//OR인지 검증 
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
