#include "../stdafx.h"
#include "Item.h"

ITEM::ITEM()
{

}

ITEM::~ITEM()
{
	SAFE_RELEASE(m_pIB);
	SAFE_RELEASE(m_pVB);
}

void ITEM::Load(string Path)
{
}



void ITEM::Update()
{
	if (m_IsClick)
	{
		m_pos = m_pos + m_forward* 1.0f* m_moveSpeed*m_currMoveSpeedRate;
		D3DXMatrixTranslation(&m_CTransMat, m_pos.x, m_pos.y, m_pos.z);
		m_matWorld = m_CSMat * m_CTransMat;
	}
	//UpdateBoundingBox();
}

void ITEM::Render()
{
	if (m_IsClick)
	{
		g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pDevice->SetFVF(VERTEX_PC::FVF);
		g_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX_PC));
		g_pDevice->SetIndices(m_pIB);
		g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,
			m_VBDesc.Size, 0, m_IBDesc.Size / 3);
	}
	//RenderBoundingBox();
}

void ITEM::SetBullet(D3DXVECTOR3 *m_pForward, D3DXVECTOR3 *m_ParantPos)
{
	m_forward = (*m_pForward);
	m_pos = (*m_ParantPos);
}

void ITEM::VertexBuffer(LPDIRECT3DVERTEXBUFFER9 & pVb, LPDIRECT3DINDEXBUFFER9 & pIb, vector<VERTEX_PC>& vecVertex, vector<WORD>& vecIndex)
{
	g_pDevice->CreateVertexBuffer(vecVertex.size() * sizeof(VERTEX_PC),
		0, VERTEX_PC::FVF, D3DPOOL_MANAGED, &pVb, NULL);

	VERTEX_PC* pVertex;
	pVb->Lock(0, 0, (LPVOID*)&pVertex, 0);
	memcpy(pVertex, &vecVertex[0], vecVertex.size() * sizeof(VERTEX_PC));
	pVb->Unlock();
	vecVertex.clear();

	g_pDevice->CreateIndexBuffer(vecIndex.size() * sizeof(WORD),
		NULL, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIb, NULL);

	WORD* pIndex;
	pIb->Lock(0, 0, (LPVOID*)&pIndex, 0);
	memcpy(pIndex, &vecIndex[0], vecIndex.size() * sizeof(WORD));
	pIb->Unlock();


	vecIndex.clear();
}

void ITEM::Init()
{
	// 메쉬 혹은 오브젝트 로딩

	m_IsClick = false;
	m_moveSpeed = 0.2f;
	m_currMoveSpeedRate = 1.0f;

	vector<D3DXVECTOR3> vecPos;
	for (size_t i = 0; i < CUBE_VERTEX_SIZE; i++)
	{
		vecPos.push_back(g_aCubeVertex[i]);
	}

	// 버텍스 설정
	D3DCOLOR blue = D3DCOLOR_XRGB(0, 102, 255);

	m_vecVertex.push_back(VERTEX_PC(vecPos[0], blue));
	m_vecVertex.push_back(VERTEX_PC(vecPos[1], blue));
	m_vecVertex.push_back(VERTEX_PC(vecPos[2], blue));
	m_vecVertex.push_back(VERTEX_PC(vecPos[3], blue));
	m_vecVertex.push_back(VERTEX_PC(vecPos[4], blue));
	m_vecVertex.push_back(VERTEX_PC(vecPos[5], blue));
	m_vecVertex.push_back(VERTEX_PC(vecPos[6], blue));
	m_vecVertex.push_back(VERTEX_PC(vecPos[7], blue));

	for (int i = 0; i < CUBE_INDEX_SIZE; i++)
	{
		m_vecIndex.push_back(g_aCubeIndex[i]);
	}
	VertexBuffer(m_pVB, m_pIB, m_vecVertex, m_vecIndex);

	m_pVB->GetDesc(&m_VBDesc);
	m_pIB->GetDesc(&m_IBDesc);

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixScaling(&m_CSMat, 0.2f, 0.2f, 0.2f);

	//initBoundingBox(NULL);
}
