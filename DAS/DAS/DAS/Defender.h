#pragma once

#include <list>
#include "enumstructs.h"
#include "Bullet.h"

using namespace std;

class Defender
{
protected:
	list<Defender*>* defenderlist;
	float x, y, vx, vy, ax, ay;
	int charnum, defnum;
	int angle;
	bool flag;
	bool usable;
	Collapsebox box1, box2;
public:
	Defender(float _x, float _y, float _vx, float _vy, int _charnum, int _defnum, list<Defender*>* _defenderlist);
	virtual ~Defender(void);
	virtual void update(){;}
	virtual void collapse(Bullet* bullet){;}
	bool getusable(){return usable;}
	void setusable(bool _usable){usable=_usable;}
	int getdefnum(){return defnum;}
	int getcharnum(){return charnum;}
	int getx(){return (int)x;}
	int gety(){return (int)y;}
};

