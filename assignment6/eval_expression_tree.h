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

// postfix식을 받아와서 트리로 만들어주는 함수 
node_ptr make_tree(char* postfix);
// inorder 순서로 트리를 출력해주는 함수 
void inorder_traversal(node_ptr ptr);
// postorder 순서로 트리를 출력해주는 함수
void postorder_traversal(node_ptr ptr);
// preorder 순서로 트리를 출력해주는 함수
void preorder_traversal(node_ptr ptr);
// 하위 노드의 result값 또는 숫자를 가져와 계산하여 상위 노드의 result값에 저장하는 함수 
float compute_oper(char oper, float lhs, float rhs);
 
// postfix식을 가져와 트리로 만들어주는 함수 
node_ptr make_tree(char* postfix){
	// 스택 초기화 
	top = -1;
	
	// 탐색을 시작할 위치를 postfix식의 첫번째 문자로 초기화 
	char* p_index = postfix;
	char lhs, rhs, tmp; 
	
	// 첫번째 문자부터 탐색 시작 
	while(*p_index != '\0'){
		// 해당 문자가 연산자인 경우 
		if(is_oper(*p_index)){
			// 노드를 하나 생성 
			node_ptr oper_node = (node_ptr)malloc(sizeof(eval_node));
			
			// 생성한 노드에 연산자를 넣는다 
			oper_node->data = *p_index;
			
			// 문자 스택의 길이가 2개 이상인 경우. 
			// 즉 상위 노드를 만들어서 연산자를 넣고 스택의 상위 두개의 숫자를 자식노드로 연결해야하는 경우 
			if(get_length(&top) >= 2){
				// 상위 두개의 숫자를 가져온다 
				rhs = pop(&top);
				lhs = pop(&top);
				
				// 상위 두개의 숫자를 해당 노드의 연산자로 연산을 수행하고 이를 해당 연산자의 result값에 넣는다 
				oper_node->result = compute_oper(*p_index, lhs-48, rhs-48);
				
				// 왼쪽 자식노드를 생성한다 
				node_ptr left_child_node = (node_ptr)malloc(sizeof(eval_node));
				// 왼쪽 자신 노드에 숫자를 넣는다 
				left_child_node->data = lhs;
				left_child_node->left_child = left_child_node->right_child = NULL;
				
				// 오른쪽 자식 노드를 생성한다 
				node_ptr right_child_node = (node_ptr)malloc(sizeof(eval_node));
				// 오른쪽 자식 노드에 숫자를 넣는다 
				right_child_node->data = rhs;
				right_child_node->left_child = right_child_node->right_child = NULL;
				
				// 상위노드에 왼쪽 자식 노드와 오른쪽 자식 노드를 연결한다 
				oper_node->left_child = left_child_node;
				oper_node->right_child = right_child_node;
				
				node_stack_push(oper_node,&node_ptr_stack_top);	
				
		
			}  
			// 문자 스택의 길이가 1인 경우 
			else if(get_length(&top) == 1){
				// 문자 스택의 top에서 숫자를 하나 꺼내온다 
				rhs = pop(&top);
				
				// 노드를 하나 생성한다 
				node_ptr oper_node = (node_ptr)malloc(sizeof(eval_node));
				// 생성한 노드에 해당 연산자를 넣는다 
				oper_node->data = *p_index;
				
				// 오른쪽 자식 노드를 만든다 
				node_ptr right_child_node = (node_ptr)malloc(sizeof(eval_node));
				// 옹른쪽 자식 노드에 문자스택에서 가져온 문자를 넣는다 
				right_child_node->data = rhs;
				right_child_node->left_child = right_child_node->right_child = NULL;
				
				// 왼쪽 자식은 노드 스택에서 하나를 pop하여 가져온다 
				oper_node->left_child = node_stack_pop(&node_ptr_stack_top);
				
				// 오른쪽 자식노드를 연결한다 
				oper_node->right_child = right_child_node;
				
				// 상위 노드에 자식노드의 result값을 연산한 결과값을 넣는다 
				oper_node->result = compute_oper(*p_index, oper_node->left_child->result, rhs - 48);
				
				
				// 생성한 노드 포인터를 노드스택에 push한다 
				node_stack_push(oper_node,&node_ptr_stack_top);
			}
			else{
				// 노드를 하나 생성한다 
				node_ptr oper_node = (node_ptr)malloc(sizeof(eval_node));
				// 생성한 노드에 문자를 넣는다 
				oper_node->data = *p_index;
				// 노드 스택으로부터 가져온 노드를 자식노드에 연결해준다 
				oper_node->right_child = node_stack_pop(&node_ptr_stack_top);
				oper_node->left_child = node_stack_pop(&node_ptr_stack_top);
				
				// 자식노드로부터 가져온 result를 해당 연산자로 수행한후 결과값을 저장한다 
				oper_node->result = compute_oper(*p_index, oper_node->left_child->result, oper_node->right_child->result);
				
				
				// 새로 생성한 노드의 포인터면수를  노드 스택에 push해준다 
				node_stack_push(oper_node,&node_ptr_stack_top);
			}
		}
		// 해당 문자가 피연산자인 경우 문자 스택에 push한다 
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

// 연산자와 두개의 float형 숫자를 받아 연산을 수행한 후 결과값을 리턴해주는 함수 
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
