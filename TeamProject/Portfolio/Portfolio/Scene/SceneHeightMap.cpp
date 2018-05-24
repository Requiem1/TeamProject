#include "../stdafx.h"
#include "SceneHeightMap.h"
#include "../Map/HeightMap.h"
#include "../Player/Player.h"

SceneHeightMap::SceneHeightMap()
{
	S_HeightMap = NULL;
	S_Player = NULL;

	// 맵이므로 오브젝트에서 뺀다
	g_DisplayObjMgr->RemoveObject(S_HeightMap);
}


SceneHeightMap::~SceneHeightMap()
{
	OnDestructIScene();
}

void SceneHeightMap::Init()
{
	g_pCamera->SetTest(true);

	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 0.2f, 0.03f, 0.2f);

	S_HeightMap = new HeightMap();
	AddSimpleDisplayObj(S_HeightMap);

	S_Player = new Player();
	S_Player->Init();
	AddSimpleDisplayObj(S_Player);

	S_HeightMap->Setdimension(257);
	S_HeightMap->Load("Resource/Map/HeightMap.raw", &matS);
	S_HeightMap->Init();

	D3DMATERIAL9 mtl = DXUtil::WHITE_MTRL;
	S_HeightMap->SetMtlTex(mtl, g_pTextureManager->GetTexture("Resource/Map/desert.jpg"));

	g_pMapManager->AddMap("HeightMap", S_HeightMap);
	g_pMapManager->SetCurrentMap("HeightMap");

	D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);		// 광원의 방향을 단위벡터로 만듬
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);  // 광원 종류와 방향/색 지정
	g_pDevice->SetLight(0, &light);		// 디바이스에 0번 광원 설치
	g_pDevice->LightEnable(0, true);	// 0번 광원을 켬

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}

void SceneHeightMap::Update()
{
	OnUpdateIScene();
}

void SceneHeightMap::Render()
{
	OnRenderIScene();
}

void SceneHeightMap::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SAFE_WNDPROC(S_HeightMap);
}
