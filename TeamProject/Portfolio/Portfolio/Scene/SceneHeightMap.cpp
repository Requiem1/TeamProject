#include "../stdafx.h"
#include "SceneHeightMap.h"
#include "../Map/HeightMap.h"
#include "../Player/Player.h"

#include "../Map/SkyBox.h"
#include "../Obstacle/MapObstacle.h"
#include "../Obstacle/CheckpointSwitch.h"

#include "../Mob/MonsterCube.h"

SceneHeightMap::SceneHeightMap()
{
	S_HeightMap = NULL;
	S_Player = NULL;
	S_SkyBox = NULL;
}


SceneHeightMap::~SceneHeightMap()
{
	SAFE_RELEASE(S_HeightMap);
	SAFE_RELEASE(S_SkyBox);
	OnDestructIScene();
}

void SceneHeightMap::Init()
{
	g_pCamera->SetTest(true);

	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 0.2f, 0.03f, 0.2f);

	// ��
	S_HeightMap = new HeightMap();

	S_HeightMap->Setdimension(257);
	S_HeightMap->Load("Resource/Map/HeightMap.raw", &matS);
	S_HeightMap->Init();

	D3DMATERIAL9 mtl = DXUtil::WHITE_MTRL;
	S_HeightMap->SetMtlTex(mtl, g_pTextureManager->GetTexture(L"Resource/Map/desert.jpg"));

	g_pMapManager->AddMap("HeightMap", S_HeightMap);
	g_pMapManager->SetCurrentMap("HeightMap");
	//AddSimpleDisplayObj(S_HeightMap);


	// ��ī�̹ڽ�
	S_SkyBox = new SkyBox();
	S_SkyBox->Create("Resource/Skybox", "grimmnight");

	for (size_t i = 0; i < 50; i++)
	{
		MonsterCube * pMonsterCube = new MonsterCube;
		pMonsterCube->Init();
		m_pMonsterCubeList.push_back(pMonsterCube);
		AddSimpleDisplayObj(pMonsterCube);
	}
	//AddSimpleDisplayObj(S_SkyBox);

	//lD3DXMATRIXA16 ObstaclePos;

	// ��ֹ�
	//MapObstacle* Obstacle = new MapObstacle();
	//Obstacle->SetObstacle("Switch.obj", D3DXVECTOR3(5.0f, 2.3f, 5.0f));
	//S_vecObstacle.push_back(Obstacle);
	//AddSimpleDisplayObj(Obstacle);

	//S_Switch->Init();
	//AddSimpleDisplayObj(S_Switch);

	D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);		// ������ ������ �������ͷ� ����
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);  // ���� ������ ����/�� ����
	g_pDevice->SetLight(0, &light);		// ����̽��� 0�� ���� ��ġ
	g_pDevice->LightEnable(0, true);	// 0�� ������ ��

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}

void SceneHeightMap::Update()
{
	OnUpdateIScene();
}

void SceneHeightMap::Render()
{
	OnRenderIScene();
	SAFE_RENDER(S_HeightMap);
	SAFE_RENDER(S_SkyBox);
}

void SceneHeightMap::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//SAFE_WNDPROC(S_HeightMap);
}