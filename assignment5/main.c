#include <stdio.h.>
#include <stdlib.h>

#include "evaluation_of_expression.h"
#include "stack.h"

int main(){
	char equation[100]; 
	while(1){
		printf("==============Infix to postfix calculator==============\n");
		printf("infix�� ������� �Է����ּ���.( ���α׷� ���� : q )\n => ");
		scanf("%s", &equation);
		if(!strcmp(equation,"q"))break; 
		
		// �Է¹���  infix ���� ���� 
		int valid_check = equation_validation(equation);
		
		// ���ϰ��� -1�� ��� �Ŀ��� �����Ǵ� �κ��� ���ٴ� �ǹ�. 
		if(valid_check == -1){
			printf("Postfix : ");
			infix_to_postfix(equation);
			printf("%s\n", postFix);
			printf("����� : %f\n", calculate_postfix(postFix));
			
			// ���� �ʱ�ȭ 
			while(!isEmpty(stack))Pop(&top);
			
			//postFix ���ڿ� �ʱ�ȭ 
			postFix[0] = '\0';
		}
		
		// ���ϰ��� -1�� �ƴ� ��� �Ŀ��� ������ �Ǵ� ��ġ�� ã�Ҵٴ� �ǹ�. 
		else{
			printf("��ȿ���� ���� equation ���Դϴ�.\n");
			// �Է¹��� ���ڿ����� ������ �߻��� ��ġ�� �˷���. 
			printf("���� ��ġ : %d\n", valid_check);
		}
	}
	
	printf("���� �Ϸ� �Ǽ���.\n");
	return 0;
}
