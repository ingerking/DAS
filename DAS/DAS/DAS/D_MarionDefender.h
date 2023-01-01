#pragma once

#include <stdlib.h>
#include "Defender.h"
#include "D_MarionCandy.h"

class D_MarionDefender :
	public Defender
{
private:
	int count;
public:
	D_MarionDefender(float _x, float _y, float _vx, float _vy, int _charnum, int _defnum, list<Defender*>* _defenderlist);
	~D_MarionDefender(void);
	void update();
	void collapse(Bullet* bullet);
};

