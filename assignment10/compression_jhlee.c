#include <stdio.h>
#include <stdlib.h>

#define MAX_LEAF_NODES 55

int GetHashCode(int chr);
int GetChr(int hashCode);

struct Node
{
	int code;
	int weight;
	struct Node* parent;
	struct Node* children[2];
};

void Swap(struct Node** ptr_lhs, struct Node** ptr_rhs);

struct Node leafNodes[MAX_LEAF_NODES];
int huffmanCodes[MAX_LEAF_NODES];
int bitWidths[MAX_LEAF_NODES];

struct Node nonLeafNodes[MAX_LEAF_NODES - 1];
int idx_nextNonLeafNode;

struct Node* heap[MAX_LEAF_NODES + 1];
int count_heap;

void Heap_Insert(struct Node* nodeToInsert);
struct Node* Heap_GetMin();

int main()
{
	FILE* fp_read;
	FILE* fp_write;
	int idx_node;
	int chr;
	int hashCode;
	int huffmanCode;
	int width;
	unsigned char data;
	int remainedBits_data;
	unsigned char bitPos_data;
	struct Node* node_current;

	// 자료구조 초기화
	for (idx_node = 0; idx_node < MAX_LEAF_NODES; ++idx_node)
		leafNodes[idx_node].code = idx_node;

	// Tree 만들고 hashCode별 huffmanCode 생성
	fp_read = fopen("text.txt", "r");

	while (1)
	{
		chr = fgetc(fp_read);
		hashCode = GetHashCode(chr);

		if (hashCode == -1)
		{
			printf("Error. Invalid input. (%c)\n", chr);
			exit(1);
		}

		++leafNodes[hashCode].weight;

		// 마침표를 읽을 때까지 진행
		if (chr == '.')
			break;
	}

	fclose(fp_read);

	for (idx_node = 0; idx_node < MAX_LEAF_NODES; ++idx_node)
		Heap_Insert(&leafNodes[idx_node]);

	while (count_heap != 1)
	{
		struct Node* node_left = Heap_GetMin();
		struct Node* node_right = Heap_GetMin();

		node_current = &nonLeafNodes[idx_nextNonLeafNode];
		++idx_nextNonLeafNode;

		node_current->code = node_left->code;
		node_current->weight = node_left->weight + node_right->weight;

		node_current->children[0] = node_left;
		node_left->parent = node_current;

		node_current->children[1] = node_right;
		node_right->parent = node_current;

		Heap_Insert(node_current);
	}

	for (idx_node = 0; idx_node < MAX_LEAF_NODES; ++idx_node)
	{
		node_current = &leafNodes[idx_node];
		huffmanCode = 0;
		width = 0;

		while (node_current->parent != 0)
		{
			if (node_current->parent->children[1] == node_current)
				huffmanCode |= 1 << width;

			++width;

			node_current = node_current->parent;
		}

		huffmanCodes[idx_node] = huffmanCode;
		bitWidths[idx_node] = width;
	}

	// Encode
	fp_read = fopen("input.txt", "r");
	fp_write = fopen("output.txt", "wb");

	data = 0;
	remainedBits_data = 8;

	while (1)
	{
		chr = fgetc(fp_read);
		hashCode = GetHashCode(chr);
		huffmanCode = huffmanCodes[hashCode];
		width = bitWidths[hashCode];

		// 이번 바이트를 꽉 채우게 되는 경우 앞 비트를 먼저 출력
		while (width > remainedBits_data)
		{
			data <<= remainedBits_data;
			data |= (unsigned char)(huffmanCode >> (width - remainedBits_data));

			huffmanCode &= (1 << (width - remainedBits_data)) - 1;
			width -= remainedBits_data;

			fwrite(&data, sizeof(unsigned char), 1, fp_write);
			data = 0;
			remainedBits_data = 8;
		}

		// 아직 출력할 비트가 남은 경우 기록
		if (width != 0)
		{
			data <<= width;
			data |= (unsigned char)huffmanCode;
			remainedBits_data -= width;

			// 기록 후 이번 바이트가 꽉 찬 경우 출력
			if (remainedBits_data == 0)
			{
				fwrite(&data, sizeof(unsigned char), 1, fp_write);
				data = 0;
				remainedBits_data = 8;
			}
		}

		// 마침표를 읽을 때까지 진행
		if (chr == '.')
			break;
	}

	// 아직 출력하지 않은 비트가 있는 경우 마지막으로 출력
	if (data != 0)
	{
		data <<= remainedBits_data;
		fwrite(&data, sizeof(unsigned char), 1, fp_write);
	}

	fclose(fp_read);
	fclose(fp_write);


	// Decode
	fp_read = fopen("output.txt", "rb");
	fp_write = fopen("recoveredinput.txt", "w");

	node_current = heap[1];

	while (1)
	{
		fread(&data, sizeof(unsigned char), 1, fp_read);
		bitPos_data = 0x80;

		while (bitPos_data != 0)
		{
			node_current = node_current->children[(data & bitPos_data) != 0];

			if (node_current->children[0] == 0)
			{
				hashCode = node_current->code;
				chr = GetChr(hashCode);

				fputc(chr, fp_write);

				// 마침표를 출력할 때까지 진행
				if (chr == '.')
					break;

				node_current = heap[1];
			}

			bitPos_data >>= 1;
		}

		// 마침표를 출력할 때까지 진행
		if (chr == '.')
			break;
	}

	fclose(fp_read);
	fclose(fp_write);

	system("PAUSE");
	return 0;
}

int GetHashCode(int chr)
{
	if (chr == ' ')
		return 0;

	if (chr == ',')
		return 1;

	if (chr == '.')
		return 2;

	if (chr >= 'A' && chr <= 'Z')
		return chr - 'A' + 3;

	if (chr >= 'a' && chr <= 'z')
		return chr - 'a' + 29;

	return -1;
}

int GetChr(int hashCode)
{
	if (hashCode == 0)
		return ' ';

	if (hashCode == 1)
		return ',';

	if (hashCode == 2)
		return '.';

	if (hashCode >= 3 && hashCode <= 28)
		return 'A' + hashCode - 3;

	if (hashCode >= 29 && hashCode <= 55)
		return 'a' + hashCode - 29;

	return '\0';
}

int Compare(struct Node* lhs, struct Node* rhs)
{
	return lhs->weight != rhs->weight ?
		lhs->weight - rhs->weight :
		lhs->code - rhs->code;
}

void Swap(struct Node** ptr_lhs, struct Node** ptr_rhs)
{
	struct Node* temp = *ptr_lhs;
	*ptr_lhs = *ptr_rhs;
	*ptr_rhs = temp;
}

void Heap_Insert(struct Node* nodeToInsert)
{
	int pos_current;
	int pos_parent;
	struct Node* node_parent;

	// Heap의 맨 뒤에 새 node 추가
	++count_heap;
	heap[count_heap] = nodeToInsert;

	// Heafify
	for (pos_current = count_heap; pos_current != 1; pos_current = pos_parent)
	{
		pos_parent = pos_current >> 1;
		node_parent = heap[pos_parent];

		if (Compare(nodeToInsert, node_parent) < 0)
			Swap(&heap[pos_parent], &heap[pos_current]);
		else
			break;
	}
}

struct Node* Heap_GetMin()
{
	int pos_current;
	int pos_leftChild;
	int pos_rightChild;
	struct Node* node_current;
	struct Node* node_min = heap[1];

	// 맨 앞 node를 뽑고 맨 뒷 번호 node를 맨 앞에 가져옴
	pos_current = 1;
	node_current = heap[count_heap];
	heap[1] = node_current;
	--count_heap;

	// Heafify
	while (1)
	{
		pos_leftChild = pos_current << 1;
		pos_rightChild = pos_leftChild + 1;

		if (pos_leftChild > count_heap)
			break;

		if (pos_leftChild == count_heap || Compare(heap[pos_leftChild], heap[pos_rightChild]) < 0)
		{
			if (Compare(heap[pos_leftChild], node_current) < 0)
			{
				Swap(&heap[pos_current], &heap[pos_leftChild]);
				pos_current = pos_leftChild;
			}
			else
				break;
		}
		else
		{
			if (Compare(heap[pos_rightChild], node_current) < 0)
			{
				Swap(&heap[pos_current], &heap[pos_rightChild]);
				pos_current = pos_rightChild;
			}
			else
				break;
		}
	}

	return node_min;
}