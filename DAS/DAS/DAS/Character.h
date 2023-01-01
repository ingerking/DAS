#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <d3dx9.h>
#include <audiere.h>

#include "Image.h"
#include "Sound.h"
#include "Bullet.h"
#include "Defender.h"

#define NUM_SAKUYA 0
#define NUM_ZERO 1
#define NUM_MARION 2

using namespace std;
using namespace audiere;
class Character
{
protected:
	LPDIRECT3DDEVICE9 dev;
	AudioDevicePtr aud_dev;
	vector<Image*> imglist;
	vector<Sound*> sndlist;
	vector<Image*> sysimglist;
	vector<Image*>* dielist;
	Image* body;
	Image* face;
	int charnum;
	int maxstock[4];
	int delay[4];
	int pdelay[4];
	int behaviornum[4];
	int behaviordelay[4];
	int boxwidth, boxheight;
	int vx, vy;
	int hp;
	wchar_t name[16];
	bool loaded;
public:
	Character(LPDIRECT3DDEVICE9 _dev, AudioDevicePtr _aud_dev, wchar_t* _name, vector<Image*>* _dielist);
	int getcharnum(){return charnum;}
	Image* getbody(){return body;}
	Image* getface(){return face;}
	vector<Image*>* getimglist(){return &imglist;}
	vector<Sound*>* getsndlist(){return &sndlist;}
	vector<Image*>* getsysimglist(){return &sysimglist;}
	vector<Image*>* getdielist(){return dielist;}
	int getvx(){return vx;}
	int getvy(){return vy;}
	int getmaxstock(int i){return maxstock[i];}
	int getdelay(int i){return delay[i];}
	int getpdelay(int i){return pdelay[i];}
	int getbehaviornum(int i){return behaviornum[i];}
	int getbehaviordelay(int i){return behaviordelay[i];}
	int gethp(){return hp;}
	virtual ~Character(void){;}
	virtual void behavior1(list<Bullet*>* bulletlist, int x, int y, bool flag){;}
	virtual void behavior2(list<Bullet*>* bulletlist, int x, int y, bool flag){;}
	virtual void behavior3(list<Bullet*>* bulletlist, int x, int y, bool flag){;}
	virtual void behavior4(list<Defender*>* defenderlist, int x, int y, int* inftime, int* worldtime, bool flag){;}
	virtual void loadimage(){;}
	void hit(){;}
	void die(){;}
	void unloadimage();
	virtual void loadsound(){;}
	void unloadsound();
	void inverse(bool flag);
};

