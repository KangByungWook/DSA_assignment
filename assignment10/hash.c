#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR 10
#define MAX_ELEMENT 100
#define MAX_HEAP_SIZE 100 

// hash 테이블의 변수 타입
// key는 알파벳, value는 빈도수를 담는 변수 
typedef struct element{
	char key;
	int value;
	struct element *left_child, *right_child; 
}element;

// heap에 대한 정보를 담는 타입을 정의 
typedef struct HeapType{
	element heap[MAX_HEAP_SIZE];
	int heap_size;
}HeapType;


// hash 테이블 배열 
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

// HeapType 변수를 초기화해주는 함수 
void init(HeapType *h){
	h->heap_size = 0;
}

// HeapType의 heap배열에서 element들의 자리를 서로 바꾸는 함수 
void swap(element *a, element *b){
	element tmp;
	tmp.key = a->key;
	tmp.value = a->value;
	*a = *b;
	*b = tmp;
}

// HeapType heap배열의 적절한 위치에 element 변수를 삽입하는 함수 
void insert_element(HeapType *h, element e){
	int i = ++h->heap_size;
	h->heap[i] = e;
	
	while(i != 1){
		if((h->heap[i]).key < (h->heap[i/2]).key){
			swap(h->heap + i, h->heap + i/2);
			i/=2;
		}
		else break;
	}
	
}
int main(){
	element tmp;
	tmp.key = 'a';
	tmp.value = 2;
	hash_table_insert(hash_table, tmp);
	printf("%d\n", hash(tmp));
	printf("%d", hash_table[hash(tmp)].value);
}
