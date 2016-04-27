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
			// ��带 �ϳ� ���� 
			node_ptr oper_node = (node_ptr)malloc(sizeof(eval_node));
			
			// ������ ��忡 �����ڸ� �ִ´� 
			oper_node->data = *p_index;
			
			// ���� ������ ���̰� 2�� �̻��� ���. 
			// �� ���� ��带 ���� �����ڸ� �ְ� ������ ���� �ΰ��� ���ڸ� �ڽĳ��� �����ؾ��ϴ� ��� 
			if(get_length(&top) >= 2){
				// ���� �ΰ��� ���ڸ� �����´� 
				rhs = pop(&top);
				lhs = pop(&top);
				
				// ���� �ΰ��� ���ڸ� �ش� ����� �����ڷ� ������ �����ϰ� �̸� �ش� �������� result���� �ִ´� 
				oper_node->result = compute_oper(*p_index, lhs-48, rhs-48);
				
				// ���� �ڽĳ�带 �����Ѵ� 
				node_ptr left_child_node = (node_ptr)malloc(sizeof(eval_node));
				// ���� �ڽ� ��忡 ���ڸ� �ִ´� 
				left_child_node->data = lhs;
				left_child_node->left_child = left_child_node->right_child = NULL;
				
				// ������ �ڽ� ��带 �����Ѵ� 
				node_ptr right_child_node = (node_ptr)malloc(sizeof(eval_node));
				// ������ �ڽ� ��忡 ���ڸ� �ִ´� 
				right_child_node->data = rhs;
				right_child_node->left_child = right_child_node->right_child = NULL;
				
				// ������忡 ���� �ڽ� ���� ������ �ڽ� ��带 �����Ѵ� 
				oper_node->left_child = left_child_node;
				oper_node->right_child = right_child_node;
				
				node_stack_push(oper_node,&node_ptr_stack_top);	
				
		
			}  
			// ���� ������ ���̰� 1�� ��� 
			else if(get_length(&top) == 1){
				// ���� ������ top���� ���ڸ� �ϳ� �����´� 
				rhs = pop(&top);
				
				// ��带 �ϳ� �����Ѵ� 
				node_ptr oper_node = (node_ptr)malloc(sizeof(eval_node));
				// ������ ��忡 �ش� �����ڸ� �ִ´� 
				oper_node->data = *p_index;
				
				// ������ �ڽ� ��带 ����� 
				node_ptr right_child_node = (node_ptr)malloc(sizeof(eval_node));
				// �˸��� �ڽ� ��忡 ���ڽ��ÿ��� ������ ���ڸ� �ִ´� 
				right_child_node->data = rhs;
				right_child_node->left_child = right_child_node->right_child = NULL;
				
				// ���� �ڽ��� ��� ���ÿ��� �ϳ��� pop�Ͽ� �����´� 
				oper_node->left_child = node_stack_pop(&node_ptr_stack_top);
				
				// ������ �ڽĳ�带 �����Ѵ� 
				oper_node->right_child = right_child_node;
				
				// ���� ��忡 �ڽĳ���� result���� ������ ������� �ִ´� 
				oper_node->result = compute_oper(*p_index, oper_node->left_child->result, rhs - 48);
				
				
				// ������ ��� �����͸� ��彺�ÿ� push�Ѵ� 
				node_stack_push(oper_node,&node_ptr_stack_top);
			}
			else{
				// ��带 �ϳ� �����Ѵ� 
				node_ptr oper_node = (node_ptr)malloc(sizeof(eval_node));
				// ������ ��忡 ���ڸ� �ִ´� 
				oper_node->data = *p_index;
				// ��� �������κ��� ������ ��带 �ڽĳ�忡 �������ش� 
				oper_node->right_child = node_stack_pop(&node_ptr_stack_top);
				oper_node->left_child = node_stack_pop(&node_ptr_stack_top);
				
				// �ڽĳ��κ��� ������ result�� �ش� �����ڷ� �������� ������� �����Ѵ� 
				oper_node->result = compute_oper(*p_index, oper_node->left_child->result, oper_node->right_child->result);
				
				
				// ���� ������ ����� �����͸����  ��� ���ÿ� push���ش� 
				node_stack_push(oper_node,&node_ptr_stack_top);
			}
		}
		// �ش� ���ڰ� �ǿ������� ��� ���� ���ÿ� push�Ѵ� 
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

// �����ڿ� �ΰ��� float�� ���ڸ� �޾� ������ ������ �� ������� �������ִ� �Լ� 
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
