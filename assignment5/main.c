#include <stdio.h.>
#include <stdlib.h>

#include "evaluation_of_expression.h"
#include "stack.h"

int main(){
	char equation[100]; 
	while(1){
		printf("==============Infix to postfix calculator==============\n");
		printf("infix를 공백없이 입력해주세요.( 프로그램 종료 : q )\n => ");
		scanf("%s", &equation);
		if(!strcmp(equation,"q"))break; 
		
		// 입력받은  infix 식을 검증 
		int valid_check = equation_validation(equation);
		
		// 리턴값이 -1인 경우 식에서 문제되는 부분이 없다는 의미. 
		if(valid_check == -1){
			printf("Postfix : ");
			infix_to_postfix(equation);
			printf("%s\n", postFix);
			printf("계산결과 : %f\n", calculate_postfix(postFix));
			
			// 스택 초기화 
			while(!isEmpty(stack))Pop(&top);
			
			//postFix 문자열 초기화 
			postFix[0] = '\0';
		}
		
		// 리턴값이 -1이 아닌 경우 식에서 문제가 되는 위치를 찾았다는 의미. 
		else{
			printf("유효하지 않은 equation 식입니다.\n");
			// 입력받은 문자열에서 에러가 발생한 위치를 알려줌. 
			printf("에러 위치 : %d\n", valid_check);
		}
	}
	
	printf("좋은 하루 되세요.\n");
	return 0;
}
