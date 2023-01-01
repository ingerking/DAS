#pragma once
#include "bullet.h"
#include "enumstructs.h"

#define ZEROBULLET_WIDTH 24
#define ZEROBULLET_HEIGHT 30
#define ZEROBULLET_RANGE 120
#define ZEROBULLET_ACC 2

static const int ZEROBULLET_ARRAY[80]=
{
	1,6,3,8,4,9,10,11,12,
	13,14,7,15,6,3,7,16,
	6,3,7,15,6,3,7,16,
	6,3,7,15,6,3,7,16,
	6,3,7,15,6,3,7,16,
	6,3,7,15,6,3,7,16,
	6,3,7,15,6,3,7,16,
	6,3,7,15,6,3,7,16,
	6,3,7,15,6,3,7,16,
	6,3,6,1,5,0,0
};

class B_ZeroBullet :
	public Bullet
{
private:
	int countnum;
	int countcount;
	bool flag;
public:
	B_ZeroBullet(float _x, float _y, float _vx, float _vy, int _charnum, int _bulnum, int _dmg);
	~B_ZeroBullet(void);
	void update();
	bool checkcollapse(int _x, int _y);
	bool checkcollapse(Collapsebox* box, int _x, int _y);
	void setcollapse();
	int getdmg();
};

