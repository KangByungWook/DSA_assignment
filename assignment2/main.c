//
//  main.c
//  hanoi
//
//  Created by KangByung wook on 2016. 3. 18..
//  Copyright © 2016년 KangByung wook. All rights reserved.
//

#include <stdio.h>

int total_action = 0;

// 기둥이 세개 있는 경우 -> start(시작점): 1번기둥, middle(중간점): 2번기둥, end(목표점): 3번 기둥
void tower_3(int n, int start, int middle , int end){
    // 종결조건
    if(n == 1){
        // 원판이 하나일 경우 시작점에서 목표점으로 원판을 옮긴 후 종료한다.
        printf("%d번에서 %d번으로 옮겼습니다.\n",start,end);
        total_action++;
    }
    else{
        // 원판이 한 개 이상일 경우 n-1개 만큼 tower_3를 실행하는데 목표점을 2번 기둥(middle)으로, 중간점을 3번 기둥(end)으로 한다.
        // 즉 시작점(start)에서 맨 아래원판을 제외한 나머지를 2번기둥으로 옮김(재귀함수 호출)
        tower_3(n-1,start,end,middle);
        
        // 시작점(start)에 남은 맨 아래 원판을 목표점(end)으로 옮긴다.
        printf("%d번에서 %d번으로 옮겼습니다.\n",start,end);
        total_action++;
        
        // 그리고 2번 기둥에 있던 n-1개의 나머지 원판들을, 1번 기둥을 중간점(middle)으로 하여 목표점(end)으로 옮긴다.(재귀함수 호출)
        tower_3(n-1,middle,start,end);
    }
}

// 기둥이 네개 있는 경우 -> start(시작점): 1번기둥, middle1(중간점1): 2번기둥, middle2(중간점2): 3번기둥, end(목표점): 4번기둥
void tower_4(int n, int start, int middle1, int middle2, int end){
    // 종결조건1
    if(n == 1){
        // 원판이 하나일 경우 시작점에서 목표점으로 원판을 옮긴 후 종료
        printf("%d번에서 %d번으로 옮겼습니다.\n",start,end);
        total_action++;
    }
    // 종결조건2
    else if(n==2){
        // 원판이 두개일 경우 작은 원판을 시작점에서 중간점2(middle2)로 이동 한 후,
        printf("%d번에서 %d번으로 옮겼습니다.\n",start,middle2);
        total_action++;
        // 다음 원판을 목표점(end)으로 이동하고,
        printf("%d번에서 %d번으로 옮겼습니다.\n",start,end);
        total_action++;
        // 중간점2(middle2)에 있던 작은 원판을 목표점(end)에 옮기고 종료
        printf("%d번에서 %d번으로 옮겼습니다.\n",middle2,end);
        total_action++;
    }
    // n이 종결조건에 해당하지 않는 경우
    else{
        // n-2개 만큼의 원판을 시작점(start)에서 중간점1(middle1)로 옮긴다.(재귀함수 호출)
        tower_4(n-2, start, middle2, end, middle1);
        // 시작점(start)에 남은 아래 두개의 원판중 작은 원판을 중간점2(middle2)로 옮긴다
        printf("%d번에서 %d번으로 옮겼습니다.\n",start,middle2);
        total_action++;
        // 시작점(start)에 남은 아래 두개의 원판중 큰 원판을 목표점(end)으로 옮긴다
        printf("%d번에서 %d번으로 옮겼습니다.\n",start,end);
        total_action++;
        // 중간점2(middle2)에 있던 원판을 목표점(end)으로 옮긴다.
        printf("%d번에서 %d번으로 옮겼습니다.\n",middle2,end);
        total_action++;
        // 중간점1(middle1)에 있던 n-2개의 원판을 목표점으로 이동한다(재귀함수 호출)
        tower_4(n-2, middle1, start, middle2, end);
    }
}

void tower_5(int n, int start, int middle1, int middle2, int middle3, int end){
    // 종결조건1
    if(n == 1){
        // 원판이 하나일 경우 시작점에서 목표점으로 원판을 옮긴 후 종료
        printf("%d번에서 %d번으로 옮겼습니다.\n",start,end);
        total_action++;
    }
    // 종결조건2
    else if(n == 2){
        // 원판이 두개일 경우 작은 원판을 시작점에서 중간점1(middle1)로 이동 한 후,
        printf("%d번에서 %d번으로 옮겼습니다.\n",start, middle1);
        total_action++;
        // 다음 원판을 목표점(end)으로 이동하고,
        printf("%d번에서 %d번으로 옮겼습니다.\n",start, end);
        total_action++;
        // 중간점1(middle1)에 있던 작은 원판을 목표점(end)에 옮기고 종료
        printf("%d번에서 %d번으로 옮겼습니다.\n",middle1, end);
        total_action++;
    }
    // 종결조건3
    else if(n==3){
        // 원판이 새개일 경우 작은 원판을 중간점1(middle1)로 이동 한 후,
        printf("%d번에서 %d번으로 옮겼습니다.\n",start, middle1);
        total_action++;
        // 두번째로 큰 원판을 중간점2(middle2)로 이동하고
        printf("%d번에서 %d번으로 옮겼습니다.\n",start, middle2);
        total_action++;
        // 가장 작은 원판을 목표점(end)로 옮긴다.
        printf("%d번에서 %d번으로 옮겼습니다.\n",start, end);
        total_action++;
        // 그리고 중간점2(middle2)에 있던 두번째로 큰 원판을 목표점(end)로 옮기고
        printf("%d번에서 %d번으로 옮겼습니다.\n",middle2, end);
        total_action++;
        // 중간점1(middle1)에 있던 가장 작은 원판을 목표점(end)로 옮긴다.
        printf("%d번에서 %d번으로 옮겼습니다.\n",middle1, end);
        total_action++;
    }
    // n이 종결조건에 해당하지 않는 경우
    else{
        // n-3개 만큼의 원판을 일단 중간점1(middle1)으로 옮긴다(재귀함수 호출)
        tower_5(n-3,start,middle1,middle2,end,middle1);
        // 시작점(start)에 남은 세개의 원판 중 가장 작은 원판을 중간점2(middle2)로 이동
        printf("%d번에서 %d번으로 옮겼습니다.\n",start, middle2);
        total_action++;
        // 시작점(start)에 남은 세개의 원판 중 두번째로 작은 원판을 중간점3(middle3)으로 이동
        printf("%d번에서 %d번으로 옮겼습니다.\n",start, middle3);
        total_action++;
        // 시작점(start)에 남은 가장 작은 원판을 목표점(end)으로 이동
        printf("%d번에서 %d번으로 옮겼습니다.\n",start, end);
        total_action++;
        // 시작점3(middle3)에 있던 원판을 목표점(end)으로 이동
        printf("%d번에서 %d번으로 옮겼습니다.\n",middle3, end);
        total_action++;
        // 시작점2(middle2)에 있던 원판을 목표점(end)으로 이동
        printf("%d번에서 %d번으로 옮겼습니다.\n",middle2, end);
        total_action++;
        // 중간점1(middle1)에 있던 n-3개의 원판을 목표점으로 이동(재귀함수 호출)
        tower_5(n-3,middle1,start,middle2,middle3,end);
    }
}



int main(int argc, const char * argv[]) {

    int number = 0, tower_number;
    while (1) {
        // 타워의 갯수 입력받기
        printf("몇개의 타워로 플레이하시겠습니까?(3,4,5중 선택 | 0 입력시 종료) : ");
        scanf("%d",&tower_number);
        
        // 0을 입력받았을 경우 반복문 탈출하여 게임 종료
        if (tower_number == 0) {
            printf("게임을 종료합니다\n");
            break;
        }
        
        // 3,4,5가 아닌 숫자를 타워의 갯수로 받았을 경우 다시 입력받음
        if(tower_number < 3 || tower_number > 5){
            printf("3 | 4 | 5 중에서 선택해주세요\n");
            continue;
        }
        
        // 유효한 타워의 갯수를 입력받았을 경우
        else{
            // 유효한 원판의 갯수를 입력받을때까지 반복문 실행
            while (number <= 0) {
                // 원판의 갯수를 입력받음
                printf("몇개의 원판으로 플레이하시겠습니까?(1 이상) : ");
                scanf("%d",&number);
                
                // 0 또는 음수를 입력받았을 경우 양수를 입력하라는 안내와 함께 원판의 갯수를 다시 입력받음
                if(number <=0){
                    printf("양수를 입력해주세요\n");
                }
            }
            // 입력받은 타워의 갯수에 따라 각각 정의한 함수를 실행
            switch (tower_number) {
                case 3:
                    tower_3(number, 1, 2, 3);
                    break;
                case 4:
                    tower_4(number, 1, 2, 3, 4);
                    break;
                case 5:
                    tower_5(number, 1, 2, 3, 4, 5);
                    break;
                default:
                    break;
            }
            // 총 움직인 횟수 출력
            printf("총 움직인 횟수 : %d\n",total_action);
            
            // 총 움직인 횟수와 원판의 갯수 0으로 초기화
            total_action = 0;
            number = 0;
        }
    }
    
    return 0;
}
