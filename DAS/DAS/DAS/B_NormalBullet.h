#pragma once
#include "Bullet.h"
#include "enumstructs.h"

#define NORMALBULLET_WIDTH 12
#define NORMALBULLET_HEIGHT 15
class B_NormalBullet :
	public Bullet
{
public:
	B_NormalBullet(float _x, float _y, float _vx, float _vy, int _charnum, int _bulnum, int _dmg);
	~B_NormalBullet(void);
	void update();
	bool checkcollapse(int _x, int _y);
	bool checkcollapse(Collapsebox* box, int _x, int _y);
	void setcollapse();
	int getdmg();
};

