#pragma once
#include <list>
#include "character.h"
#include "Bullet.h"
#include "Defender.h"
#include "B_NormalBullet.h"
#include "B_WideBullet.h"
#include "D_MarionDefender.h"
#include "Sound.h"

using namespace std;

#define MARION_VX 2
#define MARION_VY 2
#define MARION_BV 4
#define MARION_MAXHP 8

#define MARION_MAXSTOCK_1 9
#define MARION_MAXSTOCK_2 4
#define MARION_MAXSTOCK_3 3
#define MARION_MAXSTOCK_4 1

#define MARION_DELAY_1 60
#define MARION_DELAY_2 180
#define MARION_DELAY_3 300
#define MARION_DELAY_4 3000

#define MARION_PDELAY_1 1
#define MARION_PDELAY_2 1
#define MARION_PDELAY_3 1
#define MARION_PDELAY_4 1

#define MARION_BEHAVIORNUM_1 1
#define MARION_BEHAVIORNUM_2 1
#define MARION_BEHAVIORNUM_3 3
#define MARION_BEHAVIORNUM_4 1

#define MARION_BEHAVIORDELAY_1 1
#define MARION_BEHAVIORDELAY_2 1
#define MARION_BEHAVIORDELAY_3 10
#define MARION_BEHAVIORDELAY_4 1

class C_Marion :
	public Character
{
public:
	C_Marion(LPDIRECT3DDEVICE9 _dev, AudioDevicePtr _aud_dev, wchar_t* _name, vector<Image*>* _dielist);
	~C_Marion(void);
	void behavior1(list<Bullet*>* bulletlist, int x, int y, bool flag);
	void behavior2(list<Bullet*>* bulletlist, int x, int y, bool flag);
	void behavior3(list<Bullet*>* bulletlist, int x, int y, bool flag);
	void behavior4(list<Defender*>* defenderlist, int x, int y, int* inftime, int* worldtime, bool flag);
	void loadimage();
	void loadsound();
};

