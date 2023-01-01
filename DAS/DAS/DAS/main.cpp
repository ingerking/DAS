#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <stdlib.h>
#include <audiere.h>
#include "enumstructs.h"
#include "Game.h"

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#pragma comment (lib, "winmm.lib")

#pragma comment (lib, "audiere.lib")



LPDIRECT3D9 d3d;
LPDIRECT3DDEVICE9 d3d_dev;

HRESULT initD3D(HWND hWnd){
	d3d=Direct3DCreate9(D3D_SDK_VERSION);	//�������̽� ����
	D3DPRESENT_PARAMETERS d3dpp;			//���� �������� ��� ����ü
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//�޸� �ʱ�ȭ
	d3dpp.Windowed=TRUE;					//â ���
	d3dpp.SwapEffect=D3DSWAPEFFECT_DISCARD;	//
	d3dpp.hDeviceWindow=hWnd;				//����
	d3dpp.BackBufferFormat=D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//����̽� ����
	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3d_dev);
	
    d3d_dev->SetRenderState( D3DRS_ZENABLE, TRUE );
    d3d_dev->SetRenderState( D3DRS_AMBIENT, 0xffffffff );

	return S_OK;
}

void cleanD3D(){
	d3d->Release();
	d3d_dev->Release();
}

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch(msg){
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		
		
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


FLOAT CalcFPS() {
	static int cnt = 0;
	static DWORD curr_time = 0, prev_time = 0, elapsed = 0;
	static float fps = 0.0f;

	prev_time = curr_time;
	curr_time = timeGetTime();
	cnt++;
	elapsed += curr_time - prev_time;

	if(elapsed >= 1000) {
		fps = cnt * 1000.0f / elapsed;
		elapsed = 0;
		cnt = 0;
	}
	return fps;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT){
	WNDCLASSEX wc={sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, hInst, NULL, LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_WINDOW+1), 
		NULL, L"DAS", NULL};
	RegisterClassEx(&wc);

	HWND hWnd=CreateWindow(L"DAS", L"Dodge And Shooting v.1.0", WS_OVERLAPPED|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_SYSMENU, 0, 0, 200, 100, NULL, NULL, wc.hInstance, NULL);
		
	RECT rect;
	GetClientRect(hWnd, &rect);
	int x=1000-rect.right;
	int y=700-rect.bottom;
	HDC hdc=GetDC(NULL);
	int dx=GetDeviceCaps(hdc, HORZRES);
	int dy=GetDeviceCaps(hdc, VERTRES);

	dx=(dx-x)/2;
	dy=(dy-y)/2;

	SetWindowPos(hWnd, HWND_NOTOPMOST, dx, dy, x, y, SWP_NOZORDER);
	ReleaseDC(hWnd, hdc);
	
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	initD3D(hWnd); //���� & �ʱ�ȭ

	////////////////

//	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

//	_CrtSetBreakAlloc(344);

	//////////


	bool flag;
	HWND focused;

	float fps=0.0f;;

	MSG msg;
	msg.message = 0;
	Game* game=new Game(d3d_dev);
	while(msg.message!=WM_QUIT){
		flag=false;
		focused=GetFocus();
		flag=(focused==hWnd);

		if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(game->gameloop(flag))
			break;
		game->draw();
		fps=CalcFPS();
	}

	delete game;
	
	cleanD3D(); //������

	UnregisterClass(L"DAS", wc.hInstance);

	_CrtDumpMemoryLeaks();
	return 0;
}
