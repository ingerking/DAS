#pragma once
#include <d3dx9.h>

class Font
{
private:
	LPD3DXSPRITE fontsprite;
	LPD3DXFONT font;
public:
	Font(LPDIRECT3DDEVICE9 d3d_dev, float fontsize);
	~Font(void);
	void draw(const wchar_t* wcs, float left, float up, float right, float down, DWORD color, int center);
};

