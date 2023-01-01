#pragma once
#include <d3dx9.h>
#include <vector>
#include <audiere.h>

#include "enumstructs.h"
#include "Image.h"
#include "Option.h"
#include "Clientc.h"
#include "Font.h"

#include "Character.h"
#include "C_Sakuya.h"
#include "C_Zero.h"
#include "C_Marion.h"

using namespace std;
using namespace audiere;
class Game
{
private:
	LPDIRECT3DDEVICE9 d3d_dev;
	AudioDevicePtr aud_dev;
	Clientc* clientc;
	vector<Character*> charlist;
	vector<Image*> sysimglist;
	vector<Image*> dielist;
	vector<Sound*> soundlist;
	PLAYMODE playmode;
	Option* option;
	Option* backoption;
	Font* font;
	int key1, key2;
	int pkey1, pkey2;
	int topselect, opselect;
	D3DXMATRIX onep, onepinv, twop, twopinv;
public:
	Game(LPDIRECT3DDEVICE9 _dev);
	~Game(void);
	void init();
	bool gameloop(bool flag);
	void gamelooptop();
	void gameloopplay();
	void gameloopoption();
	void update();
	void draw();
	void drawtop();
	void drawplay();
	void dreawoption();
};

