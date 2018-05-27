#include "../stdafx.h"
#include "SceneHeightMap.h"
#include "../Map/HeightMap.h"
#include "../Player/Player.h"

#include "../Map/SkyBox.h"
#include "../Obstacle/MapObstacle.h"
#include "../Obstacle/CheckpointSwitch.h"

SceneHeightMap::SceneHeightMap()
{
	S_HeightMap = NULL;
	S_Player = NULL;
	S_SkyBox = NULL;
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

	// 맵
	S_HeightMap = new HeightMap();
	AddSimpleDisplayObj(S_HeightMap);

	S_HeightMap->Setdimension(257);
	S_HeightMap->Load("Resource/Map/HeightMap.raw", &matS);
	S_HeightMap->Init();

	// 플레이어
	S_Player = new Player();
	S_Player->Init();
	AddSimpleDisplayObj(S_Player);

	// 스카이박스
	S_SkyBox = new SkyBox();
	S_SkyBox->Create("Resource/Skybox", "grimmnight");
	AddSimpleDisplayObj(S_SkyBox);

	//lD3DXMATRIXA16 ObstaclePos;

	// 장애물
	//MapObstacle* Obstacle = new MapObstacle();
	//Obstacle->SetObstacle("Switch.obj", D3DXVECTOR3(5.0f, 2.3f, 5.0f));
	//S_vecObstacle.push_back(Obstacle);
	//AddSimpleDisplayObj(Obstacle);

	//S_Switch->Init();
	//AddSimpleDisplayObj(S_Switch);

	D3DMATERIAL9 mtl = DXUtil::WHITE_MTRL;
	S_HeightMap->SetMtlTex(mtl, g_pTextureManager->GetTexture(L"Resource/Map/desert.jpg"));

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