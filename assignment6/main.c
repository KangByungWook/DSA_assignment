#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "eval_expression.h"
#include "eval_expression_tree.h"

int main(){
	char cmd[100];
	printf("ют╥б : ");scanf("%s", cmd);
	infix_to_postfix(cmd);
	node_ptr tmp = make_tree(postFix);
	
	printf("Preorder traversal : ");preorder_traversal(tmp);printf("\n");
	printf("Inorder traversal : ");inorder_traversal(tmp);printf("\n");
	printf("Postorder traversal : ");postorder_traversal(tmp);printf("\n");
	printf("Evaluation test : %f", tmp->result);
}
