#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR 10
#define MAX_ELEMENT 100
#define MAX_HEAP_SIZE 100 
#define TRUE 1
#define FALSE 0

typedef struct element* element_ptr;
// hash ���̺��� ���� Ÿ��
// key�� ���ĺ�, value�� �󵵼��� ��� ���� 
typedef struct element{
	char key;
	int value;
	element_ptr left_child, right_child;
	int is_leaf;
}element;



// heap�� ���� ������ ��� Ÿ���� ���� 
typedef struct HeapType{
	element_ptr heap[MAX_HEAP_SIZE];
	int heap_size;
}HeapType;


// hash ���̺� �迭 
// element������ ����Ű�� �����ͺ��� �迭 
element hash_table[MAX_ELEMENT];

// element������ key���� �޾Ƽ� ���ڷ� ��ȯ���ִ� �Լ�
// �̶� ��ȯ�Ǵ� ���ڴ� �ش� char�� �ƽ�Ű�ڵ� �� 
int transform(char key){
	int number = key;
	return number;
}

// element������ �޾Ƽ� hash_table�� �� ��ġ�� ��ȯ���ִ� �Լ� 
int hash(element e){
	return transform(e.key) % MAX_ELEMENT;
}

// element������ hash���̺� �����ϴ� �Լ� 
void hash_table_insert(element table[], element e){
	// �ش� element������ �� ��ġ�� �Ǵ� 
	int index = hash(e);
	// �ش� ��ġ�� �ִ� ������ key���� �����Ϸ��� element�� key���� ������ �ߺ����� �߻���Ŵ 
	if(table[index].key == e.key){
		printf("key duplicated\n");
		exit(1);
	}
	// �ش� ��ġ�� �ٸ� element ������ �ִٸ� ����ִ� ��ġ�� ���ö����� ���� Ž�� 
	while(!(table+index)){
		index  = (index+1) % MAX_ELEMENT;
		
		// ���� ó���ڸ��� �ٽ� �ǵ��ƿԴٸ� ���̺��� �����ִٴ� �ǹ��̹Ƿ� ���� �޽��� ����� ���α׷� ����. 
		if(index == hash(e)){
			printf("hash table is full\n");
			exit(1);
		}
	}
	// ������ ��ġ�� ã�Ҵٸ� �ش� ��ġ�� element�� ���� 
	table[index] = e;
}


// Heap ���� ����. 
// HeapType ������ �ʱ�ȭ���ִ� �Լ� 
void init(HeapType *h){
	h->heap_size = 0;
}

// HeapType�� heap�迭���� element���� �ڸ��� ���� �ٲٴ� �Լ� 
void swap(element_ptr *a, element_ptr *b){
	element_ptr tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

// HeapType heap�迭�� ������ ��ġ�� element ������ �����ϴ� �Լ� 
void insert_element(HeapType *h, element_ptr e_ptr){
	int i = ++h->heap_size;
	h->heap[i] = e_ptr;
	
	while(i != 1){
		// ���� �θ� ����� value��(�󵵼�)�� �� ũ�� �θ���� ��ġ�� �ٲ۴� 
		if((h->heap[i])->value < (h->heap[i/2])->value){
			swap(h->heap + i, h->heap + i/2);
			i/=2;
		}
		else break;
	}
	
}

element_ptr delete_node(HeapType *h){
	element_ptr tmp;
	int index = 1;
	// �ʱ�ȭ ����
	int i = (h->heap_size)--;
	tmp = h->heap[1];
	h->heap[1] = h->heap[i];
	
	// �ڱ� �ڸ��� ã�ư��� ����
	while(1){
		// left node�� value�� �ڽź��� ���� ��� 
		if(index * 2 <= h->heap_size && (h->heap[index])->value > (h->heap[index*2])->value && (h->heap[index*2])->value < (h->heap[index*2 + 1])->value ){
			swap(h->heap + index, h->heap + index*2);
			index *= 2;
		}
		// right node�� value�� �ڽź��� ���� ��� 
		else if(index * 2 + 1 <= h->heap_size && (h->heap[index])->value > (h->heap[index*2 + 1])->value && (h->heap[index*2])->value > (h->heap[index*2 + 1])->value ){
			swap(h->heap + index, h->heap + index*2 + 1);
			index *= 2;
			index++;
		}
		else break;
		
	}
	return tmp;
}

element_ptr get_root_node(HeapType *h) {
	// ���� �� �������� �ΰ��� �����鼭 Ʈ���� �����.
	if (h->heap_size == 0) {
		printf("Heap empty!!\n");
		exit(1);
	}
	while (h->heap_size > 1) {
		element_ptr new_node = (element_ptr)malloc(sizeof(element));
		element_ptr left_node_ptr = delete_node(h);
		element_ptr right_node_ptr = delete_node(h);
		new_node->left_child = left_node_ptr;
		new_node->right_child = right_node_ptr;
		new_node->value = left_node_ptr->value + right_node_ptr->value;
		new_node->is_leaf = FALSE;
		
		insert_element(h, new_node);
	}
	return h->heap[1];
}


void PrintTree(element_ptr h, int i, char *pCode)
{
	if (h)
	{
		i++;
		pCode[i] = '1';
		PrintTree(h->left_child, i, pCode);
		pCode[i] = '0';
		PrintTree(h->right_child, i, pCode);
		pCode[i] = '\0';

		if (h->left_child == NULL && h->right_child == NULL)
		{
			printf("%3c\t%3d\t%s\n", h->key, h->value, pCode);
		}
	}
}

int main(){
	element tmp = { 'a', 278, NULL, NULL, TRUE },
			tmp2 = { 'b', 42, NULL, NULL, TRUE },
			tmp3 = { 'c', 65, NULL, NULL, TRUE },
			tmp4 = { 'd', 745, NULL, NULL, TRUE },
			tmp5 = { 'e', 34, NULL, NULL, TRUE },
			tmp6 = { 'f', 65, NULL, NULL, TRUE },
			tmp7 = { 'g', 35, NULL, NULL, TRUE },
			tmp8 = { 'h', 97, NULL, NULL, TRUE },
			tmp9 = { 'i', 65, NULL, NULL, TRUE };
	
	int i;
	char binaryCode[100];
	tmp.key = 'a';
	tmp.value = 2;
	hash_table_insert(hash_table, tmp);
	printf("%d\n", hash(tmp));
	printf("%d", hash_table[hash(tmp)].value);
	
	HeapType *Heap_ptr = (HeapType*)malloc(sizeof(HeapType));
	init(Heap_ptr);
	element_ptr p_elenment = &tmp;
	insert_element(Heap_ptr, p_elenment);
	p_elenment = &tmp2;
	insert_element(Heap_ptr, p_elenment);
	p_elenment = &tmp3;
	insert_element(Heap_ptr, p_elenment);
	p_elenment = &tmp4;
	insert_element(Heap_ptr, p_elenment);
	p_elenment = &tmp5;
	insert_element(Heap_ptr, p_elenment);
	p_elenment = &tmp6;
	insert_element(Heap_ptr, p_elenment);
	p_elenment = &tmp7;
	insert_element(Heap_ptr, p_elenment);
	p_elenment = &tmp8;
	insert_element(Heap_ptr, p_elenment);
	p_elenment = &tmp9;
	insert_element(Heap_ptr, p_elenment);

	
	 
	printf("\n--------\n");
	for(i = 1 ; i <= Heap_ptr->heap_size; i++){
		printf("%d ", (Heap_ptr->heap[i])->value);
	}
	
	delete_node(Heap_ptr);
	
	element_ptr root = get_root_node(Heap_ptr);

	printf("value : %d\n", (root->left_child)->value);

	PrintTree(root, -1, binaryCode);
	system("pause");
	return 0;
}
