#include "../stdafx.h"
#include "IntroScene.h"
#include "../UI/IntroUI.h"


IntroScene::IntroScene()
{

}


IntroScene::~IntroScene()
{
	OnDestructIScene();
}

void IntroScene::Init()
{
	IDisplayObject * pObj = new IntroUI; pObj->Init();
	AddSimpleDisplayObj(pObj);

	D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, true);

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}

void IntroScene::Update()
{
	OnUpdateIScene();
}

void IntroScene::Render()
{
	OnRenderIScene();
}

void IntroScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
