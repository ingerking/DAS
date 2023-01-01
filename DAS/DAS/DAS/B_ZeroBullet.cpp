#include "B_ZeroBullet.h"


B_ZeroBullet::B_ZeroBullet(float _x, float _y, float _vx, float _vy, int _charnum, int _bulnum, int _dmg):Bullet(_x, _y, _vx, _vy, _charnum, _bulnum, _dmg)
{
	countcount=0;
	countnum=0;
	flag=false;
}


B_ZeroBullet::~B_ZeroBullet(void)
{
}

void B_ZeroBullet::update(){
	if(flag){
		if(usable){
			bulnum=ZEROBULLET_ARRAY[countnum];
			if(countcount==2){
				countcount=0;
				countnum++;
			}
			if(countnum==79)
				usable=false;
		}
	}
	else{
		y+=vy;

		if(x>MAP_WIDTH)
			usable=!(x>BUL_MAP_OUT+MAP_WIDTH);
		else if(x<0)
			usable=!(x<-BUL_MAP_OUT);
		if(y>MAP_HEIGHT){
			setcollapse();
			return;
		}
		else if(y<0){
			setcollapse();
			return;
		}

		if(countcount==2){
			countcount=0;
			countnum++;
		}
		if(countnum==4){
			if(vy<0)
				vy-=ZEROBULLET_ACC;
			else vy+=ZEROBULLET_ACC;
			countnum=0;
			bulnum++;
			if(bulnum==22)
				bulnum=19;
		}
	}
	countcount++;
}

bool B_ZeroBullet::checkcollapse(int _x, int _y){
	static int bombrange=ZEROBULLET_RANGE*ZEROBULLET_RANGE;
	int xrange, yrange;
	if(usable){
		if(flag){
			if(x-ZEROBULLET_RANGE<_x&&x+ZEROBULLET_RANGE>_x){
				if(y-ZEROBULLET_RANGE<_y&&y+ZEROBULLET_RANGE>_y){
					xrange=x-_x;
					yrange=y-_y;
					if(xrange*xrange+yrange*yrange<bombrange)
						return true;
				}
			}
		}
		else{
			if(x-ZEROBULLET_WIDTH<_x&&x+ZEROBULLET_WIDTH>_x){
				if(y-ZEROBULLET_HEIGHT<_y&&y+ZEROBULLET_HEIGHT>_y){
					return true;
				}
			}
		}
	}
	return false;
}

bool B_ZeroBullet::checkcollapse(Collapsebox* box, int _x, int _y){
	if(usable){
		if(!flag){
			if(box->left+_x<x-ZEROBULLET_WIDTH){
				if(box->right+_x>x-ZEROBULLET_WIDTH){
					if(box->up+_y<y-ZEROBULLET_HEIGHT){
						if(box->down+_y>y-ZEROBULLET_HEIGHT){
							return true;
						}
					}
					else{
						if(y+ZEROBULLET_HEIGHT>box->up+_y){
							return true;
						}
					}
				}
			}
			else{
				if(x+ZEROBULLET_WIDTH>box->left+_x){
					if(box->up+_y<y-ZEROBULLET_HEIGHT){
						if(box->down+_y>y-ZEROBULLET_HEIGHT){
							return true;
						}
					}
					else{
						if(y+ZEROBULLET_HEIGHT>box->up+_y){
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void B_ZeroBullet::setcollapse(){
	if(!flag){
		dmg=1;
		flag=true;
		countnum=0;
		countcount=0;
	}
}

int B_ZeroBullet::getdmg(){
	if(usable){
		if(flag){
			if(countcount==1){
				if(bulnum==15)
					return dmg;
				else if(bulnum==4)
					return dmg;
			}
		}
		else
			return 1;
	}
	return 0;
}