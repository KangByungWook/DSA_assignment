#include <stdio.h>
#include <stdlib.h>
#define MAX 60000

void SWAP(int a[], int b[]){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void insertSort(int list[], int n){
	int i, j , key;
	for(i = 1 ; i < n ; i++){
		// key: 비교할 값 
		key = list[i];				
		
		// 인덱스 0의 위치요소부터 탐색하면서 key값이 들어갈 적절한 위치를 탐색 
		for(j = i-1 ; j >= 0 ; j--){
			// 인덱스를 하나씩 내려가면서 탐색
			// 만약 자기 자신보다 큰 배열 요소를 찾으면 해당 요소의 다음 위치에 key값을 넣는다 
			if(list[j] < key){		
				list[j+1] = key;
				break;
			}
			// 아닌 경우 위치를 바꾼다 
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
        // 최소값을 찾는 과정 
        for (j = i + 1; j < n; j++)
        {
            if (list[j] < list[indexMin])
            {
                indexMin = j;
            }
        }
        // 최소값을 찾으면 값을 교체한다 
        temp = list[indexMin];
        list[indexMin] = list[i];
        list[i] = temp;
    }
}

 
void mergeSort(int list[], int left, int right){
	// middle -> left 배열과 right배열의 경계 
	int middle = (left+right) / 2;
	if(left < right){
		// left배열과 right배열에 대해 각각 재귀적으로 합병정렬을 실행 
		mergeSort(list, left, middle);
		mergeSort(list, middle+1, right);
		merge(list, left, middle, right);	// 분산뒨 배열을 합쳐주는 함수 실행 
	}
}

// 분산된 배열을 병합시켜주는 함수 
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



// 배열을 Heap의 구조로 바꿔주는 함수 
void Max_Heap(int parm_data[], int parm_start, int parm_count)
{
    int node_left, node_right, node_current, node_start, node_index;
    if(parm_count - parm_start < 2) return;
    node_current = parm_start;
 
    while(node_current >= 0){
        node_index = node_current;
        node_start = node_current;
        while(node_start*2+1 < parm_count){
        	// 왼쪽 자식노드는 부모 노드 인덱스*2 
        	// 0부터 시작하므로 1을 더해준다 
            node_left = node_start*2+1;
            
            // 오른쪽 자식노드는 부모 노드 인덱스*2 + 1
            // 0부터 시작하므로 1을 더해준다 
            node_right = node_start*2+2;
            
            // 왼쪽 노드부터 시작한다. 
            node_start = node_left;
 
 			// 왼쪽 노드와 오른쪽 노드를 비교해서 큰 쪽으로 node_start를 지정 
            if(node_right < parm_count && parm_data[node_right] >= parm_data[node_left]){
                node_start = node_right;
            }
            // 부모노드보다 자식노드가 더 크면 바꿔준다
            if(parm_data[node_start] > parm_data[node_index]){
                SWAP(&parm_data[node_index], &parm_data[node_start]);
                node_index = node_start;
            }
        }
        --node_current;
    }
}

// 힙정렬 함수 
void Heap_Sort(int parm_data[], int parm_count)
{	
    Max_Heap(parm_data, parm_count/2-1, parm_count);
    while(parm_count > 0){
        --parm_count;
        // parm_data[0]에 있는 숫자가 가장 크므로 이를 맨뒤로 보내준다 
        SWAP(&parm_data[0], &parm_data[parm_count]);
        // 배열을 다시 Heap 구조로 만들어준다 
        Max_Heap(parm_data, 0, parm_count);
    }
}

