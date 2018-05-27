#include "../stdafx.h"
#include "IntroScene.h"
#include "../UI/IntroUI.h"
#include "../Mob/MonsterCube.h"
#include "../Manager/Grid.h"


IntroScene::IntroScene()
{

}


IntroScene::~IntroScene()
{
	for (auto p : m_pMonsterCubeList)
	{
		SAFE_RELEASE(p);
	}

	SAFE_RELEASE(m_Grid);
	OnDestructIScene();
}

void IntroScene::Init()
{
	//IDisplayObject * pObj = new IntroUI; pObj->Init();
	//AddSimpleDisplayObj(pObj);
	g_pCamera->SetTest(true);
	
	m_Grid = new Grid(); m_Grid->Init();
	
	/*
	
	m_Player = new Player(); m_Player->Init();
	AddSimpleDisplayObj(m_Player);
	*/


	for (size_t i = 0; i < 50; i++)
	{
		MonsterCube * pMonsterCube = new MonsterCube;
		pMonsterCube->Init();
		m_pMonsterCubeList.push_back(pMonsterCube);
	}
	

	D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, true);

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}

void IntroScene::Update()
{
	for (auto p : m_pMonsterCubeList)
	{
		p->Update();
	}

	OnUpdateIScene();
}

void IntroScene::Render()
{
	for (auto p : m_pMonsterCubeList)
	{
		p->Render();
	}

	SAFE_RENDER(m_Grid);
	OnRenderIScene();
}

void IntroScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
