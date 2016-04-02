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
#include <string.h>
#include <time.h>

//구조체 정의
//team : 팀명, num: 해당 플레이어의 ID, weapon: 1(가위),2(바위),3(보), islive: 0(죽음),1(생존)
typedef struct member{
    char *team;
    int num;
    int weapon;
    int islive;
}member;

//숫자로 표기된 무기를 string으로 바꿔주는 함수
char* weapon_to_str(int number){
    char *weapon_name;
    switch (number) {
        case 1:
            weapon_name = "가위";
            break;
        case 2:
            weapon_name = "바위";
            break;
        case 3:
            weapon_name = "보";
            break;
        default:
            break;
    }
    return weapon_name;
}

// 숫자로 표기된 생존 여부를 char형으로 바꿔주는 함수
char islive_to_char(int number){
    char value;
    switch (number) {
        case 0:
            value = 'X';
            break;
        case 1:
            value = 'O';
            break;
        default:
            break;
    }
    return value;
}

// 팀 멤버의 상태를 출력해주는 함수
void print_status(member* team_array_p,member* enemy_array_p, int array_num){
    printf("#################%s팀(당신)의 상태#################\n",team_array_p->team);
    for(int i = 0; i < array_num ; i++){
        printf("ID: %d, 무기 : %s, 생존 여부 : %c\n", (*(team_array_p + i)).num, weapon_to_str((*(team_array_p + i)).weapon), islive_to_char((*(team_array_p + i)).islive));
    }
    printf("#################%s팀(상대팀)의 상태#################\n",enemy_array_p->team);
    for(int i = 0; i < array_num ; i++){
        printf("ID: %d, 무기 : ??, 생존 여부 : %c\n", (*(enemy_array_p + i)).num, islive_to_char((*(enemy_array_p + i)).islive));
    }
};

// 승부를 판단하는 함수(custom function)
// 리턴값: -1(패배), 0(무승부), 1(승리)
int fight(member* my_team_member, member* enemy_team_member){
    srand(time(NULL));
    int tmp_weapon;
    // 내가 이기는 조건
    if((my_team_member->weapon != 1 && my_team_member->weapon - enemy_team_member->weapon == 1) || (my_team_member->weapon == 1 && my_team_member->weapon - enemy_team_member->weapon == -2)){
        enemy_team_member->islive = 0;
        sleep(2);
        printf("해설자 : 당신이 승리하였습니다!!!\n\n");
        sleep(2);
        // 50퍼센트 확률로 무기를 바꾸지 않는 경우
        if((rand()%2 == 1) ? 0 : 1){
        }
        // 50퍼센트 확률로 무기를 바꾸는 경우
        else{
            tmp_weapon = my_team_member->weapon;
            my_team_member->weapon = enemy_team_member -> weapon;
            enemy_team_member->weapon = tmp_weapon;
            printf("상대의 무기를 빼앗아 %s(으)로 무기를 바꾸었습니다!!!정말 자비가 없군요!!!\n\n", weapon_to_str(my_team_member->weapon));
        }
        return 1;
    }
    // 무승부 조건
    else if(my_team_member->weapon == enemy_team_member->weapon){
        printf("해설자 : 무승부입니다!! 역시 기대를 저버리지 않는 팽팽한 승부네요!!!\n\n");
        sleep(2);
        printf("해설자 : 각 팀의 선수들에게 다시 랜덤으로 무기가 제공됩니다\n\n");
        my_team_member->weapon = rand()%3+1;
        enemy_team_member->weapon = rand()%3+1;
        sleep(2);
        printf("(알림)당신의 플레이어 %d는 새로운 무기 %s을(를) 얻었습니다.\n\n",my_team_member->num,weapon_to_str(my_team_member->weapon));
        sleep(2);
        return 0;
    }
    // 이기거나 비기는 경우를 제외한 나머지는 패배
    else{
        sleep(2);
        printf("해설자 : 당신은 패배하였습니다!!!\n");
        my_team_member->islive = 0;
        sleep(2);
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
