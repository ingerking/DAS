#include "Image.h"


Image::Image(LPDIRECT3DDEVICE9 dev, wchar_t* name, DWORD colorkey)
{	
	D3DXIMAGE_INFO info;

	sprite=NULL;
	texture=NULL;

	D3DXCreateSprite(dev, &sprite);
	D3DXGetImageInfoFromFile(name, &info);
	D3DXCreateTextureFromFileEx(dev, name, info.Width, info.Height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, colorkey, NULL, NULL, &texture);

	iwidth=info.Width;
	iheight=info.Height;
	width=0.0f-(float)info.Width/2.0f;
	height=0.0f-(float)info.Height/2.0f;
	inversed=false;
}


Image::~Image(void)
{
	if(sprite!=NULL)
		sprite->Release();
	if(texture!=NULL)
		texture->Release();
}

void Image::setinverse(bool inverse){
	D3DLOCKED_RECT lrect;

	if(inverse!=inversed){
		inversed=inverse;
		texture->LockRect(0, &lrect, NULL, 0);
		//	texture->LockRect(0, &lrect, NULL, D3DLOCK_NOSYSLOCK);
		BYTE* pBits = (BYTE*)lrect.pBits;

		for(UINT y=0; y<iheight; ++y)
		{
			DWORD* pPixel = (DWORD*)pBits;
			pBits += lrect.Pitch;
			for(UINT x=0; x<iwidth; ++x)
			{
				DWORD a = (*pPixel)&0xff000000;
				DWORD rgb=(~(*pPixel))&0x00ffffff;

				*pPixel = a | rgb;

				pPixel++;
			}
		}
		texture->UnlockRect(0);
	}
}

void Image::draw(float x, float y, int color, bool center){
	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);
	D3DXMATRIX centermatr;
	D3DXMATRIX matr;
	D3DXMatrixTranslation(&matr, x, y, 0.0f);
	
	if(center){
		D3DXMatrixTranslation(&centermatr, width, height, 0.0f);
		D3DXMatrixMultiply(&matr, &centermatr, &matr);
	}

	sprite->SetTransform(&matr);

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, NULL, NULL, &vec, color);
	sprite->End();
}

void Image::draw(float x, float y, float rot, int color, bool center){
	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);
	D3DXMATRIX centermatr;
	D3DXMATRIX matrt;
	D3DXMATRIX matrr;
	D3DXMatrixTranslation(&matrt, x, y, 0.0f);
	D3DXMatrixRotationZ(&matrr, rot);

	if(center){
		D3DXMatrixTranslation(&centermatr, width, height, 0.0f);
		D3DXMatrixMultiply(&matrr, &centermatr, &matrr);
	}

	D3DXMatrixMultiply(&matrt, &matrr, &matrt);

	sprite->SetTransform(&matrt);
	
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, NULL, NULL, &vec, color);
	sprite->End();
}

void Image::draw(float x, float y, float rot, float scax, float scay, int color, bool center){
	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);
	D3DXMATRIX centermatr;
	D3DXMATRIX matrt;
	D3DXMATRIX matrr;
	D3DXMATRIX matrs;
	D3DXMatrixTranslation(&matrt, x, y, 0.0f);
	D3DXMatrixRotationZ(&matrr, rot);
	D3DXMatrixScaling(&matrs, scax, scay, 1.0f);

	if(center){
		D3DXMatrixTranslation(&centermatr, width, height, 0.0f);
		D3DXMatrixMultiply(&matrs, &centermatr, &matrs);
	}

	D3DXMatrixMultiply(&matrr, &matrs, &matrr);
	D3DXMatrixMultiply(&matrt, &matrr, &matrt);

	sprite->SetTransform(&matrt);
	
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, NULL, NULL, &vec, color);
	sprite->End();
}


void Image::drawcoordinate(float x, float y, int color, bool center, D3DXMATRIX* mat){
	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);
	D3DXMATRIX centermatr;
	D3DXMATRIX matr;
	D3DXMatrixTranslation(&matr, x, y, 0.0f);
	
	if(center){
		D3DXMatrixTranslation(&centermatr, width, height, 0.0f);
		D3DXMatrixMultiply(&matr, &centermatr, &matr);
	}

	D3DXMatrixMultiply(&matr, &matr, mat);

	sprite->SetTransform(&matr);

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, NULL, NULL, &vec, color);
	sprite->End();
}

void Image::drawcoordinaterev(float x, float y, int color, bool center, D3DXMATRIX* mat){
	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);
	D3DXMATRIX centermatr;
	D3DXMATRIX matr;
	D3DXMATRIX rev;
	D3DXMatrixScaling(&rev, -1.0, -1.0, 1.0);
	D3DXMatrixTranslation(&matr, x, y, 0.0f);
	
	D3DXMatrixMultiply(&matr, &rev, &matr);
	if(center){
		D3DXMatrixTranslation(&centermatr, width, height, 0.0f);
		D3DXMatrixMultiply(&matr, &centermatr, &matr);
	}
	D3DXMatrixMultiply(&matr, &matr, mat);

	sprite->SetTransform(&matr);

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, NULL, NULL, &vec, color);
	sprite->End();
}