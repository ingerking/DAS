#include "Game.h"


Game::Game(LPDIRECT3DDEVICE9 _dev)
{
	d3d_dev=_dev;
	playmode=PM_TOP;
	key1=0;
	key2=0;
	pkey1=0;
	pkey2=0;
	topselect=0;
	clientc=NULL;
	font=NULL;

	init();
}


Game::~Game(void)
{
	Image* image;
	Sound* sound;
	Character* chara;
	for(int i=0;i<sysimglist.size();i++){
		image=sysimglist[i];
		if(image!=NULL)
			delete image;
	}
	sysimglist.clear();
	for(int i=0;i<dielist.size();i++){
		image=dielist[i];
		if(image!=NULL)
			delete image;
	}
	dielist.clear();
	for(int i=0;i<charlist.size();i++){
		chara=charlist[i];
		if(chara!=NULL)
			delete chara;
	}
	charlist.clear();
	for(int i=0;i<soundlist.size();i++){
		sound=soundlist[i];
		if(sound!=NULL)
			delete sound;
	}
	soundlist.clear();

	if(clientc)
		delete clientc;
	if(font)
		delete font;
}

void Game::init(){
	Image* image;
	Character* character;
	Sound* sound;
	sysimglist.push_back(NULL);

	aud_dev=OpenDevice();
	
	image=new Image(d3d_dev, L"data\\res\\die00.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die01.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die02.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die03.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die04.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die05.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die06.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die07.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die08.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die09.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die10.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die11.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die12.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die13.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die14.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die15.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die16.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die17.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die18.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die19.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die20.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die21.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die22.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die23.png", 0);
	dielist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\die24.png", 0);
	dielist.push_back(image);

	image=new Image(d3d_dev, L"data\\res\\01.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\02.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\03.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\04.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\05.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\06.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\07.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\08.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\09.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\10.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\11.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\12.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\13.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\14.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\15.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\16.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\17.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\18.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\19.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\20.png", 0);
	sysimglist.push_back(image);
	image=new Image(d3d_dev, L"data\\res\\21.png", 0);
	sysimglist.push_back(image);
	
	character=new C_Sakuya(d3d_dev, aud_dev, L"Sakuya", &dielist);
	charlist.push_back(character);
	character=new C_Zero(d3d_dev, aud_dev, L"Zero", &dielist);
	charlist.push_back(character);
	character=new C_Marion(d3d_dev, aud_dev, L"Marion", &dielist);
	charlist.push_back(character);

	font=new Font(d3d_dev, 8);

	
	sound=new Sound(aud_dev, "data\\res\\00.wav", 0.5f);
	soundlist.push_back(sound);
	sound=new Sound(aud_dev, "data\\res\\01.wav", 0.5f);
	soundlist.push_back(sound);
	sound=new Sound(aud_dev, "data\\res\\02.wav", 0.5f);
	soundlist.push_back(sound);


	clientc=new Clientc(&charlist, aud_dev, font);

	onep;
	onepinv;
	twop;
	twopinv;
}

bool Game::gameloop(bool flag){
	pkey1=key1;
	pkey2=key2;
	key1=0;
	key2=0;
	if(flag){
		if(GetAsyncKeyState('F')&0x8000){
			key1=key1|KEY_LEFT;
		}
		if(GetAsyncKeyState('H')&0x8000){
			key1=key1|KEY_RIGHT;
		}
		if(GetAsyncKeyState('G')&0x8000){
			key1=key1|KEY_DOWN;
		}
		if(GetAsyncKeyState('T')&0x8000){
			key1=key1|KEY_UP;
		}
		if(GetAsyncKeyState('Z')&0x8000){
			key1=key1|KEY_Z;
		}
		if(GetAsyncKeyState('X')&0x8000){
			key1=key1|KEY_X;
		}
		if(GetAsyncKeyState('C')&0x8000){
			key1=key1|KEY_C;
		}
		if(GetAsyncKeyState('A')&0x8000){
			key1=key1|KEY_A;
		}
		if(GetAsyncKeyState(VK_LEFT)&0x8000){
			key2=key2|KEY_LEFT;
		}
		if(GetAsyncKeyState(VK_RIGHT)&0x8000){
			key2=key2|KEY_RIGHT;
		}
		if(GetAsyncKeyState(VK_DOWN)&0x8000){
			key2=key2|KEY_DOWN;
		}
		if(GetAsyncKeyState(VK_UP)&0x8000){
			key2=key2|KEY_UP;
		}
		if(GetAsyncKeyState(VK_OEM_COMMA)&0x8000){
			key2=key2|KEY_Z;
		}
		if(GetAsyncKeyState(VK_OEM_PERIOD)&0x8000){
			key2=key2|KEY_X;
		}
		if(GetAsyncKeyState(VK_OEM_2)&0x8000){
			key2=key2|KEY_C;
		}
		if(GetAsyncKeyState('K')&0x8000){
			key2=key2|KEY_A;
		}
	}

	switch(playmode){
	case PM_TOP:
		gamelooptop();
		break;
	case PM_OPTION:
		gameloopoption();
		break;
	case PM_PLAY:
		gameloopplay();
		break;
	case PM_QUIT:
		return true;
	default:
		break;
	}

	return false;
}

void Game::gamelooptop(){
	int key=key1|key2;
	int pkey=pkey1|pkey2;
	int ckey=(~pkey)&key;
	
	if(ckey&KEY_Z){
		switch(topselect){
		case 0:
			playmode=PM_PLAY;
			soundlist.at(1)->play(true, false);
			clientc->setgamemode(GM_PVP);
			clientc->setgamestatus(GS_SELECT);
			clientc->init(&sysimglist, &soundlist);
			break;/*
		case 1:
			playmode=PM_PLAY;
			soundlist.at(1)->play(true, false);
			clientc->setgamemode(GM_NETWORK);
			clientc->init(&sysimglist, &soundlist);
			break;
		case 2:
			playmode=PM_PLAY;
			soundlist.at(1)->play(true, false);
			clientc->setgamemode(GM_REPLAY);
			clientc->init(&sysimglist, &soundlist);
			break;
		case 3:
			playmode=PM_OPTION;
			soundlist.at(1)->play(true, false);
			break;*/
		case 4:
			playmode=PM_QUIT;
			soundlist.at(2)->play(true, false);
			break;
		}
	}
	else if(ckey&KEY_X){
		if(topselect==4){
			playmode=PM_QUIT;
			soundlist.at(2)->play(true, false);
		}
		else{
			topselect=4;
			soundlist.at(2)->play(true, false);
		}
	}
	else if(ckey&KEY_DOWN){
		if(topselect!=4){
			topselect++;
			soundlist.at(0)->play(true, false);
		}
	}
	else if(ckey&KEY_UP){
		if(topselect!=0){
			topselect--;
			soundlist.at(0)->play(true, false);
		}
	}
}

void Game::gameloopplay(){
	if(clientc->clientloop(key1, pkey1, key2, pkey2)){
		playmode=PM_TOP;
		clientc->unload();
	}
}

void Game::gameloopoption(){;}

void Game::update(){

}

void Game::draw(){
	d3d_dev->Clear( 0, NULL, D3DCLEAR_TARGET, 0xFF000000, 1.0f, 0 );
	d3d_dev->BeginScene();

	switch(playmode){
	case PM_TOP:
		drawtop();
		break;
	case PM_OPTION:
		dreawoption();
		break;
	case PM_PLAY:
		drawplay();
		break;
	default:
		break;
	}

	d3d_dev->EndScene();
	d3d_dev->Present(NULL, NULL, NULL, NULL);
}

void Game::drawtop(){
	int ileft[5]={440,480,480,500,490};
	int iheight=200;
	sysimglist[1]->draw(15, 10, 0xBFFFFFFF, false);
	for(int i=0;i<5;i++){
		sysimglist[i+2]->draw(ileft[i], iheight, i==topselect?(0xEFFFFFFF):(0x7FFFFFFF), false);
		iheight+=70;
	}
}

void Game::drawplay(){
	clientc->draw();
}

void Game::dreawoption(){
	;
}
