#include <stdio.h.>
#include <stdlib.h>

#include "evaluation_of_expression.h"
#include "stack.h"

int main(){
	char cmd[100]; 
	printf("식 입력 : ");
	scanf("%s", &cmd);
	printf("Postfix : ");
	prefix_to_postfix(cmd);
	printf("%s\n", postFix);
	printf("계산결과 : %f\n", calculate_postfix(postFix));
	
	
	return 0;
}
