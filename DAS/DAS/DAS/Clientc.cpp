#include "Clientc.h"


Clientc::Clientc(vector<Character*>* _charlist, AudioDevicePtr _aud_dev, Font* _font)
{
	charlist=_charlist;
	font=_font;
	D3DXMatrixIdentity(&team1mat);
	D3DXMatrixIdentity(&team2mat);
	aud_dev=_aud_dev;
	bgm=new Sound(aud_dev, "data\\res\\play.mp3", 0.5f);
}


Clientc::~Clientc(void)
{
	unload();
	delete bgm;
}

void Clientc::setgamemode(GAMEMODE _gamemode){
	gamemode=_gamemode;
}

void Clientc::setgamestatus(GAMESTATUS _gamestatus){
	gamestatus=_gamestatus;
}

void Clientc::newplayer(wstring id, int idnum){
	Player* player=new Player(id, idnum);
	playerlist.push_back(player);
}

void Clientc::setteam(int idnum, int teamnum){
	Player* player;
	list<Player*>::iterator iter;
	for(iter=playerlist.begin();iter!=playerlist.end();iter++){
		player=(*iter);
		if(player->getidnum()==idnum){
			player->setteam(teamnum==1);
			break;
		}
	}
	if(teamnum==1){
		team1.push_back(player);
		for(iter=team2.begin();iter!=team2.end();iter++){
			player=(*iter);
			if(player->getidnum()==idnum){
				team2.erase(iter);
				break;
			}
		}
	}
	else{
		team2.push_back(player);
		for(iter=team1.begin();iter!=team1.end();iter++){
			player=(*iter);
			if(player->getidnum()==idnum){
				team1.erase(iter);
				break;
			}
		}
	}
}

void Clientc::charselect(int idnum, int charnum){
	Player* player;
	for(list<Player*>::iterator iter=playerlist.begin();iter!=playerlist.end();iter++){
		player=(*iter);
		if(player->getidnum()==idnum){
			player->setcharacter(charlist->at(charnum));
			break;
		}
	}
}

void Clientc::setready(int idnum, bool ready){
	Player* player;
	for(list<Player*>::iterator iter=playerlist.begin();iter!=playerlist.end();iter++){
		player=(*iter);
		if(player->getidnum()==idnum){
			player->setready(ready);
			break;
		}
	}
}

void Clientc::init(vector<Image*>* _imglist, vector<Sound*>* _soundlist){
	imagelist=_imglist;
	soundlist=_soundlist;
	switch(gamemode){
	case GM_PVP:
		newplayer(L"Player1", 0);
		newplayer(L"Player2", 1);
		setteam(0, 1);
		setteam(1, 2);
		charselect(0, 0);
		charselect(1, charlist->size()-1);
		D3DXMatrixScaling(&team2mat, -1.0, -1.0, 1.0);
		D3DXMatrixTranslation(&team1mat, PVP_MAP_RIGHT, PVP_MAP_DOWN, 0.0);
		D3DXMatrixMultiply(&team2mat, &team2mat, &team1mat);
		D3DXMatrixTranslation(&team1mat, PVP_MAP_LEFT, PVP_MAP_UP, 0.0);
		break;
	case GM_NETWORK:

		break;
	case GM_REPLAY:

		break;
	default:
		break;
	}
}

void Clientc::unload(){
	Player* player;
	for(list<Player*>::iterator iter=playerlist.begin();iter!=playerlist.end();iter++){
		player=(*iter);
		delete player;
	}
	team1.clear();
	team2.clear();
	playerlist.clear();
	D3DXMatrixIdentity(&team1mat);
	D3DXMatrixIdentity(&team2mat);
}

bool Clientc::clientloop(int key1, int pkey1, int key2, int pkey2){
	switch(gamemode){
	case GM_PVP:
		return clientlooppvp(key1, pkey1, key2, pkey2);
	case GM_NETWORK:
		return clientloopnetwork(key1, pkey1, key2, pkey2);
	case GM_REPLAY:
		return clientloopreplay(key1, pkey1, key2, pkey2);
	default:
		return true;
	}
}

bool Clientc::clientlooppvp(int key1, int pkey1, int key2, int pkey2){
	int ckey1, ckey2;
	int tkey1, tkey2;
	switch(gamestatus){
	case GS_SELECT:
		ckey1=(~pkey1)&key1;
		ckey2=(~pkey2)&key2;
		return clientlooppvpselect(ckey1, ckey2);
	case GS_LOADING:
		return clientlooppvploading(0,0);
		break;
	case GS_READY:
		return clientlooppvpready(0,0);
		break;
	case GS_PLAYING:
		tkey1=(~pkey1)&key1&0xF0;
		tkey2=pkey1&0x0F;
		ckey1=tkey1|tkey2;
		tkey1=(~pkey2)&key2&0xF0;
		tkey2=pkey2&0x0F;
		ckey2=tkey1|tkey2;
		return clientlooppvpplaying(ckey1, ckey2);
		break;
	default:
		return true;
	}
	return false;
}

bool Clientc::clientloopnetwork(int key1, int pkey1, int key2, int pkey2){
	return false;
}

bool Clientc::clientloopreplay(int key1, int pkey1, int key2, int pkey2){
	return false;
}

bool Clientc::clientlooppvpselect(int ckey1, int ckey2){
	Player* player1, *player2;
	int num;
	bool ret=false;
	list<Player*>::iterator iter=playerlist.begin();
	player1=(*iter);

	if(player1->getready()){
		if(ckey1&KEY_X){
			setready(0, false);
			soundlist->at(2)->play(true, false);
		}
	}
	else{
		num=player1->getcharacter()->getcharnum();
		if(ckey1&KEY_RIGHT){
			num++;
			if(num!=charlist->size()){
				charselect(0, num);
				soundlist->at(0)->play(true, false);
			}
		}
		else if(ckey1&KEY_LEFT){
			if(num!=0){
				charselect(0, num-1);
				soundlist->at(0)->play(true, false);
			}
		}
		else if(ckey1&KEY_Z){
			setready(0, true);
			soundlist->at(1)->play(true, false);
		}
		else if(ckey1&KEY_X){
			ret=true;
			soundlist->at(2)->play(true, false);
		}
	}
	iter++;
	player2=(*iter);

	if(player2->getready()){
		if(ckey2&KEY_X){
			setready(1, false);
			soundlist->at(2)->play(true, false);
		}
	}
	else{
		num=player2->getcharacter()->getcharnum();
		if(ckey2&KEY_RIGHT){
			num++;
			if(num!=charlist->size()){
				charselect(1, num);
				soundlist->at(0)->play(true, false);
			}
		}
		else if(ckey2&KEY_LEFT){
			if(num!=0){
				charselect(1, num-1);
				soundlist->at(0)->play(true, false);
			}
		}
		else if(ckey2&KEY_Z){
			setready(1, true);
			soundlist->at(1)->play(true, false);
		}
		else if(ckey2&KEY_X){
			ret=true;
			soundlist->at(2)->play(true, false);
		}
	}

	if(!ret){
		if(player1->getready()&&player2->getready()){
			gamestatus=GS_LOADING;
		}
	}
	return ret;
}

bool Clientc::clientlooppvploading(int ckey1, int ckey2){
	Player* player;
	for(list<Player*>::iterator iter=playerlist.begin();iter!=playerlist.end();iter++){
		player=(*iter);
		player->getcharacter()->loadimage();
		player->init();
	}
	worldtime=0;
	gamestatus=GS_READY;
	return false;
}

bool Clientc::clientlooppvpready(int ckey1, int ckey2){
	gamestatus=GS_PLAYING;
	bgm->play(true, true);
	return false;
}

bool Clientc::clientlooppvpplaying(int ckey1, int ckey2){
	Player* player1, *player2;
	list<Player*>::iterator iter=playerlist.begin();
	int _worldtime=worldtime;
	int wtimeret[2];

	bool team1alive=false;
	bool team2alive=false;
	
	player1=*iter;
	iter++;
	player2=*iter;
	
	if(worldtime>1){
		worldtime--;
		if(bgm->getisplaying()){
			bgm->stop();
		}
		if(worldtime==420){
			charlist->at(NUM_SAKUYA)->getsndlist()->at(4)->play(true, false);
		}
		if(worldtime==120){
			charlist->at(NUM_SAKUYA)->getsndlist()->at(5)->play(true, false);
		}
	}
	else if(worldtime==1){
		worldtime--;
		player1->getcharacter()->inverse(false);
		player2->getcharacter()->inverse(false);
		imagelist->at(8)->setinverse(false);
		bgm->play(false, true);
	}

	wtimeret[0]=player1->update(ckey1, _worldtime);
	wtimeret[1]=player2->update(ckey2, _worldtime);

	player1->collapsedefender(player2);
	player2->collapsedefender(player1);
	player1->collapse(player2);
	
	for(int i=0;i<2;i++){
		if(worldtime==0){
			if(wtimeret[i]!=0){
				worldtime=wtimeret[i];
				if(wtimeret[1]!=0){
					player1->setworldtime(worldtime);
				}
				if(wtimeret[0]!=0){
					player2->setworldtime(worldtime);
				}
				player1->getcharacter()->inverse(true);
				player2->getcharacter()->inverse(true);
				imagelist->at(8)->setinverse(true);
				break;
			}
		}
	}
	
	team1alive=!player1->getdie();
	team2alive=!player2->getdie();

	if(!team1alive||!team2alive){
		player1->getcharacter()->unloadimage();
		player2->getcharacter()->unloadimage();
		player1->clear();
		player2->clear();
		gamestatus=GS_SELECT;
		bgm->stopnreset();
	}
	return false;
}

bool Clientc::clientloopnetworkselect(int ckey){
	return false;
}

bool Clientc::clientloopnetworkloading(int ckey){
	return false;
}

bool Clientc::clientloopnetworkready(int ckey){
	return false;
}

bool Clientc::clientloopnetworkplaying(int ckey){
	return false;
}

bool Clientc::clientloopreplayselect(int ckey){
	return false;
}

bool Clientc::clientloopreplayloading(int ckey){
	return false;
}

bool Clientc::clientloopreplayready(int ckey){
	return false;
}

bool Clientc::clientloopreplayplaying(int ckey){
	return false;
}

void Clientc::draw(){
	switch(gamestatus){
	case GS_SELECT:
		drawselect();
		break;
	case GS_LOADING:
		drawloading();
		break;
	case GS_READY:
		drawready();
		break;
	case GS_PLAYING:
		drawplaying();
		break;
	default:
		break;
	}
}

void Clientc::drawselect(){
	switch(gamemode){
	case GM_PVP:
		drawselectpvp();
		break;
	case GM_NETWORK:

		break;
	case GM_REPLAY:

		break;
	default:
		break;
	}
}

void Clientc::drawloading(){
	;
}

void Clientc::drawready(){
	;
}

void Clientc::drawplaying(){
	switch(gamemode){
	case GM_PVP:
		drawplayingpvp();
		break;
	case GM_NETWORK:

		break;
	case GM_REPLAY:

		break;
	default:
		break;
	}
}


void Clientc::drawselectpvp(){
	Player* player1, *player2;
	Character* chara;
	list<Player*>::iterator iter;
	int color;
	int x=150, y=120;
	iter=team1.begin();
	player1=*iter;
	iter=team2.begin();
	player2=*iter;

	chara=player1->getcharacter();
	if(player1->getready()){
		color=0xFFC0C0C0;
	}
	else{
		color=0xFFFFFFFF;
	}
	chara->getbody()->draw(x, y, color, true);
	font->draw(player1->getid()->c_str(), x-50, y-60, x+50, y-30, color, true);
	x=650;
	y=380;

	chara=player2->getcharacter();
	if(player2->getready()){
		color=0xFFC0C0C0;
	}
	else{
		color=0xFFFFFFFF;
	}
	chara->getbody()->draw(x, y, color, true);
	font->draw(player2->getid()->c_str(), x-50, y-60, x+50, y-30, color, true);
}

void Clientc::drawselectnetwork(){/*
	
	Player* player;
	Character* chara;
	list<Player*>::iterator iter;
	int color;
	int x=150, y=120;
	for(iter=team1.begin();iter!=team1.end();iter++){
		player=(*iter);
		chara=player->getcharacter();
		if(player->getready()){
			color=0xFFC0C0C0;
		}
		else{
			color=0xFFFFFFFF;
		}
		chara->getbody()->draw(x, y, color, true);
		font->draw(player->getid()->c_str(), x-50, y-60, x+50, y-30, color, true);
		x+=100;
	}
	x=650;
	y=380;
	for(iter=team2.begin();iter!=team2.end();iter++){
		player=(*iter);
		chara=player->getcharacter();
		if(player->getready()){
			color=0xFFC0C0C0;
		}
		else{
			color=0xFFFFFFFF;
		}
		chara->getbody()->draw(x, y, color, true);
		font->draw(player->getid()->c_str(), x-50, y-60, x+50, y-30, color, true);
		x-=100;
	}*/
}

void Clientc::drawselectreplay(){
	;
}



void Clientc::drawplayingpvp(){
	Player* player1, *player2;
	list<Player*>::iterator iter;
	int xcoordinate, color;
	int px, py;
	float ysize;
	int stock;

	iter=team1.begin();
	player1=*iter;
	iter=team2.begin();
	player2=*iter;

		imagelist->at(8)->drawcoordinate(0, 0, 0xFFFFFFFF, false, &team1mat);
		imagelist->at(8)->drawcoordinate(0, 0, 0xFFFFFFFF, false, &team2mat);
			player1->drawlandbullet(&team1mat, charlist);
			player1->drawlandbullet(&team2mat, charlist);
			player2->drawlandbullet(&team1mat, charlist);
			player2->drawlandbullet(&team2mat, charlist);
			player1->drawshield(&team1mat, charlist);
			player1->drawshield(&team2mat, charlist);
			player2->drawshield(&team1mat, charlist);
			player2->drawshield(&team2mat, charlist);
			player1->drawbullet(&team1mat, charlist);
			player1->drawbullet(&team2mat, charlist);
			player2->drawbullet(&team1mat, charlist);
			player2->drawbullet(&team2mat, charlist);
			player1->drawbody(&team1mat);
			player1->drawbody(&team2mat);
			player2->drawbody(&team1mat);
			player2->drawbody(&team2mat);
		imagelist->at(7)->draw(0, 0, 0xFFFFFFFF, false);

		player1->getcharacter()->getsysimglist()->at(0)->draw(75, 35, 0xFFFFFFFF, true);
		if(!player1->getalive())
			imagelist->at(11)->draw(75, 35, 0xFFFFFFFF, true);
		for(int i=0;i<4;i++){
			xcoordinate=(74*i)+64;
			player1->getcharacter()->getsysimglist()->at(i+1)->draw(xcoordinate, 538, 0xFFFFFFFF, false);
			stock=player1->getstock(i);
			if(stock==0){
				ysize=(float)(player1->getdelay(i))/(float)(player1->getcharacter()->getdelay(i));
				imagelist->at(9)->draw(xcoordinate, 538, 0.0f, 1.0f, ysize, 0x80FFFFFF, false);
			}
			else{
				imagelist->at(stock+12)->draw(xcoordinate+37, 575, 0x80FFFFFF, false);
			}
		}
		for(int i=0;i<player1->gethp();i++){
			xcoordinate=(25*i)+110;
			if(player1->gethp()<3)
				color=0xFFE53F01;
			else if(player1->gethp()<5)
				color=0xFFEB8607;
			else if(player1->gethp()<7)
				color=0xFFC7F713;
			else
				color=0xFF1AFE1A;
			imagelist->at(10)->draw(xcoordinate, 30, color, false);
		}
		
		player2->getcharacter()->getsysimglist()->at(0)->draw(475, 35, 0xFFFFFFFF, true);
		if(!player2->getalive())
			imagelist->at(11)->draw(475, 35, 0xFFFFFFFF, true);
		for(int i=0;i<4;i++){
			xcoordinate=(74*i)+464;
			player2->getcharacter()->getsysimglist()->at(i+1)->draw(xcoordinate, 538, 0xFFFFFFFF, false);
			stock=player2->getstock(i);
			if(stock==0){
				ysize=(float)(player2->getdelay(i))/(float)(player2->getcharacter()->getdelay(i));
				imagelist->at(9)->draw(xcoordinate, 538, 0.0f, 1.0f, ysize, 0x80FFFFFF, false);
			}
			else{
				imagelist->at(stock+12)->draw(xcoordinate+37, 575, 0x80FFFFFF, false);
			}
		}
		for(int i=0;i<player2->gethp();i++){
			xcoordinate=(25*i)+510;
			if(player2->gethp()<3)
				color=0xFFE53F01;
			else if(player2->gethp()<5)
				color=0xFFEB8607;
			else if(player2->gethp()<7)
				color=0xFFC7F713;
			else
				color=0xFF1AFE1A;
			imagelist->at(10)->draw(xcoordinate, 30, color, false);
		}

		if(player1->getalive()){
			px=player1->getx();
			py=player1->gety();
			
			font->draw(L"YOU", px, py+20, px+100, py+50, 0xFFFFFF00, true);
		}

		if(player2->getalive()){
			px=player2->getx();
			py=player2->gety();
			
			font->draw(L"YOU", 700-px, 470-py, 800-px, 500-py, 0xFFFFFF00, true);
		}
}

void Clientc::drawplayingnetwork(){/*
	
	Player* player;
	list<Player*>::iterator iter;
	int xcoordinate, color;
	float ysize;
	switch(gamemode){
	case GM_PVP:
		imagelist->at(8)->drawcoordinate(0, 0, 0xFFFFFFFF, false, &team1mat);
		imagelist->at(8)->drawcoordinate(0, 0, 0xFFFFFFFF, false, &team2mat);
		for(iter=team1.begin();iter!=team1.end();iter++){
			player=*iter;
			player->drawlandbullet(&team1mat, charlist);
			player->drawlandbullet(&team2mat, charlist);
		}
		for(iter=team2.begin();iter!=team2.end();iter++){
			player=*iter;
			player->drawlandbullet(&team1mat, charlist);
			player->drawlandbullet(&team2mat, charlist);
		}
		for(iter=team1.begin();iter!=team1.end();iter++){
			player=*iter;
			player->drawshield(&team1mat, charlist);
			player->drawshield(&team2mat, charlist);
		}
		for(iter=team2.begin();iter!=team2.end();iter++){
			player=*iter;
			player->drawshield(&team1mat, charlist);
			player->drawshield(&team2mat, charlist);
		}
		for(iter=team1.begin();iter!=team1.end();iter++){
			player=*iter;
			player->drawbullet(&team1mat, charlist);
			player->drawbullet(&team2mat, charlist);
		}
		for(iter=team2.begin();iter!=team2.end();iter++){
			player=*iter;
			player->drawbullet(&team1mat, charlist);
			player->drawbullet(&team2mat, charlist);
		}
		for(iter=team1.begin();iter!=team1.end();iter++){
			player=*iter;
			player->drawbody(&team1mat);
			player->drawbody(&team2mat);
		}
		for(iter=team2.begin();iter!=team2.end();iter++){
			player=*iter;
			player->drawbody(&team1mat);
			player->drawbody(&team2mat);
		}
		imagelist->at(7)->draw(0, 0, 0xFFFFFFFF, false);

		iter=team1.begin();
		player=*iter;
		player->getcharacter()->getsysimglist()->at(0)->draw(75, 35, 0xFFFFFFFF, true);
		for(int i=0;i<4;i++){
			xcoordinate=(74*i)+64;
			player->getcharacter()->getsysimglist()->at(i+1)->draw(xcoordinate, 538, 0xFFFFFFFF, false);
			if(player->getstock(i)==0){
				ysize=(float)(player->getdelay(i))/(float)(player->getcharacter()->getdelay(i));
				imagelist->at(9)->draw(xcoordinate, 538, 0.0f, 1.0f, ysize, 0xFFFFFFFF, false);
			}
			else{
				;//스톡 숫자 표시
			}
		}
		for(int i=0;i<player->gethp();i++){
			xcoordinate=(25*i)+110;
			if(player->gethp()<3)
				color=0xFFE53F01;
			else if(player->gethp()<5)
				color=0xFFEB8607;
			else if(player->gethp()<7)
				color=0xFFC7F713;
			else
				color=0xFF1AFE1A;
			imagelist->at(10)->draw(xcoordinate, 30, color, false);
		}
		
		iter=team2.begin();
		player=*iter;
		player->getcharacter()->getsysimglist()->at(0)->draw(475, 35, 0xFFFFFFFF, true);
		for(int i=0;i<4;i++){
			xcoordinate=(74*i)+464;
			player->getcharacter()->getsysimglist()->at(i+1)->draw(xcoordinate, 538, 0xFFFFFFFF, false);
			if(player->getstock(i)==0){
				ysize=(float)(player->getdelay(i))/(float)(player->getcharacter()->getdelay(i));
				imagelist->at(9)->draw(xcoordinate, 538, 0.0f, 1.0f, ysize, 0xFFFFFFFF, false);
			}
			else{
				;//스톡 숫자 표시
			}
		}
		for(int i=0;i<player->gethp();i++){
			xcoordinate=(25*i)+510;
			if(player->gethp()<3)
				color=0xFFE53F01;
			else if(player->gethp()<5)
				color=0xFFEB8607;
			else if(player->gethp()<7)
				color=0xFFC7F713;
			else
				color=0xFF1AFE1A;
			imagelist->at(10)->draw(xcoordinate, 30, color, false);
		}
		break;
	case GM_NETWORK:

		break;
	case GM_REPLAY:

		break;
	default:
		break;
	}*/
}

void Clientc::drawplayingreplay(){

}