#include "Bullet.h"


Bullet::Bullet(float _x, float _y, float _vx, float _vy, int _charnum, int _bulnum, int _dmg)
{
	x=_x;
	y=_y;
	vx=_vx;
	vy=_vy;
	charnum=_charnum;
	bulnum=_bulnum;
	dmg=_dmg;
	usable=true;
}


Bullet::~Bullet(void)
{
}
