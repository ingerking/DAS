#include "Character.h"


Character::Character(LPDIRECT3DDEVICE9 _dev, AudioDevicePtr _aud_dev, wchar_t* _name, vector<Image*>* _dielist)
{
	dev=_dev;
	wcscpy_s(name, _name);
	loadsound();
	loaded=false;
	aud_dev=_aud_dev;
	dielist=_dielist;
}

void Character::unloadimage(){
	Image* image;
	if(loaded){
		for(int i=0;i<imglist.size();i++){
			image=imglist[i];
			if(image)
				delete image;
		}
		imglist.clear();
		for(int i=0;i<sysimglist.size();i++){
			image=sysimglist[i];
			if(image)
				delete image;
		}
		sysimglist.clear();
		loaded=false;
	}
}

void Character::unloadsound(){
	Sound* sound;
	for(int i=0;i<sndlist.size();i++){
		sound=sndlist[i];
		delete sound;
	}
	sndlist.clear();
}

void Character::inverse(bool flag){
	for(int i=0;i<imglist.size();i++){
		imglist[i]->setinverse(flag);
	}
	body->setinverse(flag);
}