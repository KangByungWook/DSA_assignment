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
	//printf("매개변수로 들어온 문자열 %s를 %d에 넣습니다", key, insert_location);

	strcpy(t_ptr->table + insert_location, key);
}

// 찾고자 하는 키와 같은 키가 있으면 위치 반환
// 없을 시 -1 반환
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
	printf("위치 : %d", find_previous_key_location(t_ptr, "kang"));
	system("pause");*/
	/////////////////////////////////////////////////

	// input파일 읽어가며 encoding + table 핸들링
	FILE* input_fp = fopen("input.txt", "r");
	
	TableType t;
	TableType_ptr t_ptr = &t;

	init_table(t_ptr);
	
	char c;
	char text[MAX_TEXT_SIZE];
	int i = 0;

	while ((c = fgetc(input_fp)) != EOF) {
		printf("%c", c);
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
			
			will_be_encoded_index = find_previous_key_location(t_ptr, cmp_text);
			if (will_be_encoded_index != -1) {
				strcpy(previous_key, cmp_text);
				reading_location++;
			}
			else {
				insert_table(t_ptr, cmp_text);
				printf("%d ", find_previous_key_location(t_ptr, previous_key));
				cmp_text[0] = '\0';
				previous_key[0] = '\0';
			}
		}
		else{
			printf("%d ", find_previous_key_location(t_ptr, previous_key));
			break;
		}
		
		
	}
	system("pause");
	
	return 0;
}