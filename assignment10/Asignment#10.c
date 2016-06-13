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
		// 힙배열에서 노드 두개를 빼서 하나의 트리를 만든다
		element_ptr left_node_ptr = delete_node(h);
		element_ptr right_node_ptr = delete_node(h);
		// 새로 생성한 노드의 child_node에 방금 빼낸 두개의 노드를 연결한다
		new_node->left_child = left_node_ptr;
		new_node->right_child = right_node_ptr;
		new_node->value = left_node_ptr->value + right_node_ptr->value;
		new_node->is_leaf = FALSE;
		
		insert_element_to_heap(h, new_node);
	}
	return h->heap[1];
}

// 힙트리를 읽어서 각각의 알파벳을 바이너리화하는 함수
void get_binary_code_and_save(element_ptr h, int i, char *pCode)
{
	if (h)
	{
		i++;
		// right_child로 갈 경우 바이너리코드에 1을 추가
		pCode[i] = '1';
		get_binary_code_and_save(h->right_child, i, pCode);
		// left_child로 갈 경우 바이너리코드에 0을 추가
		pCode[i] = '0';
		get_binary_code_and_save(h->left_child, i, pCode);
		// 마지막에 널문자 삽입
		pCode[i] = '\0';

		// leaf노드에 도착했을 경우 pCode를 각 노드의 bincode변수에 저장
		if (h->left_child == NULL && h->right_child == NULL && h->is_leaf == TRUE)
		{
			strcpy(h->bincode,pCode);
		}
	}
}

int main(){
	// 원본텍스트파일을 읽기 위한 파일포인터를 생성
	FILE *original_read = fopen("input.txt", "r");
	char c;
	int element_location;
	// 원본텍스트파일을 한글자씩 읽어가면서 hash_table에 저장한다
	while ((c = fgetc(original_read)) != EOF) {
		// 알파벳에 맞는 hash_table의 적절한 위치에 해당 알파벳이 없는경우 추가
		if ((element_location = find_location_with_key(hash_table, c)) == -1) {
			element will_be_inserted_element = {c,1,NULL,NULL,TRUE};
			hash_table_insert(hash_table, will_be_inserted_element);
		}
		// 기존에 존재할 경우 value(빈도값)에 1을 더해준다
		else {
			hash_table[element_location].value++;
		}
	}
	// 압축파일을 만들기 위해 원본파일을 다시 처음부터 읽어야하므로
	// 포인터를 파일의 시작지점으로 옮긴다
	fseek(original_read, 0, SEEK_SET);
	int i;
	// 바이너리문자열을 저장하기 위한 변수생성
	char binaryCode[100];
	
	// 힙타입의 포인터변수를 동적할당
	HeapType *Heap_ptr = (HeapType*)malloc(sizeof(HeapType));
	
	// 동적할당한 포인터변수를 초기화 한다
	init(Heap_ptr);
	
	// hash_table을 하나씩 살피면서 
	// hash_table안에 있는 유효한 element변수를 heap에 넣는다
	for (i = 0; i < MAX_ELEMENT; i++) {
		if (hash_table[i].key) {
			insert_element_to_heap(Heap_ptr, hash_table+i);
		}
	}
	// heap에 있는 element포인터변수를 이용하여 힙트리를 만들고 
	// 완성된 힙트리의 root노드 포인터를 root 변수에 저장
	element_ptr root = get_root_node(Heap_ptr);
	
	// 방금 생성한 힙트리를 이용하여 각 알파벳의 고유 바이너리코드를 생성하여 저장한다
	get_binary_code_and_save(root, -1, binaryCode);
	
	// 파일 압축
	// 압축 텍스트 파일을 쓰기 위한 파일포인터 생성
	FILE *compressed_write = fopen("output.txt", "w");
	int loc;
	// 원본파일을 읽어가며 각 알파벳에 맞는 바이너리문자열을 compressed.txt.dp 출력한다
	while ((c = fgetc(original_read)) != EOF) {
		// hash_tabe로 부터 알파벳에 맞는 바이너리문자열을 찾아서 
		loc = find_location_with_key(hash_table, c);
		// compressed.txt파일에 출력한다
		fprintf(compressed_write, hash_table[loc].bincode);
	}
	// 열어둔 파일을 닫는다
	fclose(original_read);
	fclose(compressed_write);

	// 압축파일 디코딩
	// 디코딩한 텍스트파일을 저장할 파일포인터 생성
	FILE *decompressed_write = fopen("recoveredinput.txt", "w");

	// 압축된 파일을 읽기 위한 파일포인터 생성
	FILE *compressed_read = fopen("output.txt", "r");
	element_ptr tmp = root;
	
	// 압축된 파일 텍스트를 하나씩 읽어가면서 바이너리코드에 해당하는 알파벳으로 변환
	while ((c = fgetc(compressed_read)) != EOF) {
		// 0인 경우 left_child로 이동
		if (c == '0') {
			tmp = tmp->left_child;
		}
		// 1인 경우 right_child로 이동
		else if (c == '1') {
			tmp = tmp->right_child;
		}
		// 해당 노드가 left_node인 경우 알파벳을 decompressed.txt에 출력하고
		if (tmp->is_leaf == TRUE) {
			fputc(tmp->key, decompressed_write);
			// 노드의 포인터를 root로 바꾼다
			tmp = root;
		}
	}
	// 열어준 파일을 닫는다
	fclose(decompressed_write);
	fclose(compressed_read);
	system("pause");
	return 0;
}
