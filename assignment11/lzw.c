#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000
#define MAX_KEY_SIZE 100
#define MAX_TEXT_SIZE 1000

char* table[TABLE_SIZE];

typedef struct TableType {
	char* table[TABLE_SIZE];
	int size;
}TableType;

typedef struct TableType* TableType_ptr;

void init_table(TableType_ptr t) {
	char tmp[2];
	int i;
	for (int i = 97; i <= 122; i++) {
		tmp[0] = i;
		tmp[1] = '\0';
		strcpy(t->table + i - 97, tmp);
	}
	t->size = 26;
}

void insert_table(TableType_ptr t_ptr, char* key) {
	if (t_ptr->size == TABLE_SIZE) {
		printf("Table size full!\n");
		exit(1);
	}
	
	int insert_location = ++(t_ptr->size) - 1;
	//printf("�Ű������� ���� ���ڿ� %s�� %d�� �ֽ��ϴ�", key, insert_location);

	strcpy(t_ptr->table + insert_location, key);
}

// ã���� �ϴ� Ű�� ���� Ű�� ������ ��ġ ��ȯ
// ���� �� -1 ��ȯ
int find_previous_key_location(TableType_ptr t, char* key) {
	int i;
	for (i = 0; i < t->size; i++) {
		if (strcmp(t->table + i, key) == 0) {
			return i;
		}
	}
	return -1;
}

int main() {
	
	// file io test
	/////////////////////////////////////////////////
	/*FILE* input_fp = fopen("input.txt", "r");
	char c;
	char text[MAX_TEXT_SIZE];
	int i = 0;
	while ((c = fgetc(input_fp)) != EOF) {
		printf("%c", c);
		text[i++] = c;
	}
	text[i] = '\0';
	printf("%s", text);
	system("pause");*/
	/////////////////////////////////////////////////
	
	// insert_table test
	/////////////////////////////////////////////////
	//TableType t;
	//TableType_ptr t_ptr = &t;
	//
	//init_table(t_ptr);
	//for (int i = 0; i < t_ptr->size; i++) {
	//	printf("%s ", t_ptr->table + i);
	//}
	//insert_table(t_ptr, "abcd");
	//for (int i = 0; i < t_ptr->size; i++) {
	//	printf("%s ", t_ptr->table + i);
	//}
	//system("pause");
	/////////////////////////////////////////////////

	//find_previous_key_location test
	/////////////////////////////////////////////////
	/*
	TableType t;
	TableType_ptr t_ptr = &t;

	init_table(t_ptr);
	insert_table(t_ptr, "kang");
	printf("��ġ : %d", find_previous_key_location(t_ptr, "kang"));
	system("pause");*/
	/////////////////////////////////////////////////

	// input���� �о�� encoding + table �ڵ鸵
	// encoding
	FILE* input_fp = fopen("input.txt", "r");
	
	TableType encoding_table;
	TableType_ptr encoding_table_ptr = &encoding_table;
	init_table(encoding_table_ptr);

	TableType decoding_table;
	TableType_ptr decoding_table_ptr = &decoding_table;
	init_table(decoding_table_ptr);
	
	char c;
	char text[MAX_TEXT_SIZE];
	int i = 0;

	char tmp[MAX_KEY_SIZE];
	char tmp2[MAX_KEY_SIZE];

	int encode[1000];
	int encode_index = 0;

	// �ؽ�Ʈ������ ���ڿ� �迭�� ����
	while ((c = fgetc(input_fp)) != EOF) {
		//printf("%c", c);
		text[i++] = c;
	}
	text[i] = '\0';
	printf("input.txt : %s\n", text);

	int reading_location = 0;
	char cmp_text[MAX_KEY_SIZE];
	char reading_location_char_to_string[2];
	cmp_text[0] = '\0';
	char previous_key[MAX_KEY_SIZE];
	char will_be_encoded_index = 0;
	while (1) {
		if(text[reading_location] != '\0'){
			reading_location_char_to_string[0] = text[reading_location];
			reading_location_char_to_string[1] = '\0';
			strcat(cmp_text, reading_location_char_to_string);
			
			will_be_encoded_index = find_previous_key_location(encoding_table_ptr, cmp_text);
			if (will_be_encoded_index != -1) {
				strcpy(previous_key, cmp_text);
				reading_location++;
			}
			else {
				insert_table(encoding_table_ptr, cmp_text);
				printf("%d ", find_previous_key_location(encoding_table_ptr, previous_key));
				encode[encode_index++] = find_previous_key_location(encoding_table_ptr, previous_key);
				cmp_text[0] = '\0';
				previous_key[0] = '\0';
			}
		}
		else{
			// TODO: ���̳ʸ��� �����ϴ� ���� �ʿ�
			printf("%d ", find_previous_key_location(encoding_table_ptr, previous_key));
			encode[encode_index++] = find_previous_key_location(encoding_table_ptr, previous_key);
			break;
		}
	}

	//decoding
	int decode_index = 0;
	FILE *recoveredinput_write = fopen("recoverdinput.txt", "w");
	while (decode_index < encode_index) {
		strcpy(tmp, decoding_table_ptr->table + encode[decode_index]);
		fprintf(recoveredinput_write, tmp);
		if (decode_index + 1 == encode_index)break;
		strcpy(tmp2, decoding_table_ptr->table + encode[decode_index+1]);
		reading_location_char_to_string[0] = tmp2[0];
		reading_location_char_to_string[1] = '\0';
		strcat(tmp, reading_location_char_to_string);
		insert_table(decoding_table_ptr, tmp);

		/*printf("���ڵ��� ���ڿ� %s\n", tmp);
		printf("decode_index = %d, encode_index = %d\n", decode_index, encode_index);%
		*/
		
		
		tmp[0] = '\0';
		tmp2[0] = '\0';
		decode_index++;
	}

	fclose(input_fp);
	fclose(recoveredinput_write);
	system("pause");
	
	return 0;
}