#include <stdio.h>
#include <stdlib.h>
#define MAX 60000

typedef struct HeapType{
	int heap[MAX];
	int heap_size;
}HeapType;

void init(HeapType *h){
	h->heap_size = 0;
}

void swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void insert_key(HeapType *h, int key){
	// TODO
	int i = ++h->heap_size;
	h->heap[i] = key;
	
	while(i != 1){
		if(h->heap[i] > h->heap[i/2]){
			swap(h->heap + i, h->heap + i/2);
			i/=2;
		}
		else break;
	}
	
}
void print_heap(HeapType *h, int num){
	int i;
	for(i = 0 ; i < num ; i++){
		printf("%d ", h->heap[i+1]);
	}
	printf("\n");
}

int delete_key(HeapType *h){
	int parent, child;
	int key, tmp;
	int index = 1;
	// �ʱ�ȭ ����
	int i = (h->heap_size)--;
	key = h->heap[1] = h->heap[i];
	
	// �ڱ� �ڸ��� ã�ư��� ����
	while(1){
		// left node�� �ڽź��� ū ��� 
		if(h->heap[index] < h->heap[index*2] && h->heap[index*2] > h->heap[index*2 + 1] && index*2 <= h->heap_size){
			swap(h->heap + index, h->heap + index*2);
			index *= 2;
		}
		// right node�� �ڽź��� ū ��� 
		else if(h->heap[index] < h->heap[index*2 + 1] && h->heap[index*2] < h->heap[index*2 + 1] && index*2 + 1 <= h->heap_size){
			swap(h->heap + index, h->heap + index*2 + 1);
			index *= 2;
			index++;
		}
		else break;
		
	}
	
	return key; 
}

void SWAP(int a[], int b[]){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//
void bubbleSort(int list[], int n){
	int i, j, tmp;
	for(i = 0 ; i < n ; i++){
		for(j = 0; j < n - i - 1; j++){
			if(list[j] > list[j+1]){
				SWAP(list+j, list+j+1);
			}
		}
	}
}


void insertSort(int list[], int n){
	int i, j , key;
	for(i = 1 ; i < n ; i++){
		key = list[i];
		for(j = i-1 ; j >= 0 ; j--){
			if(list[j] < key){
				list[j+1] = key;
				break;
			}
			else{
				list[j+1] = list[j];
				list[j] = key;
			}
		}
		
	}
}

void selectionSort(int list[], int n){
	int i, j , least_idx, tmp;
	for(i = 0; i < n; i++){
		tmp = list[i];
		for(j = i ; j < n ; j++){
			if(list[j] < tmp){
				tmp = list[j];
				least_idx = j;
			}
		}
		SWAP(list+i, list+least_idx);
	}
}

//mergeSort ���� 
void mergeSort(int list[], int left, int right){
	int middle = (left+right) / 2;
	if(left < right){
		mergeSort(list, left, middle);
		mergeSort(list, middle+1, right);
		merge(list, left, middle, right);
	}
}

void merge(int array[], int left, int mid, int right){
	int i, j, k, m; 

	i = left;       
	j = mid + 1; 
	k = left;    //��� �迭�� �ε���
	
	int tempArray[MAX];
	
	  //left���� mid ������ ��ϰ� mid+1���� right������ ����� ���� ���ϴ� �κ�
	while (i <= mid && j <= right) {
	   	if (array[i] < array[j]){   //left index ���� right index ������ ������ left index ���� ��� result�� ����
	      tempArray[k] = array[i];
	      i++;
	    }else{        //�ƴ϶�� right index ���� ��� result�� ����
	      tempArray[k] = array[j];
	      j++;
	    }
	    k++;
  	}

	  // left ����� ���� �� ó���Ǿ��µ� right ����� index�� ���� �������� ���
	  // right index�� ���������� ��� result�� ����
	if (i > mid){
	    for (m = j; m <= right; m++){   
	      tempArray[k] = array[m];     
	      k++;
	    }
	} else {                    // left ����� index�� ���� �������� ��� left index�� ���������� ��� result�� ���� 
	    for (m = i; m <= mid; m++){ 
	      tempArray[k] = array[m];   
	      k++;
	    }
	}
	  
	for(m = left; m <= right; m++){
	    array[m] = tempArray[m];
	}
}
// mergerSort ��
//
// quickSort ����
void quickSort(int numbers[], int array_size);
void q_sort(int numbers[], int left, int right);

void quickSort(int numbers[], int array_size)
{
    q_sort(numbers, 0, array_size -1);
}

void q_sort(int numbers[], int left, int right)
{
    int pivot, l_hold, r_hold;
    l_hold  = left;
    r_hold  = right;
    pivot   = numbers[left];  // 0��° ���Ҹ� �Ǻ����� ����
    while (left < right)
    {
        // ���� ������ �Ǻ��� ���ų� ũ�ٸ�, �̵��� �ʿ䰡 ����
        while ((numbers[right] >= pivot) && (left < right))
          right --;

          // �׷��� �ʰ� ���� �Ǻ����� �۴ٸ�,
          // �Ǻ��� ��ġ�� ���� ���� �ִ´�.
        if (left != right)
        {
             numbers[left] = numbers[right];
        }
        // ���ʺ��� ���� ��ġ���� ���� �о���̸鼭
        // �Ǻ����� ū ���� �ִٸ�, ���� �̵��Ѵ�.
        while ((numbers[left] <= pivot) && (left < right))
          left ++;
        
        if (left != right)
        {
           numbers[right] = numbers[left];
           right --;
        }
    }

    // ��� ��ĵ�� �����ٸ�, �Ǻ����� ���� ��ġ�� �Է��Ѵ�.
    // ���� �Ǻ��� �������� ���ʿ��� �Ǻ����� �۰ų� ���� ���� ���Ҵ�.
    numbers[left] = pivot;
    pivot         = left;
    left          = l_hold;
    right         = r_hold;

    // ���ȣ���� �����Ѵ�.
    if (left < pivot)
        q_sort(numbers, left, pivot - 1);
    if (right > pivot)
        q_sort(numbers, pivot+1, right);
}

