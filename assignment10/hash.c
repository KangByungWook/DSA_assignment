#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR 10
#define MAX_ELEMENT 10000
#define MAX_HEAP_SIZE 10000 
#define TRUE 1
#define FALSE 0

typedef struct element* element_ptr;
// hash 테이블의 변수 타입
// key는 알파벳, value는 빈도수를 담는 변수 
typedef struct element{
	char key;
	int value;
	element_ptr left_child, right_child;
	int is_leaf;
	char bincode[100];
}element;



// heap에 대한 정보를 담는 타입을 정의 
typedef struct HeapType{
	element_ptr heap[MAX_HEAP_SIZE];
	int heap_size;
}HeapType;


// hash 테이블 배열 
// element변수를 가리키는 포인터변수 배열 
element hash_table[MAX_ELEMENT];

// element변수의 key값을 받아서 숫자로 변환해주는 함수
// 이때 변환되는 숫자는 해당 char의 아스키코드 값 
int transform(char key){
	int number = key;
	return number;
}

// element변수를 받아서 hash_table에 들어있는 위치를 반환해주는 함수 
int find_location_with_element(element e){
	return transform(e.key) % MAX_ELEMENT;
}

int find_location_with_key(element hash_table[], char key) {
	int index = transform(key) % MAX_ELEMENT;
	while (hash_table[index].key != key) {
		index++;
		index %= MAX_ELEMENT;
		if (index == transform(key) % MAX_ELEMENT) {
			//printf("해당 key를 갖는 element가 없습니다.\n");
			return -1;
		}
	}
	return index;
}


// element변수를 hash테이블에 삽입하는 함수 
void hash_table_insert(element table[], element e){
	// 해당 element변수가 들어갈 위치를 판단 
	int index = find_location_with_element(e);
	// 해당 위치에 있는 변수의 key값이 삽입하려는 element의 key값과 같을때 중복오류 발생시킴 
	if(table[index].key == e.key){
		printf("key duplicated\n");
		exit(1);
	}
	// 해당 위치에 다른 element 변수가 있다면 비어있는 위치가 나올때까지 선형 탐색 
	while(!(table+index)){
		index  = (index+1) % MAX_ELEMENT;
		
		// 만약 처음자리로 다시 되돌아왔다면 테이블이 꽉차있다는 의미이므로 오류 메시지 출력후 프로그램 종료. 
		if(index == find_location_with_element(e)){
			printf("hash table is full\n");
			exit(1);
		}
	}
	// 적절한 위치를 찾았다면 해당 위치에 element를 삽입 
	table[index] = e;
}


// Heap 구현 시작. 
// HeapType 변수를 초기화해주는 함수 
void init(HeapType *h){
	h->heap_size = 0;
}

// HeapType의 heap배열에서 element들의 자리를 서로 바꾸는 함수 
void swap(element_ptr *a, element_ptr *b){
	element_ptr tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

// HeapType heap배열의 적절한 위치에 element 변수를 삽입하는 함수 
void insert_element_to_heap(HeapType *h, element_ptr e_ptr){
	int i = ++h->heap_size;
	h->heap[i] = e_ptr;
	
	/*if (i != 1 && i % 2 == 1) {
		if ((h->heap[i - 1])->value > (h->heap[i])->value) {
			swap(h->heap + i - 1, h->heap + i);
		}
	}*/

	while(i != 1){
		
		// 만약 부모 노드의 value값(빈도수)이 더 크면 부모노드와 위치를 바꾼다 
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
	// 초기화 과정
	int i = (h->heap_size)--;
	tmp = h->heap[1];
	h->heap[1] = h->heap[i];
	
	// 자기 자리를 찾아가는 과정
	while(1){
		// left node의 value가 자신보다 작은 경우 
		if(index * 2 <= h->heap_size && (h->heap[index])->value > (h->heap[index*2])->value && (h->heap[index*2])->value < (h->heap[index*2 + 1])->value ){
			swap(h->heap + index, h->heap + index*2);
			index *= 2;
		}
		// right node의 value가 자신보다 작은 경우 
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
	// 힙이 다 빌때까지 두개씩 빼가면서 트리를 만든다.
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
	printf("------------파일 입출력---------------\n");
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
			printf("키를 찾았습니다 %c\n", hash_table[i].key);
			insert_element_to_heap(Heap_ptr, hash_table+i);
		}
	}
	
	 
	printf("\n----힙 배열 ----\n");
	for(i = 1 ; i <= Heap_ptr->heap_size ; i++){
		printf("%d ", (Heap_ptr->heap[i])->value);
	}
	printf("\n");
	
	
	element_ptr root = get_root_node(Heap_ptr);

	

	get_binary_code_and_save(root, -1, binaryCode);

	printf("----바이너리코드 테스트-----\n");
	for (i = 0; i < MAX_ELEMENT; i++) {
		if (hash_table[i].key) {
			printf("key : %c, binaryCode: %s\n", hash_table[i].key, hash_table[i].bincode);
		}

	}

	// 파일 출력부분(바이너리화)
	FILE *compressed = fopen("compressed.txt", "w");
	int loc;
	while ((c = fgetc(fp)) != EOF) {
		loc = find_location_with_key(hash_table, c);
		fprintf(compressed, hash_table[loc].bincode);
	}
	fclose(fp);
	fclose(compressed);

	// 디코드
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
