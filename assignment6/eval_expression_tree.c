#ifndef EVAL_EXPRESSION_TREE
#define EVAL_EXPRESSION_TREE
#define TRUE 1
#define FALSE 0
#define MAX_STACK_SIZE 100

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "eval_expression_tree.h"

typedef struct eval_node* node_ptr;
typedef struct {
	char data;
	node_ptr left_child, right_child;
}eval_node;

node_ptr node_ptr_stack[MAX_STACK_SIZE];
int node_ptr_stack_top = -1;

node_ptr make_tree(char* postfix){
	// 스택 초기화 
	top = -1;
	char* p_index = postfix;
	char lhs, rhs; 
	while(*p_index != '\0'){
		// 연산자인 경우 
		if(is_oper(*p_index)){
			if(get_length(&top) >= 2){
				rhs = pop(&top);
				lhs = pop(&top);
				node_ptr oper_node = (node_ptr)malloc(sizeof(eval_node));
				node_ptr left_child_node = (node_ptr)malloc(sizeof(eval_node));
				node_ptr right_child_node = (node_ptr)malloc(sizeof(eval_node));
				oper_node->data = *p_index;
				oper_node->left_child = left_child_node;
				oper_node->right_child = right_child_node;
				left_child_node->data = lhs;
				right_child_node->data = rhs;
				left_child_node->left_child = left_child_node->right_child = NULL;
				right_child_node->left_child = right_child_node->right_child = NULL;
				node_ptr_stack[++node_ptr_stack_top] = oper_node;
			}
			else if(get_length(&top) == 1){
				rhs = pop(&top);
				node_ptr oper_node = (node_ptr)malloc(sizeof(eval_node));
				node_ptr right_child_node = (node_ptr)malloc(sizeof(eval_node));
				oper_node->data = *p_index;
				oper_node->left_child = node_ptr_stack[node_ptr_stack_top--];
				oper_node->right_child = right_child_node;
				right_child_node->data = rhs;
				right_child_node->left_child = right_child_node->right_child = NULL;
				node_ptr_stack[++node_ptr_stack_top] = oper_node;
			}
			else{
				node_ptr oper_node = (node_ptr)malloc(sizeof(eval_node));
				oper_node->right_child = node_ptr_stack[node_ptr_stack_top--];
				oper_node->left_child = node_ptr_stack[node_ptr_stack_top--];
			}
		}
		// 피연산자인 경우
		else{
			push(*p_index, &top)
		} 
		p_index++;
	}
}

#endif
