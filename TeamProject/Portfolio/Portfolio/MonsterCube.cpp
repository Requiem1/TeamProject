#include "stdafx.h"
#include "MonsterCube.h"


MonsterCube::MonsterCube()
{
	D3DXMatrixIdentity(&m_matWorld);
	m_pVB = NULL;
	m_pIB = NULL;
} 


MonsterCube::~MonsterCube()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pIB);
}

void MonsterCube::Init()
{
	vector<D3DXVECTOR3> vecPos;

	for (size_t i = 0; i < CUBE_VERTEX_SIZE; i++)
	{
		vecPos.push_back(g_aCubeVertex[i]);
	}

	SetVertex(m_vecVertex, m_vecIndex, vecPos);
	SetBuffer(m_pVB, m_pIB, m_vecVertex, m_vecIndex);

	m_pVB->GetDesc(&m_VBDesc);
	m_pIB->GetDesc(&m_IBDesc);

	

	
}

void MonsterCube::Update()
{

}

void MonsterCube::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetFVF(VERTEX_PC::FVF);
	g_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX_PC));
	g_pDevice->SetIndices(m_pIB);
	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,
		m_VBDesc.Size, 0, m_IBDesc.Size / 3);
}


void MonsterCube::SetVertex(vector<VERTEX_PC>& vecVertexOut, vector<WORD>& vecIndexOut, vector<D3DXVECTOR3> vecPos)
{
	D3DCOLOR red = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR green = D3DCOLOR_XRGB(0, 255, 0);
	D3DCOLOR blue = D3DCOLOR_XRGB(0, 0, 255);
	D3DCOLOR white = D3DCOLOR_XRGB(255, 255, 255);
	D3DCOLOR yellow = D3DCOLOR_XRGB(255, 255, 0);

	vecVertexOut.push_back(VERTEX_PC(vecPos[0], white));
	vecVertexOut.push_back(VERTEX_PC(vecPos[1], white));
	vecVertexOut.push_back(VERTEX_PC(vecPos[2], white));
	vecVertexOut.push_back(VERTEX_PC(vecPos[3], white));
	vecVertexOut.push_back(VERTEX_PC(vecPos[4], white));
	vecVertexOut.push_back(VERTEX_PC(vecPos[5], white));
	vecVertexOut.push_back(VERTEX_PC(vecPos[6], white));
	vecVertexOut.push_back(VERTEX_PC(vecPos[7], white));

	for (size_t i = 0; i < CUBE_INDEX_SIZE; i++)
	{
		vecIndexOut.push_back(g_aCubeIndex[i]);
	}
}

void MonsterCube::SetBuffer(LPDIRECT3DVERTEXBUFFER9 & pVb, LPDIRECT3DINDEXBUFFER9 & pIb, vector<VERTEX_PC>& vecVertex, vector<WORD>& vecIndex)
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
