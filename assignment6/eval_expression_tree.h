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

// postfix���� �޾ƿͼ� Ʈ���� ������ִ� �Լ� 
node_ptr make_tree(char* postfix);
// inorder ������ Ʈ���� ������ִ� �Լ� 
void inorder_traversal(node_ptr ptr);
// postorder ������ Ʈ���� ������ִ� �Լ�
void postorder_traversal(node_ptr ptr);
// preorder ������ Ʈ���� ������ִ� �Լ�
void preorder_traversal(node_ptr ptr);
// ���� ����� result�� �Ǵ� ���ڸ� ������ ����Ͽ� ���� ����� result���� �����ϴ� �Լ� 
float compute_oper(char oper, float lhs, float rhs);

// postfix���� ������ Ʈ���� ������ִ� �Լ� 
node_ptr make_tree(char* postfix){
	// ���� �ʱ�ȭ 
	top = -1;
	
	// Ž���� ������ ��ġ�� postfix���� ù��° ���ڷ� �ʱ�ȭ 
	char* p_index = postfix;
	char lhs, rhs, tmp; 
	
	// ù��° ���ں��� Ž�� ���� 
	while(*p_index != '\0'){
		// �ش� ���ڰ� �������� ��� 
		if(is_oper(*p_index)){
			if(get_length(&top) >= 2){
				rhs = pop(&top);
				lhs = pop(&top);
				node_ptr oper_node = (node_ptr)malloc(sizeof(eval_node));
				oper_node->data = *p_index;
				float f_lhs = lhs-48;
				float f_rhs = rhs-48;
				oper_node->result = compute_oper(*p_index, f_lhs, f_rhs);
				
				node_ptr left_child_node = (node_ptr)malloc(sizeof(eval_node));
				left_child_node->data = lhs;
				left_child_node->left_child = left_child_node->right_child = NULL;
				
				node_ptr right_child_node = (node_ptr)malloc(sizeof(eval_node));
				right_child_node->data = rhs;
				right_child_node->left_child = right_child_node->right_child = NULL;
				
				oper_node->left_child = left_child_node;
				oper_node->right_child = right_child_node;
				
				node_stack_push(oper_node,&node_ptr_stack_top);
				printf("\n��� ���ÿ� ��� ������ �߰� : %c\n", oper_node->data); 
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
				
				oper_node->result = compute_oper(*p_index, oper_node->left_child->result, rhs - 48);
				
				node_stack_push(oper_node,&node_ptr_stack_top);
				printf("\n��� ���ÿ� ��� ������ �߰� : %c\n", oper_node->data); 
			}
			else{
				printf("��� �����ͳ��� ��ġ��\n");
				node_ptr oper_node = (node_ptr)malloc(sizeof(eval_node));
				oper_node->data = *p_index;
				oper_node->right_child = node_stack_pop(&node_ptr_stack_top);
				oper_node->left_child = node_stack_pop(&node_ptr_stack_top);
				
				oper_node->result = compute_oper(*p_index, oper_node->left_child->result, oper_node->right_child->result);
				node_stack_push(oper_node,&node_ptr_stack_top);
			}
		}
		// �ش� ���ڰ� �ǿ������� ���
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

float compute_oper(char oper, float lhs, float rhs){
	float result;
	switch(oper){
		case '+':
			return lhs+rhs;
		case'-':
			return lhs-rhs;
		case '*':
			return lhs*rhs;
		case '/':
			return lhs/rhs;
	}
}
#endif
