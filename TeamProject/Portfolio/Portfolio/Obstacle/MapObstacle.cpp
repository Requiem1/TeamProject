#include "../stdafx.h"
#include "MapObstacle.h"
#include "DrawingGroup.h"
#include "ObjLoader.h"

MapObstacle::MapObstacle()
{
}


MapObstacle::~MapObstacle()
{
	for (auto p : m_vecDrawingGroup)
		SAFE_RELEASE(p);

	for (auto p : m_vecMtlTex)
		SAFE_RELEASE(p);

	SAFE_RELEASE(m_pMeshMap);
}

void MapObstacle::SetObstacleOnMap(char * fileName, D3DXMATRIXA16 matWorld)
{
	m_matWorld = matWorld;

	ObjLoader loader;
	m_pMeshMap = loader.LoadMesh("resources/myGame", "fileName", &m_matWorld, m_vecMtlTex);	// 메쉬 로드 

	// ObstacleManager에 추가!
	g_ObstacleMgr->AddObstacle(this, NORMAL_OBSTACLE);

	// 충돌 검사용 바운싱박스 제작
	MakeBoundingBox(m_pMeshMap);
}

void MapObstacle::initBoundingBox(CBox * pBox, const D3DXVECTOR3 & vecMin, const D3DXVECTOR3 & vecMax)
{
	pBox->center[0] = (vecMin.x + vecMax.x) / 2.0F;
	pBox->center[1] = (vecMin.y + vecMax.y) / 2.0F;
	pBox->center[2] = (vecMin.z + vecMax.z) / 2.0F;

	pBox->extent[0] = vecMax.x - pBox->center[0];
	pBox->extent[1] = vecMax.y - pBox->center[1];
	pBox->extent[2] = vecMax.z - pBox->center[2];

	// identity world coordinate axis
	pBox->axis[0][0] = 1.0F;
	pBox->axis[0][1] = 0.0F;
	pBox->axis[0][2] = 0.0F;
	pBox->axis[1][0] = 0.0F;
	pBox->axis[1][1] = 1.0F;
	pBox->axis[1][2] = 0.0F;
	pBox->axis[2][0] = 0.0F;
	pBox->axis[2][1] = 0.0F;
	pBox->axis[2][2] = 1.0F;
	pBox->translation[0] = 0.0F;
	pBox->translation[1] = 0.0F;
	pBox->translation[2] = 0.0F;
}

void MapObstacle::MakeBoundingBox(ID3DXMesh * ObjectMesh)
{	
	// dwVertexNum = Mesh변수->GetNumVertices()
	// dwFvfSize = Mesh변수->GetFVF() -- 다만 이건 VERTEX_PNT:FVF를 해야될듯함
	DWORD dwVertexNum = ObjectMesh->GetNumVertices();
	DWORD dwFvfSize = D3DXGetFVFVertexSize(ObjectMesh->GetFVF());

	D3DXVECTOR3 vecMin, vecMax, vecMinWorld, vecMaxWorld;
	VOID *ptr = NULL;

	// 바운싱 박스 제작
	ObjectMesh->LockVertexBuffer(0, &ptr);
	D3DXComputeBoundingBox((D3DXVECTOR3 *)ptr, dwVertexNum, dwFvfSize, &vecMin, &vecMax);
	ObjectMesh->UnlockVertexBuffer();

	initBoundingBox(&BoundingBox, vecMin, vecMax);
}

bool MapObstacle::UpdateBoundingBox()
{
	D3DXMATRIX matBox;

	// 박스의 transform을 가져온다.
	GetBoxTransform(&matBox, &BoundingBox);

	// 박스의 transform을 바꾼다.
	matBox *= m_matWorld;
	SetBoxTransform(&matBox, &BoundingBox);

	// 박스의 center 좌표도 바꾼다.
	//D3DXVECTOR3 vecCenter(BoundingBox.center[0], BoundingBox.center[1], BoundingBox.center[2]);
	//D3DXVec3TransformCoord(&vecCenter, &vecCenter, &m_matWorld);
	BoundingBox.center[0] = m_pos.x;
	BoundingBox.center[1] = m_pos.y;
	BoundingBox.center[2] = m_pos.z;

	// 충돌체는 캐릭터이므로 상위 클래스인 IDisplayObject를 사용해야한다
	// 이 충돌코드는 캐릭터의 충돌 함수에 포함될것...
	IDisplayObject* Collide = CollideCheckFunc();
	if (Collide != NULL)
	{
		return true;
	}

	return false;
}

void MapObstacle::RenderBoundingBox()
{

}

// 캐릭터 클래스 만들어지면 그쪽으로 넘겨주도록 하자
// 충돌을 위해 움직이는 건 Obstacle이 아니라 캐릭터니까...
IDisplayObject * MapObstacle::CollideCheckFunc()
{
	// 캐릭터 충돌의 경우 
	// 일반 Obstacle / 폭발하는 Obstacle / Wall 상관없이 무조건 부딪혀야 한다!

	// 공간 분할하여 충돌 검사하는 부분은 우선 제외하고
	// 전 맵의 오브젝트들과의 검사를 한다);
	for(auto p : g_ObstacleMgr->GetAllObstacleList())
	{
		if (p == this)
			continue;

		// Collision Detection Test!
		int nRet = BoxBoxIntersectionTest(BoundingBox, p->GetCBox());

		// 충돌!
		if (nRet == 1)
			return p;
	}

	return NULL;
}

void MapObstacle::RenderMesh()
{
	for (size_t i = 0; i < m_vecMtlTex.size(); i++)
	{
		g_pDevice->SetMaterial(&m_vecMtlTex[i]->material);
		g_pDevice->SetTexture(0, m_vecMtlTex[i]->pTexture);
		//g_pDevice->SetFVF(VERTEX_PNT::FVF);
		m_pMeshMap->DrawSubset(m_vecMtlTex[i]->id);
	}
}

void MapObstacle::Init()
{
}

void MapObstacle::Update()
{
}

void MapObstacle::Render()
{
	// 빛을 주면 그림이 다 안나와서.. 일단 빛을 뺌
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	//RenderDrawingGroup();
	RenderMesh();
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
}
