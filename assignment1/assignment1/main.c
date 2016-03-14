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
int find_alive_member_number(member* member_array_p, int member_num);

int main(int argc, const char * argv[]) {
    char my_team_name[200], enemy_team_name[200];
    int member_number, target_enemy_num;
    
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
    // 우리 팀의 생성 현형 보기
    print_status(my_team_array_p, member_number);

    while(find_alive_member_number(my_team_array_p, member_number) != -1 && find_alive_member_number(enemy_team_array_p, member_number) != -1 ){
        printf("현재 플레이어 : %d || 누구와 싸우시겠습니까? : ", find_alive_member_number(my_team_array_p, member_number));
        scanf("%d", &target_enemy_num);
        if((enemy_team_array_p+target_enemy_num)->islive != 1){
            printf("해당 상대는 이미 죽었습니다\n");
        }
        else
            fight(my_team_array_p+find_alive_member_number(my_team_array_p, member_number), enemy_team_array_p+target_enemy_num);
        
    }
    
    // 메모리 해제
    free(my_team_array_p);
    free(enemy_team_array_p);
    return 0;
}

