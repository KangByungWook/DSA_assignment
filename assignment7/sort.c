#include <stdio.h>
#include <stdlib.h>
#define MAX 60000

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

void selectionSort(int *list, const int n)
{
    int i, j, indexMin, temp;

    for (i = 0; i < n - 1; i++)
    {
        indexMin = i;
        for (j = i + 1; j < n; j++)
        {
            if (list[j] < list[indexMin])
            {
                indexMin = j;
            }
        }
        temp = list[indexMin];
        list[indexMin] = list[i];
        list[i] = temp;
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

void merge(int* array, int left, int mid, int right){
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

 
void Min_Heap(int parm_data[], int parm_start, int parm_count)
{
    int node_left, node_right, node_current, node_start, node_index;
    if(parm_count - parm_start < 2) return;
    node_current = parm_start;
 
    while(node_current >= 0){
        node_index = node_current;
        node_start = node_current;
        while(node_start*2+1 < parm_count){
            node_left = node_start*2+1;
            node_right = node_start*2+2;
            node_start = node_left;
 
            if(node_right < parm_count && parm_data[node_right] >= parm_data[node_left]){
                node_start = node_right;
            }
            if(parm_data[node_start] > parm_data[node_index]){
                SWAP(&parm_data[node_index], &parm_data[node_start]);
                node_index = node_start;
            }
        }
        --node_current;
    }
}
 
void Heap_Sort(int parm_data[], int parm_count)
{
    Min_Heap(parm_data, parm_count/2-1, parm_count);
    while(parm_count > 0){
        --parm_count;
        SWAP(&parm_data[0], &parm_data[parm_count]);
        Min_Heap(parm_data, 0, parm_count);
    }
}

