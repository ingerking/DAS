#pragma once
#include "defender.h"
class D_ZeroDefender :
	public Defender
{
private:
	int counter;
public:
	D_ZeroDefender(float _x, float _y, float _vx, float _vy, int _charnum, int _defnum, list<Defender*>* _defenderlist);
	~D_ZeroDefender(void);
	void update();
	void collapse(Bullet* bullet);
};

