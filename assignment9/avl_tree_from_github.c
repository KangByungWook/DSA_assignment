#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <windows.h>

// �ܾ�� �ǹ̸� ��� ���ܾ� Ÿ�� 
typedef struct Voca{
	// �ܾ��� �̸��� ��� ���� 
	char word[50];
	// �ܾ��� �ǹ̸� ��� ���� 
	char meaning[256];
}Voca;

// avlƮ���� ��� Ÿ�� 
struct avl_node_s {
	struct avl_node_s *left;
	struct avl_node_s *right;
	Voca voc;
};

// avlƮ���� ��� Ÿ���� AvlNode��� ��� 
typedef struct avl_node_s AvlNode;

// avlƮ���� Ʈ��Ÿ��
// root ��带 ������ ���� 
struct avl_tree_s {
	struct avl_node_s *root;
};

// avlƮ���� Ʈ��Ÿ���� AvlTree�� ��� 
typedef struct avl_tree_s AvlTree;




// ���ο� avlƮ���� ���� 
AvlTree *avl_create() {
	AvlTree *tree = NULL;
	// AvlTree ������ �����Ҵ� 
	if( ( tree = malloc( sizeof( AvlTree ) ) ) == NULL ) {
		return NULL;
	}
	
	tree->root = NULL;

	return tree;
}

// ���ο� ��带 �����ϴ� �Լ� 
AvlNode *avl_create_node() {
	AvlNode *node = NULL;
	// AvlNode ������ �����Ҵ�	
	if( ( node = malloc( sizeof( AvlNode ) ) ) == NULL ) {
		return NULL;
	}

	node->left = NULL;
	node->right = NULL;

	return node;	
}

// Avl ����� ���̸� ���ϴ� �Լ� 
int getNodeHeight( AvlNode *node ) {
	int height_left = 0;
	int height_right = 0;
	
	// ����Լ��� �̿��Ͽ� ����� ���̸� ���� 
	if( node->left ) height_left = getNodeHeight( node->left );
	if( node->right ) height_right = getNodeHeight( node->right );
	 
	return height_right > height_left ? ++height_right : ++height_left;
}

// ����� balanceFactor�� ���ϴ� �Լ�
// �������¿� �մ��� üũ 
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

// ������ ������ �����ִ� �Լ� 
AvlNode *AvlBalanceNode( AvlNode *node ) {
	AvlNode *newroot = NULL;

	// �ڽĳ���� ������ �����ش� 
	if( node->left )
		node->left  = AvlBalanceNode( node->left  );
	if( node->right ) 
		node->right = AvlBalanceNode( node->right );

	int bf = getBalanceFactor( node );

	// ���� ����� bf�� �� ū ��� 
	if( bf >= 2 ) {
		if( getBalanceFactor( node->left ) <= -1 ) 
			newroot = RotateLR( node );
		else 
			newroot = RotateLL( node );

	}
	// ������ ����� bf�� �� ū ��� 
	else if( bf <= -2 ) {
		if( getBalanceFactor( node->right ) >= 1 )
			newroot = RotateRL( node );
		else 
			newroot = RotateRR( node );

	}
	// ����� ������ �´� ��� 
	else {
		newroot = node;
	}

	return( newroot );	
}

// �־��� avlƮ���� ������ �����ִ� �Լ� 
void AvlBalance( AvlTree *tree ) {

	AvlNode *newroot = NULL;

	newroot = AvlBalanceNode( tree->root );

	if( newroot != tree->root )  {
		tree->root = newroot; 
	}
}

// ���ο� ��带 �����ϴ� �Լ� 
void AvlInsert( AvlTree *tree, Voca voc ) {
	AvlNode *node = NULL;
	AvlNode *next = NULL;
	AvlNode *last = NULL;

	// ������ ��带 �����ϴ� ��� 
	if( tree->root == NULL ) {
		node = avl_create_node();
		node->voc = voc;

		tree->root = node;
	
	} 
	// root ��尡 �̹� �ִ� ���  
	else {
		next = tree->root;

		while( next != NULL ) {
			last = next;
			
			// ���� ������ �������� �ܾ �ش� ����� �ܾ�� ������ ���� ��� 
			if( strcmp(voc.word, next->voc.word) < 0 ) {
				next = next->left;

			}
			// ���� ������ �������� �ܾ �ش� ����� �ܾ�� ������ ���� ���  
			else if( strcmp(voc.word, next->voc.word) > 0 ) {
				next = next->right;
			}
			// �������� �ܾ �̹� ������ �ִ�  ��� 
			else if( strcmp(voc.word, next->voc.word) == 0 ) {
				/* This shouldn't happen. */
				printf("�̹� �����մϴ�.\n");
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

// �ܾ �˻��ϴ� �Լ� 
AvlNode *AvlFind( AvlTree *tree, char* word ) {
	AvlNode *current = tree->root;
	while( current && strcmp(word, current->voc.word) != 0 ) {
		
		// ���� ������ �˻��Ϸ��� �ܾ �ش� ����� �ܾ�� ������ ���� ��� 
		if( strcmp(word, current->voc.word) > 0 ){
			printf("���� ���  [%s] (���������� �̵�)\n", current->voc.word);
			current = current->right;
		}
		// ���� ������ �˻��Ϸ��� �ܾ �ش� ����� �ܾ�� ������ ���� ��� 
		else{
			printf("���� ���  [%s] (�������� �̵�)\n", current->voc.word);
			current = current->left;
		}	
	}
	// while���� ���� �� current�� NULL�� ��� 
	if(!current){
		printf("\n�ܾ �������� �ʽ��ϴ�.\n\n");
	}
	// NULL�� �ƴ� ��� �ܾ ã�Ҵٴ� �ǹ� 
	else{
		printf("\n�ܾ ã�ҽ��ϴ�\n�ܾ� : %s\n�ǹ�: %s\n", current->voc.word, current->voc.meaning);
		
	} 
	return current;
}

// ���Ϸκ��� �ܾ�� �ܾ��� �ǹ̸� �о�� avlƮ���� ���ʷ� �־��ִ� �Լ� 
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
	
	// �ؽ�Ʈ ������ ������ �� �پ� �д´�. 
    while(fgets(inp,buf_size,fp)){
    	if(strlen(inp) != 1){
            token = strtok(inp, ">");
            int index = 0;
            // ">"�� ���� ���� �ܾ�, �ڴ� �ܾ��� �ǹ� 
            while(token != NULL){
            	if(index == 0){
            		strcpy(voc.word, token);
				}else{
					strcpy(voc.meaning, token);
				}
				token = strtok(NULL,">");
				index++;
			}
			
			// ����� �ܾ�� �ܾ��� �ǹ̸� avlƮ���� �ִ´�. 
			AvlInsert(*root, voc);
        }
    }
    fclose(fp);
}

// inorder ������ node�� Ž��
// ���ĺ� ������ Ž���� �ȴ�. 
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
		printf("1. �ܾ� �߰�\n");
		printf("2. �ܾ� �˻�\n");
		printf("3. �ܾ� ��� ������������ ����\n");
		printf("4. ����\n");
		printf("-----------------------------------\n");
		printf("������ �Ͻðڽ��ϱ�? : ");
		scanf("%s", cmd);
		// �ܾ� �߰� 
		if(strcmp(cmd, "1") == 0){
			system("cls");
			printf("�ܾ� : ");
			scanf("%s", voc.word);
			printf("�ǹ� : ");
			scanf("%s", voc.meaning);
			system("cls"); 
			AvlInsert(tree, voc);
		}
		// �ܾ� �˻� 
		if(strcmp(cmd,"2") == 0){
			system("cls");
			printf("ã�����ϴ� �ܾ� �Է� : ");
			scanf("%s", keyword);
			system("cls");
			AvlFind(tree, keyword);
		}
		// �ܾ� ��� ������������ ����. 
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
