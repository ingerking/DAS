#include "D_ZeroDefender.h"


D_ZeroDefender::D_ZeroDefender(float _x, float _y, float _vx, float _vy, int _charnum, int _defnum, list<Defender*>* _defenderlist):Defender(_x, _y, _vx, _vy, _charnum, _defnum, defenderlist)
{
	counter=0;

	box1.left=-90;
	box1.right=90;
	if(_vy<0){
		box1.up=-28;
		box1.down=-5;
	}
	else{
		box1.up=5;
		box1.down=28;
	}
	box2.left=-5;
	box2.right=5;
	box2.up=-68;
	box2.down=68;
}


D_ZeroDefender::~D_ZeroDefender(void)
{
}


void D_ZeroDefender::update(){
	x+=vx;
	y+=vy;
	if(vy<0){
		if(y<200){
			if(counter>=4){
				counter=0;
				vy--;
			}
		}
		else if(y<350)
			vy=-2.0f;
	}
	else{
		if(y>250){
			if(counter>=4){
				counter=0;
				vy++;
			}
		}
		else if(y>100)
			vy=2.0f;
	}

	if(x>MAP_WIDTH)
		usable=!(x>DEF_MAP_OUT+MAP_WIDTH);
	else if(x<0)
		usable=!(x<-DEF_MAP_OUT);
	if(y>MAP_HEIGHT)
		usable=!(y>DEF_MAP_OUT+MAP_HEIGHT);
	else if(y<0)
		usable=!(y<-DEF_MAP_OUT);

	counter++;
}

void D_ZeroDefender::collapse(Bullet* bullet){
	if(bullet->checkcollapse(&box1, x, y)){
		bullet->setcollapse();
	}
	else if(bullet->checkcollapse(&box2, x, y)){
		bullet->setcollapse();
	}
}