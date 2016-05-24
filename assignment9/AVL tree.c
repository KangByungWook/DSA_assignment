#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(x,y) ((x)>(y))? (x):(y)

typedef struct Voca{
	char word[50];
	char meaning[256];
}Voca;

typedef struct AvlNode{
	Voca data;
	struct AvlNode *left, *right;
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


void data_init(AvlNode** root){
	FILE *fp ;
    int index, data;
    char* inp;
    int buf_size = 1024;
    char word[50];
    char meaning[100];
    fp = fopen("eng_voc_sm.txt", "r");
	char* token = NULL;
    inp = malloc(buf_size+5);
    Voca voc;

    while(fgets(inp,buf_size,fp)){
        if(strlen(inp) != 1){
//            printf("------- \n");
//            printf("입력받은 문장 : %s\n" , inp);
//			printf("문자열의 길이 : %d \n" , strlen(inp));
            token = strtok(inp, ">");
            int index = 0;
            while(token != NULL){
            	//printf("token = %s\n", token);
            	
            	if(index == 0){
            		strcpy(voc.word, token);
				}else{
					strcpy(voc.meaning, token);
				}
				token = strtok(NULL,">");
				index++;
			}
			
			avlAdd(root, voc);
			
//			printf("word : %s", word);
//			printf("meaning : %s", meaning);
//			
//			
//            printf("------- \n");
        }
    }
    fclose(fp);
}
void main(void){
	AvlNode* root = NULL;
	printf("data gogo\n");
	data_init(&root);
	printf("data complete\n");
	
	Voca voc;
	char cmd[5], keyword[50];
	while(1){
		printf("-----------------------------------\n"); 
		printf("1. 단어 추가\n");
		printf("2. 단어 검색\n");
		printf("3. 단어 목록 내림차순으로 보기\n");
		printf("4. 종료\n");
		printf("-----------------------------------\n");
		scanf("%s", cmd);
		if(strcmp(cmd, "1") == 0){
			printf("Input the word : ");
			scanf("%s", voc.word);
			printf("Input the meaning : ");
			scanf("%s", voc.meaning);
			avlAdd(&root, voc);
		}
		if(strcmp(cmd,"2") == 0){
			printf("Input the keyword : ");
			scanf("%s", keyword);
			printf("단어 : %s\n", avlSearch(root,keyword)->data.word);
			printf("의미 : %s\n", avlSearch(root,keyword)->data.meaning);
		}
		if(strcmp(cmd,"3") == 0){
			inorderTraveling(root);
		}
		if(strcmp(cmd,"4") == 0){
			break;
		}
	} 
//	voc.word = "apple";
//	voc.meaning = "something";
//	avlAdd(&root, voc);
//	voc.word = "pear";
//	voc.meaning = "something";
//	avlAdd(&root, voc);
//	voc.word = "banana";
//	voc.meaning = "something";
//	avlAdd(&root, voc);
//	voc.word = "pineapple";
//	voc.meaning = "something";
//	avlAdd(&root, voc);
//	voc.word = "grape";
//	voc.meaning = "something";
//	avlAdd(&root, voc);
//	printf("\n검색 : %s\n", avlSearch(root,"your")->data.word);
//	printf("\n");
	
	
	return 0;
}








