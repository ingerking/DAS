#include "C_Marion.h"



C_Marion::C_Marion(LPDIRECT3DDEVICE9 _dev, AudioDevicePtr _aud_dev, wchar_t* _name, vector<Image*>* _dielist):Character(_dev, _aud_dev, _name, _dielist)
{
	charnum=NUM_MARION;
	maxstock[0]=MARION_MAXSTOCK_1;
	maxstock[1]=MARION_MAXSTOCK_2;
	maxstock[2]=MARION_MAXSTOCK_3;
	maxstock[3]=MARION_MAXSTOCK_4;
	delay[0]=MARION_DELAY_1;
	delay[1]=MARION_DELAY_2;
	delay[2]=MARION_DELAY_3;
	delay[3]=MARION_DELAY_4;
	pdelay[0]=MARION_PDELAY_1;
	pdelay[1]=MARION_PDELAY_2;
	pdelay[2]=MARION_PDELAY_3;
	pdelay[3]=MARION_PDELAY_4;
	behaviornum[0]=MARION_BEHAVIORNUM_1;
	behaviornum[1]=MARION_BEHAVIORNUM_2;
	behaviornum[2]=MARION_BEHAVIORNUM_3;
	behaviornum[3]=MARION_BEHAVIORNUM_4;
	behaviordelay[0]=MARION_BEHAVIORDELAY_1;
	behaviordelay[1]=MARION_BEHAVIORDELAY_2;
	behaviordelay[2]=MARION_BEHAVIORDELAY_3;
	behaviordelay[3]=MARION_BEHAVIORDELAY_4;
	boxwidth;
	boxheight;
	vx=MARION_VX;
	vy=MARION_VY;
	hp=MARION_MAXHP;
	
	body=new Image(dev, L"data\\char\\Marion\\body.png", 0);
	face=new Image(dev, L"data\\char\\Marion\\face.png", 0);

	loadsound();
}


C_Marion::~C_Marion(void)
{
	unloadimage();
	unloadsound();
	delete body;
	delete face;
}

void C_Marion::behavior1(list<Bullet*>* bulletlist, int x, int y, bool flag){
	Bullet* bullet;
	if(flag)
		bullet=new B_NormalBullet(x, y, 0.0f, -MARION_BV, charnum, 9, 1);
	else
		bullet=new B_NormalBullet(x, y, 0.0f, MARION_BV, charnum, 9, 1);
	bulletlist->push_back(bullet);
}

void C_Marion::behavior2(list<Bullet*>* bulletlist, int x, int y, bool flag){
	Bullet* bullet;
	if(flag)
		bullet=new B_WideBullet(x, y, 0.0f, -MARION_BV, charnum, 10, 1);
	else
		bullet=new B_WideBullet(x, y, 0.0f, MARION_BV, charnum, 10, 1);
	bulletlist->push_back(bullet);
}

void C_Marion::behavior3(list<Bullet*>* bulletlist, int x, int y, bool flag){
	Bullet* bullet;
	if(flag)
		bullet=new B_WideBullet(x, y, 0.0f, -MARION_BV, charnum, 10, 1);
	else
		bullet=new B_WideBullet(x, y, 0.0f, MARION_BV, charnum, 10, 1);
	bulletlist->push_back(bullet);
}

void C_Marion::behavior4(list<Defender*>* defenderlist, int x, int y, int* inftime, int* worldtime, bool flag){
	Defender* defender;
	defender=new D_MarionDefender(0.0f, flag?1:-1, 0.0f, 0.0f, charnum, -1, defenderlist);
	defenderlist->push_back(defender);
}

void C_Marion::loadimage(){
	Image* image;
	if(!loaded){
		loaded=true;
		image=new Image(dev, L"data\\char\\Marion\\00.png", 0);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Marion\\01.png", 0);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Marion\\02.png", 0);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Marion\\03.png", 0);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Marion\\04.png", 0);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Marion\\05.png", 0);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Marion\\06.png", 0);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Marion\\07.png", 0);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Marion\\08.png", 0);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Marion\\09.png", 0);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Marion\\10.png", 0);
		imglist.push_back(image);
		
		image=new Image(dev, L"data\\char\\Marion\\body.png", 0);
		sysimglist.push_back(image);
		image=new Image(dev, L"data\\char\\Marion\\skill0.png", 0);
		sysimglist.push_back(image);
		image=new Image(dev, L"data\\char\\Marion\\skill1.png", 0);
		sysimglist.push_back(image);
		image=new Image(dev, L"data\\char\\Marion\\skill2.png", 0);
		sysimglist.push_back(image);
		image=new Image(dev, L"data\\char\\Marion\\skill3.png", 0);
		sysimglist.push_back(image);
	}
}

void C_Marion::loadsound(){
	;
}
