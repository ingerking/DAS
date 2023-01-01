#include "D_MarionDefender.h"


D_MarionDefender::D_MarionDefender(float _x, float _y, float _vx, float _vy, int _charnum, int _defnum, list<Defender*>* _defenderlist):Defender(_x, _y, _vx, _vy, _charnum, _defnum, _defenderlist)
{
	count=3;
}


D_MarionDefender::~D_MarionDefender(void)
{
}

void D_MarionDefender::update(){
	if(count>0)
		count--;
	else
		usable=false;
}

void D_MarionDefender::collapse(Bullet* bullet){
	Defender* defender;
	int i, j;
	if(usable){
		i=(rand()%7)-3;
		j=rand()%9;
		defender=new D_MarionCandy(bullet->getx(), bullet->gety(), i, y<0?-1.0f:1.0f, charnum, j, defenderlist);
		defenderlist->push_back(defender);
		bullet->setusable(false);
	}
}