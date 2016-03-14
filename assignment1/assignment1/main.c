//
//  main.c
//  assignment1
//
//  Created by KangByung wook on 2016. 3. 14..
//  Copyright © 2016년 KangByung wook. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rsp.h"


void print_status(member team_array[], int array_num);
member* create_new_team(char* team_name, int member_num);
int fight(member* my_team_member, member* enemy_team_member);

int main(int argc, const char * argv[]) {
    char my_team_name[200], enemy_team_name[200];
    int member_number;
    
    // 난수 생성을 위한 시드 생성
    srand(time(NULL));
    // 우리팀 및 상대팀 이름 입력받기
    printf("우리팀 이름 : ");scanf("%200s",my_team_name);fflush(stdin);
    printf("상대팀 이름 : ");scanf("%200s", enemy_team_name);fflush(stdin);
    
    // 각팀의 인원수 입력 받기
    printf("각팀의 인원수 : ");scanf("%d",&member_number);
    
    // 입력받은 인원수로 각팀의 배열 메모리 할당하기
    member* my_team_array_p = (member*)malloc(member_number*sizeof(member));
    member* enemy_team_array_p = (member*)malloc(member_number*sizeof(member));
    
    // 각 팀의 member배열 초기화
    for(int i = 0 ; i < member_number ; i++){
        (my_team_array_p+i)->team = my_team_name;
        (my_team_array_p+i)->weapon = rand()%3 + 1;
        (my_team_array_p+i)->num = i;
        (my_team_array_p+i)->islive = 1;
        (enemy_team_array_p+i)->team = my_team_name;
        (enemy_team_array_p+i)->weapon = rand()%3 + 1;
        (enemy_team_array_p+i)->num = i;
        (enemy_team_array_p+i)->islive = 1;
    }
    
    print_status(my_team_array_p, member_number);
    print_status(enemy_team_array_p, member_number);
    fight(my_team_array_p, enemy_team_array_p);
    print_status(my_team_array_p, member_number);
    print_status(enemy_team_array_p, member_number);
    return 0;
}

