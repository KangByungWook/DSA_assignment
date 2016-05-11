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
	// 초기화 과정
	int i = (h->heap_size)--;
	key = h->heap[1] = h->heap[i];
	
	// 자기 자리를 찾아가는 과정
	while(1){
		// left node가 자신보다 큰 경우 
		if(h->heap[index] < h->heap[index*2] && h->heap[index*2] > h->heap[index*2 + 1] && index*2 <= h->heap_size){
			swap(h->heap + index, h->heap + index*2);
			index *= 2;
		}
		// right node가 자신보다 큰 경우 
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

//mergeSort 시작 
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
	k = left;    //결과 배열의 인덱스
	
	int tempArray[MAX];
	
	  //left부터 mid 까지의 블록과 mid+1부터 right까지의 블록을 서로 비교하는 부분
	while (i <= mid && j <= right) {
	   	if (array[i] < array[j]){   //left index 값이 right index 값보다 작으면 left index 값을 결과 result에 복사
	      tempArray[k] = array[i];
	      i++;
	    }else{        //아니라면 right index 값을 결과 result에 복사
	      tempArray[k] = array[j];
	      j++;
	    }
	    k++;
  	}

	  // left 블록의 값은 다 처리되었는데 right 블록의 index가 아직 남아있을 경우
	  // right index를 순차적으로 결과 result에 복사
	if (i > mid){
	    for (m = j; m <= right; m++){   
	      tempArray[k] = array[m];     
	      k++;
	    }
	} else {                    // left 블록의 index가 아직 남아있을 경우 left index를 순차적으로 결과 result에 복사 
	    for (m = i; m <= mid; m++){ 
	      tempArray[k] = array[m];   
	      k++;
	    }
	}
	  
	for(m = left; m <= right; m++){
	    array[m] = tempArray[m];
	}
}
// mergerSort 끝
//
// quickSort 시작
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
    pivot   = numbers[left];  // 0번째 원소를 피봇으로 선택
    while (left < right)
    {
        // 값이 선택한 피봇과 같거나 크다면, 이동할 필요가 없다
        while ((numbers[right] >= pivot) && (left < right))
          right --;

          // 그렇지 않고 값이 피봇보다 작다면,
          // 피봇의 위치에 현재 값을 넣는다.
        if (left != right)
        {
             numbers[left] = numbers[right];
        }
        // 왼쪽부터 현재 위치까지 값을 읽어들이면서
        // 피봇보다 큰 값이 있다면, 값을 이동한다.
        while ((numbers[left] <= pivot) && (left < right))
          left ++;
        
        if (left != right)
        {
           numbers[right] = numbers[left];
           right --;
        }
    }

    // 모든 스캔이 끝났다면, 피봇값을 현재 위치에 입력한다.
    // 이제 피봇을 기준으로 왼쪽에는 피봇보다 작거나 같은 값만 남았다.
    numbers[left] = pivot;
    pivot         = left;
    left          = l_hold;
    right         = r_hold;

    // 재귀호출을 수행한다.
    if (left < pivot)
        q_sort(numbers, left, pivot - 1);
    if (right > pivot)
        q_sort(numbers, pivot+1, right);
}

