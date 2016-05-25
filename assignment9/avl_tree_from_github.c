#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <windows.h>

// 단어와 의미를 담는 영단어 타입 
typedef struct Voca{
	// 단어의 이름을 담는 변수 
	char word[50];
	// 단어의 의미를 담는 변수 
	char meaning[256];
}Voca;

// avl트리의 노드 타입 
struct avl_node_s {
	struct avl_node_s *left;
	struct avl_node_s *right;
	Voca voc;
};

// avl트리의 노드 타입을 AvlNode라고 명명 
typedef struct avl_node_s AvlNode;

// avl트리의 트리타입
// root 노드를 변수로 가짐 
struct avl_tree_s {
	struct avl_node_s *root;
};

// avl트리의 트리타입을 AvlTree로 명명 
typedef struct avl_tree_s AvlTree;




// 새로운 avl트리를 생성 
AvlTree *avl_create() {
	AvlTree *tree = NULL;
	// AvlTree 변수를 동적할당 
	if( ( tree = malloc( sizeof( AvlTree ) ) ) == NULL ) {
		return NULL;
	}
	
	tree->root = NULL;

	return tree;
}

// 새로운 노드를 생성하는 함수 
AvlNode *avl_create_node() {
	AvlNode *node = NULL;
	// AvlNode 변수를 동적할당	
	if( ( node = malloc( sizeof( AvlNode ) ) ) == NULL ) {
		return NULL;
	}

	node->left = NULL;
	node->right = NULL;

	return node;	
}

// Avl 노드의 높이를 구하는 함수 
int getNodeHeight( AvlNode *node ) {
	int height_left = 0;
	int height_right = 0;
	
	// 재귀함수를 이용하여 노드의 높이를 구함 
	if( node->left ) height_left = getNodeHeight( node->left );
	if( node->right ) height_right = getNodeHeight( node->right );
	 
	return height_right > height_left ? ++height_right : ++height_left;
}

// 노드의 balanceFactor를 구하는 함수
// 균형상태에 잇는지 체크 
int getBalanceFactor( AvlNode *node ) {
	int bf = 0;

	if( node->left  ) bf += getNodeHeight( node->left );
	if( node->right ) bf -= getNodeHeight( node->right );

	return bf ;
}

// LL rotate 
AvlNode *RotateLL( AvlNode *node ) {
 	AvlNode *a = node;
	AvlNode *b = a->left;
	
	a->left = b->right;
	b->right = a;

	return( b );
}

// LR rotate
AvlNode *RotateLR( AvlNode *node ) {
	AvlNode *a = node;
	AvlNode *b = a->left;
	AvlNode *c = b->right;
	
	a->left = c->right;
	b->right = c->left; 
	c->left = b;
	c->right = a;

	return( c );
}

// RL rotate
AvlNode *RotateRL( AvlNode *node ) {
	AvlNode *a = node;
	AvlNode *b = a->right;
	AvlNode *c = b->left;
	
	a->right = c->left;
	b->left = c->right; 
	c->right = b;
	c->left = a;

	return( c );
}

// RR rotate
AvlNode *RotateRR( AvlNode *node ) {
	AvlNode *a = node;
	AvlNode *b = a->right;
	
	a->right = b->left;
	b->left = a; 

	return( b );
}

// 노드들의 균형을 맞춰주는 함수 
AvlNode *AvlBalanceNode( AvlNode *node ) {
	AvlNode *newroot = NULL;

	// 자식노드의 균형을 맞춰준다 
	if( node->left )
		node->left  = AvlBalanceNode( node->left  );
	if( node->right ) 
		node->right = AvlBalanceNode( node->right );

	int bf = getBalanceFactor( node );

	// 왼쪽 노드의 bf가 더 큰 경우 
	if( bf >= 2 ) {
		if( getBalanceFactor( node->left ) <= -1 ) 
			newroot = RotateLR( node );
		else 
			newroot = RotateLL( node );

	}
	// 오른쪽 노드의 bf가 더 큰 경우 
	else if( bf <= -2 ) {
		if( getBalanceFactor( node->right ) >= 1 )
			newroot = RotateRL( node );
		else 
			newroot = RotateRR( node );

	}
	// 노드의 균형이 맞는 경우 
	else {
		newroot = node;
	}

	return( newroot );	
}

// 주어진 avl트리의 균형을 맞춰주는 함수 
void AvlBalance( AvlTree *tree ) {

	AvlNode *newroot = NULL;

	newroot = AvlBalanceNode( tree->root );

	if( newroot != tree->root )  {
		tree->root = newroot; 
	}
}

// 새로운 노드를 삽입하는 함수 
void AvlInsert( AvlTree *tree, Voca voc ) {
	AvlNode *node = NULL;
	AvlNode *next = NULL;
	AvlNode *last = NULL;

	// 최초의 노드를 삽입하는 경우 
	if( tree->root == NULL ) {
		node = avl_create_node();
		node->voc = voc;

		tree->root = node;
	
	} 
	// root 노드가 이미 있는 경우  
	else {
		next = tree->root;

		while( next != NULL ) {
			last = next;
			
			// 사전 순서상 넣으려는 단어가 해당 노드의 단어보다 순서가 앞인 경우 
			if( strcmp(voc.word, next->voc.word) < 0 ) {
				next = next->left;

			}
			// 사전 순서상 넣으려는 단어가 해당 노드의 단어보다 순서가 뒤인 경우  
			else if( strcmp(voc.word, next->voc.word) > 0 ) {
				next = next->right;
			}
			// 넣으려는 단어가 이미 사전에 있는  경우 
			else if( strcmp(voc.word, next->voc.word) == 0 ) {
				/* This shouldn't happen. */
				printf("이미 존재합니다.\n");
				break;	
			}
		}

		node = avl_create_node();
		node->voc = voc;

		if( strcmp(voc.word, last->voc.word) < 0 ) last->left = node;
		if( strcmp(voc.word, last->voc.word) > 0 ) last->right = node;
		
	}

	AvlBalance( tree );
}

// 단어를 검색하는 함수 
AvlNode *AvlFind( AvlTree *tree, char* word ) {
	AvlNode *current = tree->root;
	while( current && strcmp(word, current->voc.word) != 0 ) {
		
		// 사전 순서상 검색하려는 단어가 해당 노드의 단어보다 순서가 앞인 경우 
		if( strcmp(word, current->voc.word) > 0 ){
			printf("현재 노드  [%s] (오른쪽으로 이동)\n", current->voc.word);
			current = current->right;
		}
		// 사전 순서상 검색하려는 단어가 해당 노드의 단어보다 순서가 뒤인 경우 
		else{
			printf("현재 노드  [%s] (왼쪽으로 이동)\n", current->voc.word);
			current = current->left;
		}	
	}
	// while문이 끝난 후 current가 NULL인 경우 
	if(!current){
		printf("\n단어가 존재하지 않습니다.\n\n");
	}
	// NULL이 아닌 경우 단어를 찾았다는 의미 
	else{
		printf("\n단어를 찾았습니다\n단어 : %s\n의미: %s\n", current->voc.word, current->voc.meaning);
		
	} 
	return current;
}

// 파일로부터 단어와 단어의 의미를 읽어와 avl트리에 차례로 넣어주는 함수 
void data_init(AvlTree** root){
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
	
	// 텍스트 파일의 내용을 한 줄씩 읽는다. 
    while(fgets(inp,buf_size,fp)){
    	if(strlen(inp) != 1){
            token = strtok(inp, ">");
            int index = 0;
            // ">"를 경계로 앞은 단어, 뒤는 단어의 의미 
            while(token != NULL){
            	if(index == 0){
            		strcpy(voc.word, token);
				}else{
					strcpy(voc.meaning, token);
				}
				token = strtok(NULL,">");
				index++;
			}
			
			// 저장된 단어와 단어의 의미를 avl트리에 넣는다. 
			AvlInsert(*root, voc);
        }
    }
    fclose(fp);
}

// inorder 순서로 node를 탐색
// 알파벳 순으로 탐색이 된다. 
AvlNode* inorderTraveling(AvlNode* root){
	if(root != NULL){
		inorderTraveling(root->left);
		printf("%s : %s \n", root->voc.word, root->voc.meaning);
		inorderTraveling(root->right);
	}
}


int main() {
	AvlTree *tree = NULL;
	int i = 0; 
	int r = 0;
	Voca voc;
	
	tree = avl_create();
	
	data_init(&tree);
	
	char cmd[5], keyword[50];
	while(1){
		printf("-----------------------------------\n");
		printf("1. 단어 추가\n");
		printf("2. 단어 검색\n");
		printf("3. 단어 목록 내림차순으로 보기\n");
		printf("4. 종료\n");
		printf("-----------------------------------\n");
		printf("무엇을 하시겠습니까? : ");
		scanf("%s", cmd);
		// 단어 추가 
		if(strcmp(cmd, "1") == 0){
			system("cls");
			printf("단어 : ");
			scanf("%s", voc.word);
			printf("의미 : ");
			scanf("%s", voc.meaning);
			system("cls"); 
			AvlInsert(tree, voc);
		}
		// 단어 검색 
		if(strcmp(cmd,"2") == 0){
			system("cls");
			printf("찾고자하는 단어 입력 : ");
			scanf("%s", keyword);
			system("cls");
			AvlFind(tree, keyword);
		}
		// 단어 목록 내림차순으로 보기. 
		if(strcmp(cmd,"3") == 0){
			system("cls");
			inorderTraveling(tree->root);
			printf("\n");
		}
		if(strcmp(cmd,"4") == 0){
			break;
		}
	}
	return 0;
}
