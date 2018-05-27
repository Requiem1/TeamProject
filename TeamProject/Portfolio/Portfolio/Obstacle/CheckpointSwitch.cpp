#include "../stdafx.h"
#include "../Obstacle/CheckpointSwitch.h"
#include "../Obstacle/DrawingGroup.h"
#include "../Loader/ObjLoader.h"


CheckpointSwitch::CheckpointSwitch()
{
}


CheckpointSwitch::~CheckpointSwitch()
{
	for (auto p : m_vecDrawingGroup)
		SAFE_RELEASE(p);

	for (auto p : m_vecMtlTex)
		SAFE_RELEASE(p);

	SAFE_RELEASE(m_pMesh);
}

void CheckpointSwitch::Init()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	//D3DXMATRIXA16 matRX, matRY, matS, matWorld;
	//D3DXMatrixRotationX(&matRX, -D3DX_PI / 2.0f);
	//D3DXMatrixRotationY(&matRY, D3DX_PI / 2.0f);
	//D3DXMatrixScaling(&matS, 0.04f, 0.04f, 0.04f);
	//matWorld = matS * matRX * matRY;

	ObjLoader loader;
	m_pMesh = loader.LoadMesh("Resource/MapObject", "KnifeSwitch.obj", &matWorld, m_vecMtlTex);	// 메쉬 로드

	BoundingBox->initBoundingBox(m_pMesh);
}

void CheckpointSwitch::Update()
{
	BoundingBox->UpdateBoundingBox(m_matWorld, m_pos);
}

void CheckpointSwitch::Render()
{
	BoundingBox->RenderBoundingBox();
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	//RenderDrawingGroup();
	RenderMesh();
}

void CheckpointSwitch::RenderDrawingGroup()
{
	for (auto p : m_vecDrawingGroup)
		SAFE_RENDER(p);
}

void CheckpointSwitch::RenderMesh()
{
	for (size_t i = 0; i < m_vecMtlTex.size(); i++)
	{
		g_pDevice->SetMaterial(&m_vecMtlTex[i]->material);
		g_pDevice->SetTexture(0, m_vecMtlTex[i]->pTexture);
		//g_pDevice->SetFVF(VERTEX_PNT::FVF);
		m_pMesh->DrawSubset(m_vecMtlTex[i]->id);
	}
}
