#include "B_NormalBullet.h"


B_NormalBullet::B_NormalBullet(float _x, float _y, float _vx, float _vy, int _charnum, int _bulnum, int _dmg):Bullet(_x, _y, _vx, _vy, _charnum, _bulnum, _dmg)
{
}


B_NormalBullet::~B_NormalBullet(void)
{
}

void B_NormalBullet::update(){
	x+=vx;
	y+=vy;
	if(x>MAP_WIDTH)
		usable=!(x>BUL_MAP_OUT+MAP_WIDTH);
	else if(x<0)
		usable=!(x<-BUL_MAP_OUT);
	if(y>MAP_HEIGHT)
		usable=!(y>BUL_MAP_OUT+MAP_HEIGHT);
	else if(y<0)
		usable=!(y<-BUL_MAP_OUT);
}

bool B_NormalBullet::checkcollapse(int _x, int _y){
	if(usable){
		if(x-NORMALBULLET_WIDTH<_x&&x+NORMALBULLET_WIDTH>_x){
			if(y-NORMALBULLET_HEIGHT<_y&&y+NORMALBULLET_HEIGHT>_y){
				return true;
			}
		}
	}
	return false;
}

bool B_NormalBullet::checkcollapse(Collapsebox* box, int _x, int _y){
	if(usable){
		if(box->left+_x<x-NORMALBULLET_WIDTH){
			if(box->right+_x>x-NORMALBULLET_WIDTH){
				if(box->up+_y<y-NORMALBULLET_HEIGHT){
					if(box->down+_y>y-NORMALBULLET_HEIGHT){
						return true;
					}
				}
				else{
					if(y+NORMALBULLET_HEIGHT>box->up+_y){
						return true;
					}
				}
			}
		}
		else{
			if(x+NORMALBULLET_WIDTH>box->left+_x){
				if(box->up+_y<y-NORMALBULLET_HEIGHT){
					if(box->down+_y>y-NORMALBULLET_HEIGHT){
						return true;
					}
				}
				else{
					if(y+NORMALBULLET_HEIGHT>box->up+_y){
						return true;
					}
				}
			}
		}
	}
	return false;
}

void B_NormalBullet::setcollapse(){
	usable=false;
}

int B_NormalBullet::getdmg(){
	if(usable){
		return dmg;
	}
	else return 0;
}
