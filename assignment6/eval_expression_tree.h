#ifndef EVAL_EXPRESSION_TREE
#define EVAL_EXPRESSION_TREE
#define TRUE 1
#define FALSE 0
#define MAX_STACK_SIZE 100

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "node_stack.h"
#include "eval_expression.h"

node_ptr make_tree(char* postfix);
void inorder_traversal(node_ptr ptr);
node_ptr make_tree(char* postfix){
	// 스택 초기화 
	top = -1;
	
	char* p_index = postfix;
	char lhs, rhs, tmp; 
	while(*p_index != '\0'){
		// 연산자인 경우 
		if(is_oper(*p_index)){
			if(get_length(&top) >= 2){
				rhs = pop(&top);
				lhs = pop(&top);
				node_ptr oper_node = (node_ptr)malloc(sizeof(eval_node));
				oper_node->data = *p_index;
				
				
				node_ptr left_child_node = (node_ptr)malloc(sizeof(eval_node));
				left_child_node->data = lhs;
				left_child_node->left_child = left_child_node->right_child = NULL;
				
				node_ptr right_child_node = (node_ptr)malloc(sizeof(eval_node));
				right_child_node->data = rhs;
				right_child_node->left_child = right_child_node->right_child = NULL;
				
				oper_node->left_child = left_child_node;
				oper_node->right_child = right_child_node;
				
				node_stack_push(oper_node,&node_ptr_stack_top);
				printf("\n노드 스택에 노드 포인터 추가 : %c\n", oper_node->data); 
			} 
			else if(get_length(&top) == 1){
				rhs = pop(&top);
				node_ptr oper_node = (node_ptr)malloc(sizeof(eval_node));
				oper_node->data = *p_index;
				
				node_ptr right_child_node = (node_ptr)malloc(sizeof(eval_node));
				right_child_node->data = rhs;
				right_child_node->left_child = right_child_node->right_child = NULL;
				
				oper_node->left_child = node_stack_pop(&node_ptr_stack_top);
				oper_node->right_child = right_child_node;
				
				
				
				node_stack_push(oper_node,&node_ptr_stack_top);
				printf("\n노드 스택에 노드 포인터 추가 : %c\n", oper_node->data); 
			}
			else{
				printf("노드 포인터끼리 합치기\n");
				node_ptr oper_node = (node_ptr)malloc(sizeof(eval_node));
				oper_node->data = *p_index;
				oper_node->right_child = node_stack_pop(&node_ptr_stack_top);
				oper_node->left_child = node_stack_pop(&node_ptr_stack_top);
				
				
				node_stack_push(oper_node,&node_ptr_stack_top);
			}
		}
		// 피연산자인 경우
		else{
			push(*p_index, &top);
		} 
		p_index++;
	}
	return node_ptr_stack[0];
}

void preorder_traversal(node_ptr ptr){
	if(ptr){
		printf("%c", ptr->data);
		preorder_traversal(ptr->left_child);
		inorder_traversal(ptr->right_child);
	}
}

void inorder_traversal(node_ptr ptr){
	if(ptr){
		inorder_traversal(ptr->left_child);
		printf("%c", ptr->data);
		inorder_traversal(ptr->right_child);
	}
}

void postorder_traversal(node_ptr ptr){
	if(ptr){
		postorder_traversal(ptr->left_child);
		postorder_traversal(ptr->right_child);
		printf("%c", ptr->data);
	}
}

#endif
