#pragma once
#include "defender.h"

#define MARIONCANDYACC 1
#define MARIONCANDYVEL 2

class D_MarionCandy :
	public Defender
{
private:
	bool vflag;
	int count;
public:
	D_MarionCandy(float _x, float _y, float _vx, float _vy, int _charnum, int _defnum, list<Defender*>* _defenderlist);
	~D_MarionCandy(void);
	void update();
	void collapse(Bullet* bullet);
};

