#include "D_MarionCandy.h"


D_MarionCandy::D_MarionCandy(float _x, float _y, float _vx, float _vy, int _charnum, int _defnum, list<Defender*>* _defenderlist):Defender(_x, _y, _vx, _vy, _charnum, _defnum, defenderlist)
{
	int vel=MARIONCANDYVEL+(rand()%4);
	vflag=_vy<0;
	count=0;
	if(vflag)
		vy=vel;
	else
		vy=-vel;
}


D_MarionCandy::~D_MarionCandy(void)
{
}

void D_MarionCandy::update(){
	x+=vx;
	y+=vy;
	count++;
	if(count==9){
		if(vflag)
			vy-=MARIONCANDYACC;
		else
			vy+=MARIONCANDYACC;
		count=0;
	}
	
	if(x>MAP_WIDTH)
		usable=!(x>DEF_MAP_OUT_WIDTH+MAP_WIDTH);
	else if(x<0)
		usable=!(x<-DEF_MAP_OUT_WIDTH);
	if(y>MAP_HEIGHT)
		usable=!(y>DEF_MAP_OUT+MAP_HEIGHT);
	else if(y<0)
		usable=!(y<-DEF_MAP_OUT);
}

void D_MarionCandy::collapse(Bullet* bullet){
	;
}