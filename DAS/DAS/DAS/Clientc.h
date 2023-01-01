#pragma once
#include <vector>
#include <list>
#include <audiere.h>

#include "Player.h"
#include "Character.h"
#include "Font.h"
#include "Image.h"
#include "Sound.h"

using namespace std;
using namespace audiere;
class Clientc
{
private:
	list<Player*> playerlist;
	list<Player*> team1;
	list<Player*> team2;
	vector<Character*>* charlist;
	vector<Image*>* imagelist;
	vector<Sound*>* soundlist;
	Font* font;
	Sound* bgm;
	AudioDevicePtr aud_dev;

	GAMEMODE gamemode;
	GAMESTATUS gamestatus;
	D3DXMATRIX team1mat;
	D3DXMATRIX team2mat;

	int worldtime;
public:
	Clientc(vector<Character*>* _charlist, AudioDevicePtr _aud_dev, Font* font);
	~Clientc(void);
	void setgamemode(GAMEMODE _gamemode);
	void setgamestatus(GAMESTATUS _gamestatus);
	void init(vector<Image*>* _imglist, vector<Sound*>* _soundlist);
	void unload();

	void newplayer(wstring id, int idnum);
	void setteam(int idnum, int teamnum);
	void charselect(int idnum, int charnum);
	void setready(int idnum, bool ready);

	bool clientloop(int key1, int pkey1, int key2, int pkey2);
	bool clientlooppvp(int key1, int pkey1, int key2, int pkey2);
	bool clientloopnetwork(int key1, int pkey1, int key2, int pkey2);
	bool clientloopreplay(int key1, int pkey1, int key2, int pkey2);
	
	bool clientlooppvpselect(int ckey1, int ckey2);
	bool clientlooppvploading(int ckey1, int ckey2);
	bool clientlooppvpready(int ckey1, int ckey2);
	bool clientlooppvpplaying(int ckey1, int ckey2);
	bool clientloopnetworkselect(int ckey);
	bool clientloopnetworkloading(int ckey);
	bool clientloopnetworkready(int ckey);
	bool clientloopnetworkplaying(int ckey);
	bool clientloopreplayselect(int ckey);
	bool clientloopreplayloading(int ckey);
	bool clientloopreplayready(int ckey);
	bool clientloopreplayplaying(int ckey);

	void draw();
	void drawselect();
	void drawloading();
	void drawready();
	void drawplaying();
	
	void drawselectpvp();
	void drawselectnetwork();
	void drawselectreplay();

	void drawplayingpvp();
	void drawplayingnetwork();
	void drawplayingreplay();
};

