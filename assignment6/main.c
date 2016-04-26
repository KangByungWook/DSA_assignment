#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "eval_expression.h"
#include "eval_expression_tree.h"

int main(){
	char cmd[100];
	scanf("%s", cmd);
	infix_to_postfix(cmd);
	printf("postFix에 저장된 값 : %s", postFix);
	node_ptr tmp = make_tree(postFix);
	
	inorder_traversal(tmp);
	}
