#include <stdio.h>
#include <stdlib.h>
#define max(x,y) ((x)>(y))? (x):(y)

typedef struct AvlNode{
	int data;
	struct AvlNode* left, *right;
}AvlNode;


int getHeight(AvlNode* node){
	int h = 0 ;
	if(node != NULL){
		h = 1 + max(getHeight(node->left), getHeight(node->right));
	}
	return h;
}

int getHeightDiff(AvlNode *node){
	if(node == NULL) return 0;
	return getHeight(node->left) - getHeight(node->right);
}

AvlNode* rotateLL(AvlNode* parent){
	AvlNode* child  = parent->left;
	parent->left = child->right;
	child->right = parent;
	return child;
}

//TODO rotate RR LR
AvlNode* rotateRR(AvlNode* parent){
	AvlNode* child = parent->right;
	parent->right = child->left;
	child->left = parent;
	return child;
}

AvlNode* rotateRL(AvlNode* parent){
	AvlNode* child = parent->right;
	parent->right = rotateLL(child);
	return rotateRR(parent);
}

AvlNode* rotateLR(AvlNode* parent){
	AvlNode* child = parent->left;
	parent->left = rotateRR(child);
	return rotateLL(parent);
}

AvlNode* rebalance(AvlNode** node){
	int heightDiff = getHeightDiff(*node);
	if(heightDiff > 1){
		if(getHeightDiff((*node)->left)>0){
			*node = rotateLL(*node); 
		}else{
			*node = rotateLR(*node);
		}
	}
	else if(heightDiff < -1){
		if(getHeightDiff((*node)->right) < 0){
			*node = rotateRR(*node);
		}else{
			*node = rotateRL(*node);
		}
	}
	
	return *node;
}

//TODO
AvlNode* avlAdd(AvlNode **root, int data){
	if(*root==NULL){
		*root = (AvlNode*)malloc(sizeof(AvlNode));
		if(*root == NULL){
			exit(1);
		}
		(*root)->data = data;
		(*root)->left = (*root)->right = NULL;
	}else if(data < (*root)->data){
		(*root)->left = avlAdd(&((*root)->left), data);
		*root = rebalance(root);
	}else if(data > (*root)->data){
		(*root)->right = avlAdd(&((*root)->right), data);
		*root = rebalance(root);
	}else{
		printf("중복키 삽입 오류\n");
		exit(1);
	}
	return *root;
}

AvlNode *avlSearch(AvlNode* node, int key){
	if(node == NULL)return NULL;
	printf("탐색: %d\n", node->data);
	if(key == node->data) return node;
	else if(key < node->data) return avlSearch(node->left, key);
	else return avlSearch(node->right, key);
}

AvlNode* inorderTraveling(AvlNode* root){
	if(root != NULL){
		inorderTraveling(root->left);
		printf("[%d] ", root->data);
		inorderTraveling(root->right);
	}
}

void main(void){
	AvlNode* root = NULL;
	
	avlAdd(&root, 7);
	avlAdd(&root, 8);
	avlAdd(&root, 9);
	avlAdd(&root, 2);
	avlAdd(&root, 1);
	avlAdd(&root, 5);
	avlAdd(&root, 3);
	avlAdd(&root, 6);
	avlAdd(&root, 4);
	printf("\n검색 : %d\n", avlSearch(root,4)->data);
	printf("\n");
	inorderTraveling(root);
	
	return 0;
}








