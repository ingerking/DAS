#include "C_Sakuya.h"


C_Sakuya::C_Sakuya(LPDIRECT3DDEVICE9 _dev, AudioDevicePtr _aud_dev, wchar_t* _name, vector<Image*>* _dielist):Character(_dev, _aud_dev, _name, _dielist)
{
	charnum=NUM_SAKUYA;
	maxstock[0]=SAKUYA_MAXSTOCK_1;
	maxstock[1]=SAKUYA_MAXSTOCK_2;
	maxstock[2]=SAKUYA_MAXSTOCK_3;
	maxstock[3]=SAKUYA_MAXSTOCK_4;
	delay[0]=SAKUYA_DELAY_1;
	delay[1]=SAKUYA_DELAY_2;
	delay[2]=SAKUYA_DELAY_3;
	delay[3]=SAKUYA_DELAY_4;
	pdelay[0]=SAKUYA_PDELAY_1;
	pdelay[1]=SAKUYA_PDELAY_2;
	pdelay[2]=SAKUYA_PDELAY_3;
	pdelay[3]=SAKUYA_PDELAY_4;
	behaviornum[0]=SAKUYA_BEHAVIORNUM_1;
	behaviornum[1]=SAKUYA_BEHAVIORNUM_2;
	behaviornum[2]=SAKUYA_BEHAVIORNUM_3;
	behaviornum[3]=SAKUYA_BEHAVIORNUM_4;
	behaviordelay[0]=SAKUYA_BEHAVIORDELAY_1;
	behaviordelay[1]=SAKUYA_BEHAVIORDELAY_2;
	behaviordelay[2]=SAKUYA_BEHAVIORDELAY_3;
	behaviordelay[3]=SAKUYA_BEHAVIORDELAY_4;
	boxwidth;
	boxheight;
	vx=SAKUYA_VX;
	vy=SAKUYA_VY;
	hp=SAKUYA_MAXHP;
	
	body=new Image(dev, L"data\\char\\Sakuya\\body.png", 0);
	face=new Image(dev, L"data\\char\\Sakuya\\face.png", 0);

	loadsound();
}


C_Sakuya::~C_Sakuya(void)
{
	unloadimage();
	unloadsound();
	delete body;
	delete face;
}

void C_Sakuya::behavior1(list<Bullet*>* bulletlist, int x, int y, bool flag){
	B_NormalBullet* bullet;
	if(flag)
		bullet=new B_NormalBullet(x, y, 0.0f, -SAKUYA_BV, charnum, 0, 1);
	else
		bullet=new B_NormalBullet(x, y, 0.0f, SAKUYA_BV, charnum, 0, 1);
	bulletlist->push_back(bullet);
}

void C_Sakuya::behavior2(list<Bullet*>* bulletlist, int x, int y, bool flag){
	B_NormalBullet* bullet1, *bullet2, *bullet3;
	if(flag){
		bullet1=new B_NormalBullet(x-10, y, 0.0f, -SAKUYA_BV, charnum, 0, 1);
		bullet2=new B_NormalBullet(x, y, 0.0f, -SAKUYA_BV, charnum, 0, 1);
		bullet3=new B_NormalBullet(x+10, y, 0.0f, -SAKUYA_BV, charnum, 0, 1);
	}
	else{
		bullet1=new B_NormalBullet(x+10, y, 0.0f, SAKUYA_BV, charnum, 0, 1);
		bullet2=new B_NormalBullet(x, y, 0.0f, SAKUYA_BV, charnum, 0, 1);
		bullet3=new B_NormalBullet(x-10, y, 0.0f, SAKUYA_BV, charnum, 0, 1);
	}
	bulletlist->push_back(bullet1);
	bulletlist->push_back(bullet2);
	bulletlist->push_back(bullet3);
	sndlist[1]->play(true, false);
}

void C_Sakuya::behavior3(list<Bullet*>* bulletlist, int x, int y, bool flag){
	B_NormalBullet* bullet1, *bullet2;
	if(flag){
		bullet1=new B_NormalBullet(x-5, y, 0.0f, -SAKUYA_BV, charnum, 0, 1);
		bullet2=new B_NormalBullet(x+5, y, 0.0f, -SAKUYA_BV, charnum, 0, 1);
	}
	else{
		bullet1=new B_NormalBullet(x+5, y, 0.0f, SAKUYA_BV, charnum, 0, 1);
		bullet2=new B_NormalBullet(x-5, y, 0.0f, SAKUYA_BV, charnum, 0, 1);
	}
	bulletlist->push_back(bullet1);
	bulletlist->push_back(bullet2);
	sndlist[1]->play(true, false);
}

void C_Sakuya::behavior4(list<Defender*>* defenderlist, int x, int y, int* inftime, int* worldtime, bool flag){
	*worldtime=WORLDTIME;
	sndlist[2]->play(true, false);
}

void C_Sakuya::loadimage(){
	Image* image;
	if(!loaded){
		loaded=true;
		image=new Image(dev, L"data\\char\\Sakuya\\00.png", 0);
		imglist.push_back(image);
		image=new Image(dev, L"data\\char\\Sakuya\\body.png", 0);
		sysimglist.push_back(image);
		image=new Image(dev, L"data\\char\\Sakuya\\skill0.png", 0);
		sysimglist.push_back(image);
		image=new Image(dev, L"data\\char\\Sakuya\\skill1.png", 0);
		sysimglist.push_back(image);
		image=new Image(dev, L"data\\char\\Sakuya\\skill2.png", 0);
		sysimglist.push_back(image);
		image=new Image(dev, L"data\\char\\Sakuya\\skill3.png", 0);
		sysimglist.push_back(image);
	}
}

void C_Sakuya::loadsound(){
	Sound* sound;
	
	sound=new Sound(aud_dev, "data\\char\\Sakuya\\0.wav", 0.5f);
	sndlist.push_back(sound);
	sound=new Sound(aud_dev, "data\\char\\Sakuya\\1.wav", 0.5f);
	sndlist.push_back(sound);
	sound=new Sound(aud_dev, "data\\char\\Sakuya\\2.wav", 0.5f);
	sndlist.push_back(sound);
	sound=new Sound(aud_dev, "data\\char\\Sakuya\\3.wav", 0.5f);
	sndlist.push_back(sound);
	sound=new Sound(aud_dev, "data\\char\\Sakuya\\4.wav", 0.5f);
	sndlist.push_back(sound);
	sound=new Sound(aud_dev, "data\\char\\Sakuya\\5.wav", 0.5f);
	sndlist.push_back(sound);
}