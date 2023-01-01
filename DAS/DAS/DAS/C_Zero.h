#pragma once
#include <list>
#include "character.h"
#include "Bullet.h"
#include "Defender.h"
#include "B_NormalBullet.h"
#include "B_WideBullet.h"
#include "B_ZeroBullet.h"
#include "D_ZeroDefender.h"
#include "Sound.h"

using namespace std;

#define ZERO_VX 2
#define ZERO_VY 2
#define ZERO_BV 4
#define ZERO_MAXHP 8

#define ZERO_MAXSTOCK_1 9
#define ZERO_MAXSTOCK_2 3
#define ZERO_MAXSTOCK_3 2
#define ZERO_MAXSTOCK_4 1

#define ZERO_DELAY_1 45
#define ZERO_DELAY_2 90
#define ZERO_DELAY_3 240
#define ZERO_DELAY_4 3000

#define ZERO_PDELAY_1 1
#define ZERO_PDELAY_2 1
#define ZERO_PDELAY_3 1
#define ZERO_PDELAY_4 1

#define ZERO_BEHAVIORNUM_1 1
#define ZERO_BEHAVIORNUM_2 1
#define ZERO_BEHAVIORNUM_3 1
#define ZERO_BEHAVIORNUM_4 1

#define ZERO_BEHAVIORDELAY_1 1
#define ZERO_BEHAVIORDELAY_2 1
#define ZERO_BEHAVIORDELAY_3 1
#define ZERO_BEHAVIORDELAY_4 1


class C_Zero :
	public Character
{
public:
	C_Zero(LPDIRECT3DDEVICE9 _dev, AudioDevicePtr _aud_dev, wchar_t* _name, vector<Image*>* _dielist);
	~C_Zero(void);
	void behavior1(list<Bullet*>* bulletlist, int x, int y, bool flag);
	void behavior2(list<Bullet*>* bulletlist, int x, int y, bool flag);
	void behavior3(list<Bullet*>* bulletlist, int x, int y, bool flag);
	void behavior4(list<Defender*>* defenderlist, int x, int y, int* inftime, int* worldtime, bool flag);
	void loadimage();
	void loadsound();
};

