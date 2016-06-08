#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR 10
#define MAX_ELEMENT 10000
#define MAX_HEAP_SIZE 10000 
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
	char bincode[100];
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

// element������ �޾Ƽ� hash_table�� ����ִ� ��ġ�� ��ȯ���ִ� �Լ� 
int find_location_with_element(element e){
	return transform(e.key) % MAX_ELEMENT;
}

int find_location_with_key(element hash_table[], char key) {
	int index = transform(key) % MAX_ELEMENT;
	while (hash_table[index].key != key) {
		index++;
		index %= MAX_ELEMENT;
		if (index == transform(key) % MAX_ELEMENT) {
			//printf("�ش� key�� ���� element�� �����ϴ�.\n");
			return -1;
		}
	}
	return index;
}


// element������ hash���̺� �����ϴ� �Լ� 
void hash_table_insert(element table[], element e){
	// �ش� element������ �� ��ġ�� �Ǵ� 
	int index = find_location_with_element(e);
	// �ش� ��ġ�� �ִ� ������ key���� �����Ϸ��� element�� key���� ������ �ߺ����� �߻���Ŵ 
	if(table[index].key == e.key){
		printf("key duplicated\n");
		exit(1);
	}
	// �ش� ��ġ�� �ٸ� element ������ �ִٸ� ����ִ� ��ġ�� ���ö����� ���� Ž�� 
	while(!(table+index)){
		index  = (index+1) % MAX_ELEMENT;
		
		// ���� ó���ڸ��� �ٽ� �ǵ��ƿԴٸ� ���̺��� �����ִٴ� �ǹ��̹Ƿ� ���� �޽��� ����� ���α׷� ����. 
		if(index == find_location_with_element(e)){
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
void insert_element_to_heap(HeapType *h, element_ptr e_ptr){
	int i = ++h->heap_size;
	h->heap[i] = e_ptr;
	
	/*if (i != 1 && i % 2 == 1) {
		if ((h->heap[i - 1])->value > (h->heap[i])->value) {
			swap(h->heap + i - 1, h->heap + i);
		}
	}*/

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
		
		insert_element_to_heap(h, new_node);
	}
	return h->heap[1];
}


void get_binary_code_and_save(element_ptr h, int i, char *pCode)
{
	if (h)
	{
		i++;
		pCode[i] = '1';
		get_binary_code_and_save(h->right_child, i, pCode);
		pCode[i] = '0';
		get_binary_code_and_save(h->left_child, i, pCode);
		pCode[i] = '\0';

		if (h->left_child == NULL && h->right_child == NULL && h->is_leaf == TRUE)
		{
			printf("%3c\t%3d\t%s\n", h->key, h->value, pCode);
			strcpy(h->bincode,pCode);
		}
	}
}

int main(){
	printf("------------���� �����---------------\n");
	FILE *fp = fopen("text.txt", "r");
	char c;
	int element_location;
	while ((c = fgetc(fp)) != EOF) {
		printf("%c", c);
		if ((element_location = find_location_with_key(hash_table, c)) == -1) {
			element will_be_inserted_element = {c,1,NULL,NULL,TRUE};
			hash_table_insert(hash_table, will_be_inserted_element);
		}
		else {
			hash_table[element_location].value++;
		}
	}
	fseek(fp, 0, SEEK_SET);
	int i;
	char binaryCode[100];
	
	for (i = 0; i < MAX_ELEMENT; i++) {
		if (hash_table[i].key) {
			printf("key : %c, value: %d\n", hash_table[i].key, hash_table[i].value);
		}
		
	}

	
	HeapType *Heap_ptr = (HeapType*)malloc(sizeof(HeapType));
	init(Heap_ptr);


	for (i = 0; i < MAX_ELEMENT; i++) {
		if (hash_table[i].key) {
			printf("Ű�� ã�ҽ��ϴ� %c\n", hash_table[i].key);
			insert_element_to_heap(Heap_ptr, hash_table+i);
		}
	}
	
	 
	printf("\n----�� �迭 ----\n");
	for(i = 1 ; i <= Heap_ptr->heap_size ; i++){
		printf("%d ", (Heap_ptr->heap[i])->value);
	}
	printf("\n");
	
	
	element_ptr root = get_root_node(Heap_ptr);

	

	get_binary_code_and_save(root, -1, binaryCode);

	printf("----���̳ʸ��ڵ� �׽�Ʈ-----\n");
	for (i = 0; i < MAX_ELEMENT; i++) {
		if (hash_table[i].key) {
			printf("key : %c, binaryCode: %s\n", hash_table[i].key, hash_table[i].bincode);
		}

	}

	// ���� ��ºκ�(���̳ʸ�ȭ)
	FILE *compressed = fopen("compressed.txt", "w");
	int loc;
	while ((c = fgetc(fp)) != EOF) {
		loc = find_location_with_key(hash_table, c);
		fprintf(compressed, hash_table[loc].bincode);
	}
	fclose(fp);
	fclose(compressed);

	// ���ڵ�
	FILE *decompressed = fopen("decompressed.txt", "w");
	FILE *read_compressed = fopen("compressed.txt", "r");
	element_ptr tmp = root;
	while ((c = fgetc(read_compressed)) != EOF) {
		if (c == '0') {
			tmp = tmp->left_child;
		}
		else if (c == '1') {
			tmp = tmp->right_child;
		}

		if (tmp->is_leaf == TRUE) {
			fputc(tmp->key, decompressed);
			tmp = root;
		}
	}
	fclose(decompressed);
	fclose(read_compressed);
	system("pause");
	return 0;
}
