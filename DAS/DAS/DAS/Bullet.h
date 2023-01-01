#pragma once
#include "enumstructs.h"

class Bullet
{
protected:
	float x, y, vx, vy, ax, ay;
	int charnum, bulnum;
	int dmg;
	int angle;
	bool flag;
	bool usable;
public:
	Bullet(float _x, float _y, float _vx, float _vy, int _charnum, int _bulnum, int _dmg);
	virtual ~Bullet(void);
	virtual void update(){;}
	virtual bool checkcollapse(int _x, int _y){return false;}
	virtual bool checkcollapse(Collapsebox* box, int _x, int _y){return false;}
	virtual void setcollapse(){;}
	virtual int getdmg(){return 0;}
	bool getusable(){return usable;}
	void setusable(bool _usable){usable=_usable;}
	int getbulnum(){return bulnum;}
	int getcharnum(){return charnum;}
	int getx(){return (int)x;}
	int gety(){return (int)y;}
};

