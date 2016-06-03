#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR 10
#define MAX_ELEMENT 100
#define MAX_HEAP_SIZE 100 
#define TRUE 1
#define FALSE 0

typedef struct element* element_ptr;
// hash 테이블의 변수 타입
// key는 알파벳, value는 빈도수를 담는 변수 
typedef struct element{
	char key;
	int value;
	element_ptr left_child, right_child;
	 
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

// element변수를 받아서 hash_table에 들어갈 위치를 반환해주는 함수 
int hash(element e){
	return transform(e.key) % MAX_ELEMENT;
}

// element변수를 hash테이블에 삽입하는 함수 
void hash_table_insert(element table[], element e){
	// 해당 element변수가 들어갈 위치를 판단 
	int index = hash(e);
	// 해당 위치에 있는 변수의 key값이 삽입하려는 element의 key값과 같을때 중복오류 발생시킴 
	if(table[index].key == e.key){
		printf("key duplicated\n");
		exit(1);
	}
	// 해당 위치에 다른 element 변수가 있다면 비어있는 위치가 나올때까지 선형 탐색 
	while(!(table+index)){
		index  = (index+1) % MAX_ELEMENT;
		
		// 만약 처음자리로 다시 되돌아왔다면 테이블이 꽉차있다는 의미이므로 오류 메시지 출력후 프로그램 종료. 
		if(index == hash(e)){
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
void insert_element(HeapType *h, element_ptr e_ptr){
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

void delete_node(HeapType *h){
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
			// TODO 여기서 문제발생
			// 아래처럼 +1을 붙이면 에러발생 안하는데 왜그런지 모르겠다. 
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
	
}


int main(){
	element tmp, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9;
	int i;
	tmp.key = 'a';
	tmp.value = 2;
	hash_table_insert(hash_table, tmp);
	printf("%d\n", hash(tmp));
	printf("%d", hash_table[hash(tmp)].value);
	
	HeapType *Heap_ptr = (HeapType*)malloc(sizeof(HeapType));
	init(Heap_ptr);
	element_ptr tmp_ptr = &tmp;
	insert_element(Heap_ptr, tmp_ptr);
	tmp1.value = 12;
	tmp_ptr = &tmp1;
	insert_element(Heap_ptr, tmp_ptr);
	tmp2.value = 65;
	tmp_ptr = &tmp2;
	insert_element(Heap_ptr, tmp_ptr);
	tmp3.value = 72;
	tmp_ptr = &tmp3;
	insert_element(Heap_ptr, tmp_ptr);
	tmp4.value = 31;
	tmp_ptr = &tmp4;
	insert_element(Heap_ptr, tmp_ptr);
	tmp5.value = 35;
	tmp_ptr = &tmp5;
	insert_element(Heap_ptr, tmp_ptr);
	tmp6.value = 87;
	tmp_ptr = &tmp6;
	insert_element(Heap_ptr, tmp_ptr);
	tmp7.value = 43;
	tmp_ptr = &tmp7;
	insert_element(Heap_ptr, tmp_ptr);
	 
	printf("\n--------\n");
	for(i = 0 ; i <= Heap_ptr->heap_size; i++){
		printf("%d ", (Heap_ptr->heap[i])->value);
	}
	
	delete_node(Heap_ptr);
	
}
