#include <stdio.h.>
#include <stdlib.h>

#include "evaluation_of_expression.h"
#include "stack.h"

int main(){
	char cmd[100]; 
	printf("�� �Է� : ");
	scanf("%s", &cmd);
	printf("Postfix : ");
	prefix_to_postfix(cmd);
	printf("%s\n", postFix);
	printf("����� : %f\n", calculate_postfix(postFix));
	
	
	return 0;
}
