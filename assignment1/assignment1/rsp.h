//
//  rsp.h
//  assignment1
//
//  Created by KangByung wook on 2016. 3. 15..
//  Copyright © 2016년 KangByung wook. All rights reserved.
//

#ifndef rsp_h
#define rsp_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//구조체 정의
typedef struct member{
    char *team;
    int num;
    int weapon;
    int islive;
}member;

// 팀 멤버의 상태를 출력해주는 함수
void print_status(member* team_array_p, int array_num){
    printf("----------%s팀의 상태----------\n",team_array_p->team);
    for(int i = 0; i < array_num ; i++){
        printf("팀 이름: %s, 번호: %d, 무기 : %d, 생존 여부 : %d\n", (*(team_array_p + i)).team, (*(team_array_p + i)).num, (*(team_array_p + i)).weapon, (*(team_array_p + i)).islive);
    }
};

member* create_new_team(char* team_name, int member_num){
    member* tmp_member_array_p = (member*)malloc(member_num*sizeof(team_name));
    for(int i = 0 ; i < member_num ; i++){
        (*(tmp_member_array_p+i)).team = team_name;
        (*(tmp_member_array_p+i)).num = i;
        (*(tmp_member_array_p+i)).weapon = rand()%3+1;
        (*(tmp_member_array_p+i)).islive = 1;
    }
    return tmp_member_array_p;
}

// 리턴값: -1(패배), 0(무승부), 1(승리)
int fight(member* my_team_member, member* enemy_team_member){
    srand(time(NULL));
    int tmp_weapon;
    // 내가 이기는 조건
    if((my_team_member->weapon != 1 && my_team_member->weapon - enemy_team_member->weapon == 1) || (my_team_member->weapon == 1 && my_team_member->weapon - enemy_team_member->weapon == -2)){
        enemy_team_member->islive = 0;
        printf("승리하였습니다\n");
        // 50퍼센트 확률로 무기를 바꾸지 않는 경우
        if((rand()%2 == 1) ? 0 : 1){
        }
        // 50퍼센트 확률로 무기를 바꾸는 경우
        else{
            tmp_weapon = my_team_member->weapon;
            my_team_member->weapon = enemy_team_member -> weapon;
            enemy_team_member->weapon = tmp_weapon;
            printf("%d으로 무기를 바꾸었습니다\n", my_team_member->weapon);
        }
        return 1;
    }
    // 무승부 조건
    else if(my_team_member->weapon == enemy_team_member->weapon){
        printf("무승부입니다");
        return 0;
    }
    // 이기거나 비기는 경우를 제외한 나머지는 패배
    else{
        printf("패배하였습니다\n");
        my_team_member->islive = 0;
        // 50퍼센트 확률로 무기를 바꾸지 않는 경우
        if((rand()%2 == 1) ? 0 : 1){
        }
        // 50퍼센트 확률로 무기를 바꾸는 경우
        else{
            tmp_weapon = my_team_member->weapon;
            my_team_member->weapon = enemy_team_member -> weapon;
            enemy_team_member->weapon = tmp_weapon;
        }

        return -1;
    }
}

// 해당 팀에서 생존해있는 멤버의 index를 리턴
// 전멸했을 경우 -1 리턴
int find_alive_member_number(member* member_array_p, int member_num){
    for(int i = 0 ; i < member_num ; i++){
        if((member_array_p+i)->islive == 1)return i;
    }
    return -1;
}

#endif /* rsp_h */
