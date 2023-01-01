#include "Font.h"


Font::Font(LPDIRECT3DDEVICE9 d3d_dev, float fontsize)
{
	fontsprite=NULL;
	font=NULL;

	D3DXFONT_DESC fontDesc;	//��Ʈ�� ������ ���� ����ü�� �ϴ� �����Ѵ�.

	ZeroMemory(&fontDesc, sizeof(fontDesc)); //��Ʈ�� ����ü�� �ʱ�ȭ��Ŵ
	fontDesc.Height = (int)(2.0f*fontsize); //��Ʈ�� ����(��ü�� �ʺ��� 2������ ������)
	fontDesc.Width = (int)(fontsize); //��Ʈ�� �ʺ�
	fontDesc.Weight = 700; //��Ʈ�� ���� (0(����)~ 1000(����)�� ���� ����)
	fontDesc.Italic = false; //���Ÿ�?
	fontDesc.CharSet = DEFAULT_CHARSET; //����Ʈ�� �����ϱ�
	wcscpy_s(fontDesc.FaceName, L"����"); // �۲� ��Ÿ��


	D3DXCreateFontIndirect(d3d_dev, &fontDesc, &font); //��Ʈ�� �����.
	D3DXCreateSprite(d3d_dev, &fontsprite);
}


Font::~Font(void)
{
	if(fontsprite!=NULL)
		fontsprite->Release();
	if(font!=NULL)
		font->Release();
}

void Font::draw(const wchar_t* wcs, float left, float up, float right, float down, DWORD color, int center){
	RECT rc={(LONG)(left), (LONG)(up), (LONG)(right), (LONG)(down)};
	fontsprite->Begin(D3DXSPRITE_ALPHABLEND);
	font->DrawTextW(fontsprite, wcs, wcslen(wcs), &rc, center | DT_SINGLELINE | DT_NOCLIP|DT_VCENTER, color);
	fontsprite->End();
}