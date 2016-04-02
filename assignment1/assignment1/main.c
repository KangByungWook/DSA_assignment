//
//  main.c
//  assignment1
//
//  Created by KangByung wook on 2016. 3. 14..
//  Copyright © 2016년 KangByung wook. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "rsp.h"


void print_status(member team_array[], member enemy_team_array[], int array_num);
int fight(member* my_team_member, member* enemy_team_member);
int find_alive_member_number(member* member_array_p, int member_num);

int main(int argc, const char * argv[]) {
    char my_team_name[200], enemy_team_name[200];
    int member_number, target_enemy_num;
    
    // 난수 생성을 위한 시드 생성
    srand(time(NULL));
    // 우리팀 및 상대팀 이름 입력받기
    printf("#################팀 이름을 입력해주세요#################\n");
    printf("우리팀 이름 : ");scanf("%200s",my_team_name);fflush(stdin);
    printf("상대팀 이름 : ");scanf("%200s", enemy_team_name);fflush(stdin);
    printf("\n해설자 : %s팀과 %s팀이 맞붙는 세기의 대결!! 과연 누가 이길까요?\n\n", my_team_name, enemy_team_name);
    sleep(1);
    printf("해설자 : 각 팀은 출전시킬 선수의 인원수를 정해주세요!!\n\n");
    // 각팀의 인원수 입력 받기
    sleep(1);
    printf("#################팀 인원수를 입력해주세요#################\n");
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
        (enemy_team_array_p+i)->team = enemy_team_name;
        (enemy_team_array_p+i)->weapon = rand()%3 + 1;
        (enemy_team_array_p+i)->num = i;
        (enemy_team_array_p+i)->islive = 1;
    }
    // 우리 팀과 상태 팀의 생성 현황 보기
    print_status(my_team_array_p,enemy_team_array_p, member_number);

    // 우리팀 또는 상대팀이 모두 전멸하기 전까지는 공격대상 입력을 받는다
    while(find_alive_member_number(my_team_array_p, member_number) != -1 && find_alive_member_number(enemy_team_array_p, member_number) != -1 ){
        printf("당신의 위대한 용사 플레이어 %d의 차례입니다. 어떤 상대와 싸우시겠습니까? : ", find_alive_member_number(my_team_array_p, member_number));
        scanf("%d", &target_enemy_num);
        if((enemy_team_array_p+target_enemy_num)->islive == 1){
            fight(my_team_array_p+find_alive_member_number(my_team_array_p, member_number), enemy_team_array_p+target_enemy_num);
            print_status(my_team_array_p, enemy_team_array_p, member_number);

        }
        else if(target_enemy_num >= member_number || target_enemy_num < 0)
            printf("해당 상대는 존재하지 않습니다\n");
        else
            printf("해당 상대는 이미 죽었습니다\n");
    }
    printf("\n\n");
    if(find_alive_member_number(my_team_array_p, member_number) == -1){
        printf("#####최종결과####\n\n");
        printf("당신은 패배하였습니다\n\n");
        printf("###############\n");
    }
    else{
        printf("#####최종결과####\n\n");
        printf("당신은 승리하였습니다\n\n");
        printf("###############\n");
    }
    // 메모리 해제
    free(my_team_array_p);
    free(enemy_team_array_p);
    return 0;
}

