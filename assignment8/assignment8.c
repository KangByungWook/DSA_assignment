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
    int size;//��������� ���������� ��ġ�� ���� ��
    int found;//�̹� �Ÿ��� ��ΰ� ���� ���� ǥ��
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

Way route[STATION];//�� ������ �Ÿ��� ��θ� ����

//��������κ��� �ٸ� ��� ��������� �ִܰŸ��� �� ��θ� ã�´�
void dijkstra(int start)
{
    double min;
    int roc=start;//�������� �Ÿ��� �˻��ϴ� ��
    int i,j,k;
    
    route[start].way[0]=start;
    //��ο� �Ÿ� �ʱ�ȭ
    for(i=0;i<STATION;i++)
    {
        route[i].distance=weight[start][i];
        route[i].size=1;
        route[i].found=FALSE;
        route[i].way[0]=start;
    }
    //���� �� �ʱ�ȭ
    route[start].found=TRUE;
    route[start].size++;
    
    
    for(i=0;i<STATION;i++)//i>=������� ��ΰ� Ȯ�ε� ��
    {
        
        //������� ��θ� ã�� ���� �����ϰ� ������ �� ���� ����� ���� ã�´�
        min=INF;
        for(j=0;j<STATION;j++)//j=���� ��θ� �˻����� ��
        {
            if(!route[j].found && min>route[j].distance)
            {
                
                min=route[j].distance;
                roc=j;
                
            }
        }
        route[roc].found=TRUE;
        
        //�˻��ϴ� �������� ��� ���ΰ�ħ
        route[roc].size++;
        route[roc].way[route[roc].size-1]=roc;
        
        
        //���� ����� �����κ��� ������ ��������� �Ÿ��� ���ΰ�ħ�Ѵ�
        for(j=0;j<STATION;j++)
        {
            if(!route[j].found)
            {
                //���� �Ÿ����� ���� ã�� �Ÿ��� �� ª�� ���
                if(route[j].distance > (min+weight[roc][j]))
                {
                    route[j].distance = min+weight[roc][j];
                    
                    //���ο� ��θ� ã�����Ƿ� ��� ���ΰ�ħ
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
        //ȯ�¿��� ���, ȯ�¿��� ��� Ȥ�� �������� �ƴҶ�
        if(route[des].way[i]!=start && route[des].way[i]!=des && is_transfer_station(route[des].way[i]+1))
        {
        	//ȯ�¿� �յڷ� ����ȣ������ ���밪��  2 ���ϸ� ȯ���� �ƴ�, �� ���� ��츸 ȯ��
            if((route[des].way[i+1]-route[des].way[i-1])> 2 || (route[des].way[i+1]-route[des].way[i-1]) < -2)
            {	
            	printf("(ȯ��)");
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
        printf("��߿��� ��ȣ�� �Է��ϼ���(1~47):");
        scanf("%d",&start);
        printf("�������� ��ȣ�� �Է��ϼ���(1~47):");
        scanf("%d",&stationNum);
        if(start < 1 || start > 47 ||stationNum < 1 || stationNum > 47 ){
        	printf("��ȣ�� �ٽ� �Է����ּ���(2�� �� �ٽ� �Է��� �޽��ϴ�.)\n");
        	Sleep(2000);
			system("cls"); continue;
		}
		stationNum--;
        start--;
        dijkstra(start);
        printWay(start,stationNum);
        printf("�Ÿ�:%lfkm\n",route[stationNum].distance);
        printf("���:%d won\n",1250+((int)route[stationNum].distance/10)*80);
        printf("��� �Ͻ÷��� �ƹ� ���ڳ� �Է� �� ���͸� ��������(����:q)\n");
        scanf("%s",cmd);
        if(!strcmp(cmd,"q"))break;
        else{
        	system("cls");
		}
        
    }
    
    return 0;
}
