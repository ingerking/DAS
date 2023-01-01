#include "C_Zero.h"


C_Zero::C_Zero(LPDIRECT3DDEVICE9 _dev, AudioDevicePtr _aud_dev, wchar_t* _name, vector<Image*>* _dielist):Character(_dev, _aud_dev, _name, _dielist)
{
	charnum=NUM_ZERO;
	maxstock[0]=ZERO_MAXSTOCK_1;
	maxstock[1]=ZERO_MAXSTOCK_2;
	maxstock[2]=ZERO_MAXSTOCK_3;
	maxstock[3]=ZERO_MAXSTOCK_4;
	delay[0]=ZERO_DELAY_1;
	delay[1]=ZERO_DELAY_2;
	delay[2]=ZERO_DELAY_3;
	delay[3]=ZERO_DELAY_4;
	pdelay[0]=ZERO_PDELAY_1;
	pdelay[1]=ZERO_PDELAY_2;
	pdelay[2]=ZERO_PDELAY_3;
	pdelay[3]=ZERO_PDELAY_4;
	behaviornum[0]=ZERO_BEHAVIORNUM_1;
	behaviornum[1]=ZERO_BEHAVIORNUM_2;
	behaviornum[2]=ZERO_BEHAVIORNUM_3;
	behaviornum[3]=ZERO_BEHAVIORNUM_4;
	behaviordelay[0]=ZERO_BEHAVIORDELAY_1;
	behaviordelay[1]=ZERO_BEHAVIORDELAY_2;
	behaviordelay[2]=ZERO_BEHAVIORDELAY_3;
	behaviordelay[3]=ZERO_BEHAVIORDELAY_4;
	boxwidth;
	boxheight;
	vx=ZERO_VX;
	vy=ZERO_VY;
	hp=ZERO_MAXHP;
	
	body=new Image(dev, L"data\\char\\Zero\\body.png", 0xFFFF0000);
	face=new Image(dev, L"data\\char\\Zero\\face.png", 0);

	loadsound();
}


C_Zero::~C_Zero(void)
{
	unloadimage();
	unloadsound();
	delete body;
	delete face;
}

void C_Zero::behavior1(list<Bullet*>* bulletlist, int x, int y, bool flag){
	Bullet* bullet;
	if(flag)
		bullet=new B_NormalBullet(x, y, 0.0f, -ZERO_BV, charnum, 22, 1);
	else
		bullet=new B_NormalBullet(x, y, 0.0f, ZERO_BV, charnum, 22, 1);
	bulletlist->push_back(bullet);
	sndlist[0]->play(true, false);
}

void C_Zero::behavior2(list<Bullet*>* bulletlist, int x, int y, bool flag){
	Bullet* bullet;
	if(flag)
		bullet=new B_WideBullet(x, y, 0.0f, -ZERO_BV, charnum, 23, 1);
	else
		bullet=new B_WideBullet(x, y, 0.0f, ZERO_BV, charnum, 23, 1);
	bulletlist->push_back(bullet);
	sndlist[0]->play(true, false);
}

void C_Zero::behavior3(list<Bullet*>* bulletlist, int x, int y, bool flag){
	Bullet* bullet;
	if(flag)
		bullet=new B_ZeroBullet(x, y, 0.0f, -ZEROBULLET_ACC, charnum, 19, 0);
	else
		bullet=new B_ZeroBullet(x, y, 0.0f, ZEROBULLET_ACC, charnum, 19, 0);
	bulletlist->push_back(bullet);
	sndlist[1]->play(true, false);
}

void C_Zero::behavior4(list<Defender*>* defenderlist, int x, int y, int* inftime, int* worldtime, bool flag){
	Defender* defender;
	if(flag)
		defender=new D_ZeroDefender(x, 550, 0.0f, -4.0f, charnum, 17, defenderlist);
	else
		defender=new D_ZeroDefender(x, -100, 0.0f, 4.0f, charnum, 17, defenderlist);
	defenderlist->push_back(defender);
}

void C_Zero::loadimage(){
	Image* image;
	if(!loaded){
		loaded=true;
		image=new Image(dev, L"data\\char\\Zero\\00.png", 0xFF00FFFF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\01.png", 0xFF00FFFF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\02.png", 0xFF00FFFF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\03.png", 0xFF00FFFF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\04.png", 0xFF00FFFF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\05.png", 0xFF00FFFF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\06.png", 0xFF00FFFF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\07.png", 0xFF00FFFF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\08.png", 0xFF00FFFF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\09.png", 0xFF00FFFF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\10.png", 0xFF00FFFF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\11.png", 0xFF00FFFF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\12.png", 0xFF00FFFF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\13.png", 0xFF00FFFF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\14.png", 0xFF00FFFF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\15.png", 0xFF00FFFF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\16.png", 0xFF00FFFF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\17.png", 0xFFFF00FF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\18.png", 0xFFFF00FF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\19.png", 0xFFFF00FF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\20.png", 0xFFFF00FF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\21.png", 0xFFFF00FF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\22.png", 0xFFFF00FF);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\23.png", 0xFFFF00FF);
		imglist.push_back(image);


		image=new Image(dev, L"data\\char\\Zero\\body.png", 0xFFFF0000);
		sysimglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\skill0.png", 0);
		sysimglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\skill1.png", 0);
		sysimglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\skill2.png", 0);
		sysimglist.push_back(image);
		image=new Image(dev, L"data\\char\\Zero\\skill3.png", 0);
		sysimglist.push_back(image);
	}
}

void C_Zero::loadsound(){
	Sound* sound;
	
	sound=new Sound(aud_dev, "data\\char\\Zero\\0.wav", 0.5f);
	sndlist.push_back(sound);
	sound=new Sound(aud_dev, "data\\char\\Zero\\1.wav", 0.5f);
	sndlist.push_back(sound);
}
