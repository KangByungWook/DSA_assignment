#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <windows.h>

typedef struct Voca{
	char word[50];
	char meaning[256];
}Voca;

struct avl_node_s {
	struct avl_node_s *left;
	struct avl_node_s *right;
	Voca voc;
};

typedef struct avl_node_s AvlNode;

struct avl_tree_s {
	struct avl_node_s *root;
};

typedef struct avl_tree_s AvlTree;




/* Create a new AVL tree. */
AvlTree *avl_create() {
	AvlTree *tree = NULL;

	if( ( tree = malloc( sizeof( AvlTree ) ) ) == NULL ) {
		return NULL;
	}

	tree->root = NULL;

	return tree;
}

/* Initialize a new node. */
AvlNode *avl_create_node() {
	AvlNode *node = NULL;
	
	if( ( node = malloc( sizeof( AvlNode ) ) ) == NULL ) {
		return NULL;
	}

	node->left = NULL;
	node->right = NULL;
//	node->voc.meaning = "";
//	node->voc.word = "";

	return node;	
}

/* Find the height of an AVL node recursively */
int getNodeHeight( AvlNode *node ) {
	int height_left = 0;
	int height_right = 0;

	if( node->left ) height_left = getNodeHeight( node->left );
	if( node->right ) height_right = getNodeHeight( node->right );

	return height_right > height_left ? ++height_right : ++height_left;
}

/* Find the balance of an AVL node */
int getBalanceFactor( AvlNode *node ) {
	int bf = 0;

	if( node->left  ) bf += getNodeHeight( node->left );
	if( node->right ) bf -= getNodeHeight( node->right );

	return bf ;
}

/* Left Left Rotate */
AvlNode *RotateLL( AvlNode *node ) {
 	AvlNode *a = node;
	AvlNode *b = a->left;
	
	a->left = b->right;
	b->right = a;

	return( b );
}

/* Left Right Rotate */
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

/* Right Left Rotate */
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

/* Right Right Rotate */
AvlNode *RotateRR( AvlNode *node ) {
	AvlNode *a = node;
	AvlNode *b = a->right;
	
	a->right = b->left;
	b->left = a; 

	return( b );
}

/* Balance a given node */
AvlNode *AvlBalanceNode( AvlNode *node ) {
	AvlNode *newroot = NULL;

	/* Balance our children, if they exist. */
	if( node->left )
		node->left  = AvlBalanceNode( node->left  );
	if( node->right ) 
		node->right = AvlBalanceNode( node->right );

	int bf = getBalanceFactor( node );

	if( bf >= 2 ) {
		/* Left Heavy */	

		if( getBalanceFactor( node->left ) <= -1 ) 
			newroot = RotateLR( node );
		else 
			newroot = RotateLL( node );

	} else if( bf <= -2 ) {
		/* Right Heavy */

		if( getBalanceFactor( node->right ) >= 1 )
			newroot = RotateRL( node );
		else 
			newroot = RotateRR( node );

	} else {
		/* This node is balanced -- no change. */

		newroot = node;
	}

	return( newroot );	
}

/* Balance a given tree */
void AvlBalance( AvlTree *tree ) {

	AvlNode *newroot = NULL;

	newroot = AvlBalanceNode( tree->root );

	if( newroot != tree->root )  {
		tree->root = newroot; 
	}
}

/* Insert a new node. */
void AvlInsert( AvlTree *tree, Voca voc ) {
	AvlNode *node = NULL;
	AvlNode *next = NULL;
	AvlNode *last = NULL;

	/* Well, there must be a first case */ 	
	if( tree->root == NULL ) {
		node = avl_create_node();
		node->voc = voc;

		tree->root = node;

	/* Okay.  We have a root already.  Where do we put this? */
	} else {
		next = tree->root;

		while( next != NULL ) {
			last = next;

			if( strcmp(voc.word, next->voc.word) < 0 ) {
				next = next->left;

			} else if( strcmp(voc.word, next->voc.word) > 0 ) {
				next = next->right;

			/* Have we already inserted this node? */
			} else if( strcmp(voc.word, next->voc.word) == 0 ) {
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

/* Find the node containing a given voc */
AvlNode *AvlFind( AvlTree *tree, char* word ) {
	AvlNode *current = tree->root;
	//printf("Avl tree 를 이용한 단어 탐색 시작\n");
	while( current && strcmp(word, current->voc.word) != 0 ) {
		
		if( strcmp(word, current->voc.word) > 0 ){
			printf("현재 노드  [%s] (오른쪽으로 이동)\n", current->voc.word);
			current = current->right;
		}
		else{
			printf("현재 노드  [%s] (왼쪽으로 이동)\n", current->voc.word);
			current = current->left;
		}	
	}
	if(!current){
		printf("\n단어가 존재하지 않습니다.\n\n");
	}
	else{
		printf("\n단어를 찾았습니다\n단어 : %s\n의미: %s\n", current->voc.word, current->voc.meaning);
		
	} 
	//printf("Avl tree 를 이용한 단어 탐색 끝\n");
	return current;
}

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
	
    while(fgets(inp,buf_size,fp)){
        if(strlen(inp) != 1){
            token = strtok(inp, ">");
            int index = 0;
            while(token != NULL){
            	if(index == 0){
            		strcpy(voc.word, token);
				}else{
					strcpy(voc.meaning, token);
				}
				token = strtok(NULL,">");
				index++;
			}
			
			AvlInsert(*root, voc);
        }
    }
    fclose(fp);
}

AvlNode* inorderTraveling(AvlNode* root){
	if(root != NULL){
		inorderTraveling(root->left);
		printf("%s : %s \n", root->voc.word, root->voc.meaning);
		inorderTraveling(root->right);
	}
}


int main( int argc, char **argv ) {
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
		if(strcmp(cmd, "1") == 0){
			system("cls");
			printf("단어 : ");
			scanf("%s", voc.word);
			printf("의미 : ");
			scanf("%s", voc.meaning);
			system("cls"); 
			AvlInsert(tree, voc);
		}
		if(strcmp(cmd,"2") == 0){
			system("cls");
			printf("찾고자하는 단어 입력 : ");
			scanf("%s", keyword);
			system("cls");
			AvlFind(tree, keyword);
		}
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
