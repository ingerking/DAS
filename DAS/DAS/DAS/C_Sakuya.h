#pragma once
#include <list>
#include "character.h"
#include "Bullet.h"
#include "Defender.h"
#include "B_NormalBullet.h"
#include "Sound.h"

using namespace std;

#define SAKUYA_VX 2
#define SAKUYA_VY 2
#define SAKUYA_BV 4
#define SAKUYA_MAXHP 8

#define SAKUYA_MAXSTOCK_1 8
#define SAKUYA_MAXSTOCK_2 3
#define SAKUYA_MAXSTOCK_3 1
#define SAKUYA_MAXSTOCK_4 1

#define SAKUYA_DELAY_1 45
#define SAKUYA_DELAY_2 90
#define SAKUYA_DELAY_3 540
#define SAKUYA_DELAY_4 4200

#define SAKUYA_PDELAY_1 1
#define SAKUYA_PDELAY_2 1
#define SAKUYA_PDELAY_3 1
#define SAKUYA_PDELAY_4 45

#define SAKUYA_BEHAVIORNUM_1 1
#define SAKUYA_BEHAVIORNUM_2 1
#define SAKUYA_BEHAVIORNUM_3 8
#define SAKUYA_BEHAVIORNUM_4 1

#define SAKUYA_BEHAVIORDELAY_1 1
#define SAKUYA_BEHAVIORDELAY_2 1
#define SAKUYA_BEHAVIORDELAY_3 15
#define SAKUYA_BEHAVIORDELAY_4 1

#define WORLDTIME 540

class C_Sakuya :
	public Character
{
public:
	C_Sakuya(LPDIRECT3DDEVICE9 _dev, AudioDevicePtr _aud_dev, wchar_t* _name, vector<Image*>* _dielist);
	~C_Sakuya(void);
	void behavior1(list<Bullet*>* bulletlist, int x, int y, bool flag);
	void behavior2(list<Bullet*>* bulletlist, int x, int y, bool flag);
	void behavior3(list<Bullet*>* bulletlist, int x, int y, bool flag);
	void behavior4(list<Defender*>* defenderlist, int x, int y, int* inftime, int* worldtime, bool flag);
	void loadimage();
	void loadsound();
};

