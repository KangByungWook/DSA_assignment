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
		// key: ���� �� 
		key = list[i];				
		
		// �ε��� 0�� ��ġ��Һ��� Ž���ϸ鼭 key���� �� ������ ��ġ�� Ž�� 
		for(j = i-1 ; j >= 0 ; j--){
			// �ε����� �ϳ��� �������鼭 Ž��
			// ���� �ڱ� �ڽź��� ū �迭 ��Ҹ� ã���� �ش� ����� ���� ��ġ�� key���� �ִ´� 
			if(list[j] < key){		
				list[j+1] = key;
				break;
			}
			// �ƴ� ��� ��ġ�� �ٲ۴� 
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
        // �ּҰ��� ã�� ���� 
        for (j = i + 1; j < n; j++)
        {
            if (list[j] < list[indexMin])
            {
                indexMin = j;
            }
        }
        // �ּҰ��� ã���� ���� ��ü�Ѵ� 
        temp = list[indexMin];
        list[indexMin] = list[i];
        list[i] = temp;
    }
}

 
void mergeSort(int list[], int left, int right){
	// middle -> left �迭�� right�迭�� ��� 
	int middle = (left+right) / 2;
	if(left < right){
		// left�迭�� right�迭�� ���� ���� ��������� �պ������� ���� 
		mergeSort(list, left, middle);
		mergeSort(list, middle+1, right);
		merge(list, left, middle, right);	// �л�� �迭�� �����ִ� �Լ� ���� 
	}
}

// �л�� �迭�� ���ս����ִ� �Լ� 
void merge(int* array, int left, int mid, int right){
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



// �迭�� Heap�� ������ �ٲ��ִ� �Լ� 
void Max_Heap(int parm_data[], int parm_start, int parm_count)
{
    int node_left, node_right, node_current, node_start, node_index;
    if(parm_count - parm_start < 2) return;
    node_current = parm_start;
 
    while(node_current >= 0){
        node_index = node_current;
        node_start = node_current;
        while(node_start*2+1 < parm_count){
        	// ���� �ڽĳ��� �θ� ��� �ε���*2 
        	// 0���� �����ϹǷ� 1�� �����ش� 
            node_left = node_start*2+1;
            
            // ������ �ڽĳ��� �θ� ��� �ε���*2 + 1
            // 0���� �����ϹǷ� 1�� �����ش� 
            node_right = node_start*2+2;
            
            // ���� ������ �����Ѵ�. 
            node_start = node_left;
 
 			// ���� ���� ������ ��带 ���ؼ� ū ������ node_start�� ���� 
            if(node_right < parm_count && parm_data[node_right] >= parm_data[node_left]){
                node_start = node_right;
            }
            // �θ��庸�� �ڽĳ�尡 �� ũ�� �ٲ��ش�
            if(parm_data[node_start] > parm_data[node_index]){
                SWAP(&parm_data[node_index], &parm_data[node_start]);
                node_index = node_start;
            }
        }
        --node_current;
    }
}

// ������ �Լ� 
void Heap_Sort(int parm_data[], int parm_count)
{	
    Max_Heap(parm_data, parm_count/2-1, parm_count);
    while(parm_count > 0){
        --parm_count;
        // parm_data[0]�� �ִ� ���ڰ� ���� ũ�Ƿ� �̸� �ǵڷ� �����ش� 
        SWAP(&parm_data[0], &parm_data[parm_count]);
        // �迭�� �ٽ� Heap ������ ������ش� 
        Max_Heap(parm_data, 0, parm_count);
    }
}

