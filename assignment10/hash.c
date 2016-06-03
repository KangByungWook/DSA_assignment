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

void delete_node(HeapType *h){
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
			// TODO ���⼭ �����߻�
			// �Ʒ�ó�� +1�� ���̸� �����߻� ���ϴµ� �ֱ׷��� �𸣰ڴ�. 
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
