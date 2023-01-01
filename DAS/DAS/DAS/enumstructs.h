#pragma once

#include <audiere.h>

using namespace audiere;

#define KEY_LEFT 0x01
#define KEY_RIGHT 0x02
#define KEY_UP 0x04
#define KEY_DOWN 0x08
#define KEY_Z 0x10
#define KEY_X 0x20
#define KEY_C 0x40
#define KEY_A 0x80

#define MAP_WIDTH 300
#define MAP_HEIGHT 450

#define PVP_MAP_LEFT 50
#define PVP_MAP_UP 70
#define PVP_MAP_RIGHT 750
#define PVP_MAP_DOWN 520

#define BUL_MAP_OUT 50
#define DEF_MAP_OUT 150
#define DEF_MAP_OUT_WIDTH 50

typedef struct User{
	int usernum;
	int charnum;
	bool team;
}User;

typedef struct Collapsebox{
	int left;
	int right;
	int up;
	int down;
}Collapsebox;

enum PLAYMODE{
	PM_TOP, PM_OPTION, PM_PLAY, PM_QUIT
};

enum GAMEMODE{
	GM_PVP, GM_NETWORK, GM_REPLAY
};

enum GAMESTATUS{
	GS_SELECT, GS_LOADING, GS_READY, GS_PLAYING
};

enum STATUS{
	ST_NONE, ST_THEWORLD, ST_CLOAK
};

typedef struct BulletArgument{
	int xbox, ybox;
	bool box;
}BulletArgument;

