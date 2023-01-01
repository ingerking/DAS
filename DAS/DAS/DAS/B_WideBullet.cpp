#include "B_WideBullet.h"


B_WideBullet::B_WideBullet(float _x, float _y, float _vx, float _vy, int _charnum, int _bulnum, int _dmg):Bullet(_x, _y, _vx, _vy, _charnum, _bulnum, _dmg)
{
}


B_WideBullet::~B_WideBullet(void)
{
}

void B_WideBullet::update(){
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

bool B_WideBullet::checkcollapse(int _x, int _y){
	if(usable){
		if(x-WIDEBULLET_WIDTH<_x&&x+WIDEBULLET_WIDTH>_x){
			if(y-WIDEBULLET_HEIGHT<_y&&y+WIDEBULLET_HEIGHT>_y){
				return true;
			}
		}
	}
	return false;
}

bool B_WideBullet::checkcollapse(Collapsebox* box, int _x, int _y){
	if(usable){
		if(box->left+_x<x-WIDEBULLET_WIDTH){
			if(box->right+_x>x-WIDEBULLET_WIDTH){
				if(box->up+_y<y-WIDEBULLET_HEIGHT){
					if(box->down+_y>y-WIDEBULLET_HEIGHT){
						return true;
					}
				}
				else{
					if(y+WIDEBULLET_HEIGHT>box->up+_y){
						return true;
					}
				}
			}
		}
		else{
			if(x+WIDEBULLET_WIDTH>box->left+_x){
				if(box->up+_y<y-WIDEBULLET_HEIGHT){
					if(box->down+_y>y-WIDEBULLET_HEIGHT){
						return true;
					}
				}
				else{
					if(y+WIDEBULLET_HEIGHT>box->up+_y){
						return true;
					}
				}
			}
		}
	}
	return false;
}

void B_WideBullet::setcollapse(){
	usable=false;
}

int B_WideBullet::getdmg(){
	if(usable){
		return dmg;
	}
	else return 0;
}
