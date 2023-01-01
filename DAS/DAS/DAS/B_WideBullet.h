#pragma once
#include "bullet.h"
#include "enumstructs.h"

#define WIDEBULLET_WIDTH 32
#define WIDEBULLET_HEIGHT 30

class B_WideBullet :
	public Bullet
{
public:
	B_WideBullet(float _x, float _y, float _vx, float _vy, int _charnum, int _bulnum, int _dmg);
	~B_WideBullet(void);
	void update();
	bool checkcollapse(int _x, int _y);
	bool checkcollapse(Collapsebox* box, int _x, int _y);
	void setcollapse();
	int getdmg();
};

