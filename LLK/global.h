#pragma once

typedef struct  tagVertex
{
	int row;
	int col;
	int info;
}Vertex;

#define BLANK -1
#define MAX_ROW 6
#define MAX_COL 8
#define MAX_VERTEX_NUM 48
#define MAX_PIC_NUM 4
#define REPEAT_NUM 6
#define MAP_TOP 50
#define MAP_LETF 20
#define PIC_WIDTH 40
#define PIC_HEIGHT 40
#define PLAY_TIMER_ID 1
#define GAME_LOSE -1
#define GAME_SUCCESS 0
#define GAME_PLAY -1