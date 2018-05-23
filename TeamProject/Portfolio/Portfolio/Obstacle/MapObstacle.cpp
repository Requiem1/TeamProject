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
	m_pMeshMap = loader.LoadMesh("resources/myGame", "fileName", &m_matWorld, m_vecMtlTex);	// �޽� �ε� 

	// ObstacleManager�� �߰�!
	g_ObstacleMgr->AddObstacle(this, NORMAL_OBSTACLE);

	// �浹 �˻�� �ٿ�̹ڽ� ����
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
	// dwVertexNum = Mesh����->GetNumVertices()
	// dwFvfSize = Mesh����->GetFVF() -- �ٸ� �̰� VERTEX_PNT:FVF�� �ؾߵɵ���
	DWORD dwVertexNum = ObjectMesh->GetNumVertices();
	DWORD dwFvfSize = D3DXGetFVFVertexSize(ObjectMesh->GetFVF());

	D3DXVECTOR3 vecMin, vecMax, vecMinWorld, vecMaxWorld;
	VOID *ptr = NULL;

	// �ٿ�� �ڽ� ����
	ObjectMesh->LockVertexBuffer(0, &ptr);
	D3DXComputeBoundingBox((D3DXVECTOR3 *)ptr, dwVertexNum, dwFvfSize, &vecMin, &vecMax);
	ObjectMesh->UnlockVertexBuffer();

	initBoundingBox(&BoundingBox, vecMin, vecMax);
}

bool MapObstacle::UpdateBoundingBox()
{
	D3DXMATRIX matBox;

	// �ڽ��� transform�� �����´�.
	GetBoxTransform(&matBox, &BoundingBox);

	// �ڽ��� transform�� �ٲ۴�.
	matBox *= m_matWorld;
	SetBoxTransform(&matBox, &BoundingBox);

	// �ڽ��� center ��ǥ�� �ٲ۴�.
	//D3DXVECTOR3 vecCenter(BoundingBox.center[0], BoundingBox.center[1], BoundingBox.center[2]);
	//D3DXVec3TransformCoord(&vecCenter, &vecCenter, &m_matWorld);
	BoundingBox.center[0] = m_pos.x;
	BoundingBox.center[1] = m_pos.y;
	BoundingBox.center[2] = m_pos.z;

	// �浹ü�� ĳ�����̹Ƿ� ���� Ŭ������ IDisplayObject�� ����ؾ��Ѵ�
	// �� �浹�ڵ�� ĳ������ �浹 �Լ��� ���Եɰ�...
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

// ĳ���� Ŭ���� ��������� �������� �Ѱ��ֵ��� ����
// �浹�� ���� �����̴� �� Obstacle�� �ƴ϶� ĳ���ʹϱ�...
IDisplayObject * MapObstacle::CollideCheckFunc()
{
	// ĳ���� �浹�� ��� 
	// �Ϲ� Obstacle / �����ϴ� Obstacle / Wall ������� ������ �ε����� �Ѵ�!

	// ���� �����Ͽ� �浹 �˻��ϴ� �κ��� �켱 �����ϰ�
	// �� ���� ������Ʈ����� �˻縦 �Ѵ�);
	for(auto p : g_ObstacleMgr->GetAllObstacleList())
	{
		if (p == this)
			continue;

		// Collision Detection Test!
		int nRet = BoxBoxIntersectionTest(BoundingBox, p->GetCBox());

		// �浹!
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
	// ���� �ָ� �׸��� �� �ȳ��ͼ�.. �ϴ� ���� ��
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	//RenderDrawingGroup();
	RenderMesh();
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
}
