#pragma once
#include <list>
#include "Character.h"
#include "enumstructs.h"
#include "Bullet.h"
#include "Defender.h"

using namespace std;
class Player
{
private:
	Character* chara;
	int idnum;
	wstring id;
	bool ready;

	int x, y;
	int stock[4];
	int delay[4];
	int pdelay[4];
	int behaviornum[4];
	int behaviordelay[4];
	int hp;
	int invtime;
	int worldtime;
	int freezetime;
	int slowtime;
	int bulletlocktime;
	bool isteam1;
	bool die;
	bool dieend;
	int diecount;
	STATUS status;
	list<Bullet*> bulletlist;
	list<Bullet*> landbulletlist;
	list<Defender*> defenderlist;
public:
	Player(wstring _id, int _idnum);
	~Player(void);

	wstring* getid(){return &id;}
	int getidnum(){return idnum;}
	void setcharacter(Character* _chara){chara=_chara;}
	Character* getcharacter(){return chara;}
	void setready(bool _ready){ready=_ready;}
	bool getready(){return ready;}
	bool getdie(){return dieend;}
	bool getalive(){return !die;}
	int getx(){return x;}
	int gety(){return y;}
	int getdelay(int i){return delay[i];}
	int getstock(int i){return stock[i];}
	int gethp(){return hp;}
	void setteam(bool _isteam1){isteam1=_isteam1;}
	void setinvtime(int _invtime){invtime=_invtime;}
	void setworldtime(int _worldtime){worldtime=_worldtime;}
	void setfreezetime(int _freezetime){freezetime=_freezetime;}
	void setslowtime(int _slowtime){slowtime=_slowtime;}
	void setbulletlocktime(int _bulletlocktime){bulletlocktime=_bulletlocktime;}
	int getworldtime(){return worldtime;}
	list<Bullet*>* getbulletlist(){return &bulletlist;}
	list<Bullet*>* getlandbulletlist(){return &landbulletlist;}
	list<Defender*>* getdefenderlist(){return &defenderlist;}
	
	void init();
	void clear();
	int update(int key, int worldtime);
	void behavior1();
	void behavior2();
	void behavior3();
	void behavior4();
	void drawbody(D3DXMATRIX* mat);
	void drawbullet(D3DXMATRIX* mat, vector<Character*>* charlist);
	void drawlandbullet(D3DXMATRIX* mat, vector<Character*>* charlist);
	void drawshield(D3DXMATRIX* mat, vector<Character*>* charlist);
	void collapsebullet(Bullet* bullet);
	void collapseshield(Defender* defender);
	void collapse(Player* player);
	void collapsedefender(Player* player);
};

