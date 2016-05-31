#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR 10
#define MAX_ELEMENT 100
#define MAX_HEAP_SIZE 100 

// hash ���̺��� ���� Ÿ��
// key�� ���ĺ�, value�� �󵵼��� ��� ���� 
typedef struct element{
	char key;
	int value;
	struct element *left_child, *right_child; 
}element;

// heap�� ���� ������ ��� Ÿ���� ���� 
typedef struct HeapType{
	element heap[MAX_HEAP_SIZE];
	int heap_size;
}HeapType;


// hash ���̺� �迭 
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

// HeapType ������ �ʱ�ȭ���ִ� �Լ� 
void init(HeapType *h){
	h->heap_size = 0;
}

// HeapType�� heap�迭���� element���� �ڸ��� ���� �ٲٴ� �Լ� 
void swap(element *a, element *b){
	element tmp;
	tmp.key = a->key;
	tmp.value = a->value;
	*a = *b;
	*b = tmp;
}

// HeapType heap�迭�� ������ ��ġ�� element ������ �����ϴ� �Լ� 
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
