#pragma once
#include <d3dx9.h>
class Image
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	float width, height;
	int iwidth, iheight;
	bool inversed;
public:
	Image(LPDIRECT3DDEVICE9 dev, wchar_t* name, DWORD colorkey);
	~Image(void);
	void setinverse(bool inverse);
	void draw(float x, float y, int color, bool center);
	void draw(float x, float y, float rot, int color, bool center);
	void draw(float x, float y, float rot, float scax, float scay, int color, bool center);
	void drawcoordinate(float x, float y, int color, bool center, D3DXMATRIX* mat);
	void drawcoordinaterev(float x, float y, int color, bool center, D3DXMATRIX* mat);
};

