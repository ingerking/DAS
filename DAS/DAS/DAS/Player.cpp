#include "Player.h"


Player::Player(wstring _id, int _idnum)
{
	id=_id;
	idnum=_idnum;
	ready=false;
	x=0;
	y=0;
}


Player::~Player(void)
{
	clear();
}

void Player::init(){
	stock[0]=0;
	stock[1]=0;
	stock[2]=0;
	stock[3]=1;
	invtime=0;
	worldtime=0;
	freezetime=0;
	slowtime=0;
	bulletlocktime=0;
	die=false;
	dieend=false;
	diecount=0;
	for(int i=0;i<4;i++){
		delay[i]=1;
		pdelay[i]=0;
		behaviornum[i]=0;
		behaviordelay[i]=0;
	}
	x=MAP_WIDTH/2;
	if(isteam1){
		y=400;
	}
	else
		y=50;
	hp=getcharacter()->gethp();
}

void Player::clear(){
	Bullet* bullet;
	Defender* defender;
	ready=false;

	for(list<Bullet*>::iterator iter=bulletlist.begin();iter!=bulletlist.end();iter++){
		bullet=*iter;
		delete bullet;
	}
	for(list<Bullet*>::iterator iter=landbulletlist.begin();iter!=landbulletlist.end();iter++){
		bullet=*iter;
		delete bullet;
	}
	for(list<Defender*>::iterator diter=defenderlist.begin();diter!=defenderlist.end();diter++){
		defender=*diter;
		delete defender;
	}
	bulletlist.clear();
	landbulletlist.clear();
	defenderlist.clear();
}

int Player::update(int key, int mapworldtime){
	Bullet* bullet;
	Defender* defender;
	list<Bullet*>::iterator iter=bulletlist.begin();
	list<Defender*>::iterator diter=defenderlist.begin();
	int vx, vy;
	int ret=0;
	if(mapworldtime==0){
		while(iter!=bulletlist.end()){
			bullet=*iter;
			bullet->update();
			if(!bullet->getusable()){
				iter=bulletlist.erase(iter);
				delete bullet;
			}
			else
				iter++;
		}
		iter=landbulletlist.begin();
		while(iter!=landbulletlist.end()){
			bullet=*iter;
			bullet->update();
			if(!bullet->getusable()){
				iter=landbulletlist.erase(iter);
				delete bullet;
			}
			else
				iter++;
		}
		while(diter!=defenderlist.end()){
			defender=*diter;
			defender->update();
			if(!defender->getusable()){
				diter=defenderlist.erase(diter);
				delete defender;
			}
			else
				diter++;
		}
	}

	if(worldtime!=0){
		worldtime--;
	}
	else{
		if(invtime!=0){
			invtime--;
		}
		for(int i=0;i<4;i++){
			if(delay[i]==0){
				stock[i]++;
				delay[i]=chara->getdelay(i);
			}
			else if(delay[i]>0){
				if(stock[i]!=chara->getmaxstock(i))
					delay[i]--;
			}
			if(!die){
				if(pdelay[i]==0){
					if(behaviornum[i]!=0){
						if(behaviordelay[i]==0){
							behaviornum[i]--;
							behaviordelay[i]=chara->getbehaviordelay(i);
							switch(i){
							case 0:
								chara->behavior1(&bulletlist, x, y, isteam1);
								break;
							case 1:
								chara->behavior2(&bulletlist, x, y, isteam1);
								break;
							case 2:
								if(chara->getcharnum()==NUM_ZERO)
									chara->behavior3(&landbulletlist, x, y, isteam1);
								else
									chara->behavior3(&bulletlist, x, y, isteam1);
								break;
							case 3:
								chara->behavior4(&defenderlist, x, y, &invtime, &ret, isteam1);
								break;
							default:
								break;
							}
						}
					}
				}
			}
			if(behaviordelay[i]>0)
				behaviordelay[i]--;
			if(pdelay[i]>0)
				pdelay[i]--;
		}


		vx=chara->getvx();
		vy=chara->getvy();
		if(slowtime!=0){
			slowtime--;
			vx/=2;
			vy/=2;
		}
		if(!die){
			if(freezetime!=0){
				freezetime--;
			}
			else{
				if(isteam1){
					if(key&KEY_LEFT){
						x-=vx;
						if(x<0)
							x=0;
					}
					else if(key&KEY_RIGHT){
						x+=vx;
						if(x>MAP_WIDTH){
							x=MAP_WIDTH;
						}
					}
					if(key&KEY_UP){
						y-=vy;
						if(y<250)
							y=250;
					}
					else if(key&KEY_DOWN){
						y+=vy;
						if(y>450)
							y=450;
					}
				}
				else{
					if(key&KEY_LEFT){
						x+=vx;
						if(x>MAP_WIDTH){
							x=MAP_WIDTH;
						}
					}
					else if(key&KEY_RIGHT){
						x-=vx;
						if(x<0)
							x=0;
					}
					if(key&KEY_UP){
						y+=vy;
						if(y>200)
							y=200;
					}
					else if(key&KEY_DOWN){
						y-=vy;
						if(y<0)
							y=0;
					}
				}
			}
		}

		if(bulletlocktime==0){
			if(key&KEY_Z){
				behavior1();
			}
			if(key&KEY_X){
				behavior2();
			}
			if(key&KEY_C){
				behavior3();
			}
			if(key&KEY_A){
				behavior4();
			}
		}
		else{
			bulletlocktime--;
		}
	}
	return ret;
}

void Player::behavior1(){
	if(stock[0]!=0){
		stock[0]--;
		pdelay[0]=chara->getpdelay(0);
		behaviornum[0]=chara->getbehaviornum(0);
	}
}

void Player::behavior2(){
	if(stock[1]!=0){
		stock[1]--;
		pdelay[1]=chara->getpdelay(1);
		behaviornum[1]=chara->getbehaviornum(1);
	}
}

void Player::behavior3(){
	if(stock[2]!=0){
		stock[2]--;
		pdelay[2]=chara->getpdelay(2);
		behaviornum[2]=chara->getbehaviornum(2);
	}
}

void Player::behavior4(){
	if(stock[3]!=0){
		stock[3]--;
		delay[3]=chara->getdelay(3);
		pdelay[3]=chara->getpdelay(3);
		behaviornum[3]=chara->getbehaviornum(3);
		if(chara->getcharnum()==NUM_SAKUYA){
			chara->getsndlist()->at(3)->play(true, false);
		}
	}
}

void Player::drawbody(D3DXMATRIX* mat){
	if(die){
		if(diecount<chara->getdielist()->size()*4){
			if(isteam1)
				chara->getdielist()->at(diecount/4)->drawcoordinate(x, y, 0xFFFFFFFF,true,mat);
			else
				chara->getdielist()->at(diecount/4)->drawcoordinaterev(x, y, 0xFFFFFFFF,true,mat);
		}
		if(!dieend){
			diecount++;
			if(diecount>=500){
				dieend=true;
			}
		}
	}
	else{
		if(worldtime==0&&chara->getcharnum()==NUM_SAKUYA){
			if(isteam1)
				chara->getsysimglist()->at(0)->drawcoordinate(x, y, 0xFFFFFFFF,true,mat);
			else
				chara->getsysimglist()->at(0)->drawcoordinaterev(x, y, 0xFFFFFFFF,true,mat);
		}
		else{
			if(isteam1)
				chara->getbody()->drawcoordinate(x, y, 0xFFFFFFFF,true,mat);
			else
				chara->getbody()->drawcoordinaterev(x, y, 0xFFFFFFFF,true,mat);
		}
	}
}

void Player::drawbullet(D3DXMATRIX* mat, vector<Character*>* charlist){
	Bullet* bullet;
	int charnum, bulnum;
	for(list<Bullet*>::iterator iter=bulletlist.begin();iter!=bulletlist.end();iter++){
		bullet=*iter;
		charnum=bullet->getcharnum();
		bulnum=bullet->getbulnum();
		if(bulnum<0) continue;
		if(isteam1)
			charlist->at(charnum)->getimglist()->at(bulnum)->drawcoordinate(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true, mat);
		else
			charlist->at(charnum)->getimglist()->at(bulnum)->drawcoordinaterev(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true, mat);
	}
}

void Player::drawlandbullet(D3DXMATRIX* mat, vector<Character*>* charlist){
	Bullet* bullet;
	int charnum, bulnum;
	for(list<Bullet*>::iterator iter=landbulletlist.begin();iter!=landbulletlist.end();iter++){
		bullet=*iter;
		charnum=bullet->getcharnum();
		bulnum=bullet->getbulnum();
		if(bulnum<0) continue;
		if(isteam1)
			charlist->at(charnum)->getimglist()->at(bulnum)->drawcoordinate(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true, mat);
		else
			charlist->at(charnum)->getimglist()->at(bulnum)->drawcoordinaterev(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true, mat);
	}
}

void Player::drawshield(D3DXMATRIX* mat, vector<Character*>* charlist){
	Defender* defender;
	int charnum, bulnum;
	for(list<Defender*>::iterator iter=defenderlist.begin();iter!=defenderlist.end();iter++){
		defender=*iter;
		charnum=defender->getcharnum();
		bulnum=defender->getdefnum();
		if(bulnum<0) continue;
		if(isteam1)
			charlist->at(charnum)->getimglist()->at(bulnum)->drawcoordinate(defender->getx(), defender->gety(), 0xFFFFFFFF, true, mat);
		else
			charlist->at(charnum)->getimglist()->at(bulnum)->drawcoordinaterev(defender->getx(), defender->gety(), 0xFFFFFFFF, true, mat);
	}
}

void Player::collapsebullet(Bullet* bullet){
	int dmg;
	if(!die){
		if(bullet->checkcollapse(x, y)){
			dmg=bullet->getdmg();
			bullet->setcollapse();
			if(dmg!=0){
				hp-=dmg;
				if(hp<=0){
					chara->die();
					die=true;
				}
				else{
					chara->hit();
				}
			}
		}
	}
}

void Player::collapseshield(Defender* defender){
	Bullet* bullet;
	for(list<Bullet*>::iterator iter=bulletlist.begin();iter!=bulletlist.end();iter++){
		bullet=*iter;
		defender->collapse(bullet);
	}
	for(list<Bullet*>::iterator iter=landbulletlist.begin();iter!=landbulletlist.end();iter++){
		bullet=*iter;
		defender->collapse(bullet);
	}
}

void Player::collapse(Player* player){
	Bullet* bullet;
	if(player->getworldtime()==0){
		for(list<Bullet*>::iterator iter=bulletlist.begin();iter!=bulletlist.end();iter++){
			bullet=*iter;
			player->collapsebullet(bullet);
		}
		for(list<Bullet*>::iterator iter=player->getbulletlist()->begin();iter!=player->getbulletlist()->end();iter++){
			bullet=*iter;
			collapsebullet(bullet);
		}

		for(list<Bullet*>::iterator iter=landbulletlist.begin();iter!=landbulletlist.end();iter++){
			bullet=*iter;
			player->collapsebullet(bullet);
		}
		for(list<Bullet*>::iterator iter=player->getlandbulletlist()->begin();iter!=player->getlandbulletlist()->end();iter++){
			bullet=*iter;
			collapsebullet(bullet);
		}
	}
}

void Player::collapsedefender(Player* player){
	Defender* defender;
	for(list<Defender*>::iterator iter=player->getdefenderlist()->begin();iter!=player->getdefenderlist()->end();iter++){
		defender=*iter;
		collapseshield(defender);
	}
}