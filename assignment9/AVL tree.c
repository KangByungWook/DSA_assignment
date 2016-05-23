#include <stdio.h>
#include <stdlib.h>
#define max(x,y) ((x)>(y))? (x):(y)

typedef struct Voca{
	char* word;
	char* meaning;
}Voca;

typedef struct AvlNode{
	Voca data;
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
AvlNode* avlAdd(AvlNode **root, Voca data){
	if(*root==NULL){
		*root = (AvlNode*)malloc(sizeof(AvlNode));
		if(*root == NULL){
			exit(1);
		}
		(*root)->data = data;
		(*root)->left = (*root)->right = NULL;
	}else if(strcmp(data.word, (*root)->data.word) < 0){
		(*root)->left = avlAdd(&((*root)->left), data);
		*root = rebalance(root);
	}else if(strcmp(data.word, (*root)->data.word) > 0){
		(*root)->right = avlAdd(&((*root)->right), data);
		*root = rebalance(root);
	}else{
		printf("중복키 삽입 오류\n");
		exit(1);
	}
	return *root;
}

AvlNode *avlSearch(AvlNode* node, char word[]){
	if(node == NULL)return NULL;
	printf("탐색: %s\n", node->data.word);
	if(!strcmp(word, node->data.word)) return node;
	else if(strcmp(word, node->data.word) < 0) return avlSearch(node->left, word);
	else return avlSearch(node->right, word);
}

AvlNode* inorderTraveling(AvlNode* root){
	if(root != NULL){
		inorderTraveling(root->left);
		printf("[%s] ", root->data.word);
		inorderTraveling(root->right);
	}
}

void main(void){
	AvlNode* root = NULL;
	Voca voc;
	voc.word = "apple";
	voc.meaning = "something";
	avlAdd(&root, voc);
	voc.word = "pear";
	voc.meaning = "something";
	avlAdd(&root, voc);
	voc.word = "banana";
	voc.meaning = "something";
	avlAdd(&root, voc);
	voc.word = "pineapple";
	voc.meaning = "something";
	avlAdd(&root, voc);
	voc.word = "grape";
	voc.meaning = "something";
	avlAdd(&root, voc);
	printf("\n검색 : %s\n", avlSearch(root,"grape")->data.word);
	printf("\n");
	inorderTraveling(root);
	
	return 0;
}








