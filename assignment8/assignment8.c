#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define STATION 47
#define INF 1000

typedef struct Way
{
    double distance;
    int way[STATION];
    int size;//출발지부터 도착지까지 거치는 역의 수
    int found;//이미 거리와 경로가 계산된 곳을 표시
}Way;

int transfer_station_list[] = {3,5,6,12,16,17,19,21,22,24,29,37};

int is_transfer_station(int n){
	int i ;
	for(i = 0 ; i < 12 ; i++){
		if(n==transfer_station_list[i])return TRUE;
	}
	return FALSE;
}

double weight[STATION][STATION]={
{0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{1,	0,	  1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	  1,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	1,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	1,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	1,	INF,	INF,	INF,	INF,	1,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	1,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	1,	  0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	1,	  0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	  0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	  0,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	1,	INF,	INF,	INF},
{INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	1,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	1,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	1,	INF,	INF,	INF,	INF,	INF,	1,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	0,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	0,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	1,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	0,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	1,},
{INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	0,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	0,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	0,	1,	INF,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	1,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	0,	INF,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	0,	INF,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	0,	INF,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	0,	INF,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	0,	INF},
{INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	1,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	INF,	0}
};

Way route[STATION];//각 역까지 거리와 경로를 저장

//출발점으로부터 다른 모든 역들까지의 최단거리와 그 경로를 찾는다
void dijkstra(int start)
{
    double min;
    int roc=start;//기준으로 거리를 검사하는 역
    int i,j,k;
    
    route[start].way[0]=start;
    //경로와 거리 초기화
    for(i=0;i<STATION;i++)
    {
        route[i].distance=weight[start][i];
        route[i].size=1;
        route[i].found=FALSE;
        route[i].way[0]=start;
    }
    //시작 역 초기화
    route[start].found=TRUE;
    route[start].size++;
    
    
    for(i=0;i<STATION;i++)//i>=현재까지 경로가 확인된 역
    {
        
        //현재까지 경로를 찾은 역을 제외하고 나머지 중 가장 가까운 곳을 찾는다
        min=INF;
        for(j=0;j<STATION;j++)//j=현재 경로를 검사중인 역
        {
            if(!route[j].found && min>route[j].distance)
            {
                
                min=route[j].distance;
                roc=j;
                
            }
        }
        route[roc].found=TRUE;
        
        //검사하는 역까지의 경로 새로고침
        route[roc].size++;
        route[roc].way[route[roc].size-1]=roc;
        
        
        //가장 가까운 역으로부터 나머지 역들까지의 거리를 새로고침한다
        for(j=0;j<STATION;j++)
        {
            if(!route[j].found)
            {
                //현재 거리보다 새로 찾은 거리가 더 짧은 경우
                if(route[j].distance > (min+weight[roc][j]))
                {
                    route[j].distance = min+weight[roc][j];
                    
                    //새로운 경로를 찾았으므로 경로 새로고침
                    route[j].size=route[roc].size;
                    for(k=0;k<route[roc].size;k++)
                    {
                        route[j].way[k]=route[roc].way[k];
                    }
                }
            }
        }
    }
    
}

void printWay(int start, int des)
{
    int i;
    
    for(i=0;i<route[des].size;i++)
    {
        printf("%d ",route[des].way[i]+1);
        //환승역인 경우, 환승역이 출발 혹은 도착역이 아닐때
        if(route[des].way[i]!=start && route[des].way[i]!=des && is_transfer_station(route[des].way[i]+1))
        {
        	//환승역 앞뒤로 역번호차이의 절대값이  2 이하면 환승이 아님, 그 외의 경우만 환승
            if((route[des].way[i+1]-route[des].way[i-1])> 2 || (route[des].way[i+1]-route[des].way[i-1]) < -2)
            {	
            	printf("(환승)");
            }
        }
        if(i!=route[des].size-1)
            printf("-> ");
        Sleep(300);
    }
    printf("\n");
    
}

int main(void)
{
    int stationNum;
    int start;
    char cmd[10];
    while(1)
    {
        printf("출발역의 번호를 입력하세요(1~47):");
        scanf("%d",&start);
        printf("도착역의 번호를 입력하세요(1~47):");
        scanf("%d",&stationNum);
        if(start < 1 || start > 47 ||stationNum < 1 || stationNum > 47 ){
        	printf("번호를 다시 입력해주세요(2초 뒤 다시 입력을 받습니다.)\n");
        	Sleep(2000);
			system("cls"); continue;
		}
		stationNum--;
        start--;
        dijkstra(start);
        printWay(start,stationNum);
        printf("거리:%lfkm\n",route[stationNum].distance);
        printf("요금:%d won\n",1250+((int)route[stationNum].distance/10)*80);
        printf("계속 하시려면 아무 문자나 입력 후 엔터를 누르세요(종료:q)\n");
        scanf("%s",cmd);
        if(!strcmp(cmd,"q"))break;
        else{
        	system("cls");
		}
        
    }
    
    return 0;
}
