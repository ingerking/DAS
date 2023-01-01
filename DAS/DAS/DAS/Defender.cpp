#include "Defender.h"


Defender::Defender(float _x, float _y, float _vx, float _vy, int _charnum, int _defnum, list<Defender*>* _defenderlist)
{
	x=_x;
	y=_y;
	vx=_vx;
	vy=_vy;
	charnum=_charnum;
	defnum=_defnum;
	usable=true;
	defenderlist=_defenderlist;
}


Defender::~Defender(void)
{
}
