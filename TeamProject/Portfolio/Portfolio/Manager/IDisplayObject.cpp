#include "../stdafx.h"
#include "IDisplayObject.h"
#include "../Obstacle/DrawingGroup.h"

IDisplayObject::IDisplayObject()
{
	m_pParent = NULL;
	D3DXMatrixIdentity(&m_matWorld);

	// ���� ��� �浹������ ���� �ʰ� RemoveObject�� �ؾ��Ѵ�!
	// �̰� �Ϲ� ������Ʈ�̹Ƿ� AddObject�� ��
	g_DisplayObjMgr->AddObject(this);
}


IDisplayObject::~IDisplayObject()
{
	for (auto p : m_vecDrawingGroup)
		SAFE_RELEASE(p);

	for (auto p : m_vecMtlTex)
		SAFE_RELEASE(p);

	SAFE_RELEASE(m_pMeshMap);
}

void IDisplayObject::AddChild(IDisplayObject * pChild)
{
	if (pChild == NULL) return;
	m_vecPChild.push_back(pChild);
	pChild->m_pParent = this;
}

void IDisplayObject::ReleaseAll()
{
	for (auto child : m_vecPChild)
		if (child) child->ReleaseAll();

	Release();
}

void IDisplayObject::SetObjectOnMap(char * fileName, D3DXMATRIXA16 matWorld)
{
	m_matWorld = matWorld;

	// Obj������ ��� load
	//ObjLoader loader;
	//m_pMeshMap = loader.LoadMesh("resources/myGame", "fileName", &m_matWorld, m_vecMtlTex);	// �޽� �ε� 

	// �浹 �˻�� �ٿ�̹ڽ� ����
	initBoundingBox(m_pMeshMap);
}

void IDisplayObject::MakeBoundingBox(CBox * pBox, const D3DXVECTOR3 & vecMin, const D3DXVECTOR3 & vecMax)
{
	// Boundingbox�� �����ϱ� ���� ���� �����
	vector<VERTEX_PC> temp;
	D3DCOLOR green = D3DCOLOR_XRGB(0, 255, 0);

	temp.push_back(VERTEX_PC(D3DXVECTOR3(vecMin.x, vecMin.y, vecMin.z), green)); //Min
	temp.push_back(VERTEX_PC(D3DXVECTOR3(vecMin.x, vecMax.y, vecMin.z), green));
	temp.push_back(VERTEX_PC(D3DXVECTOR3(vecMax.x, vecMax.y, vecMin.z), green));
	temp.push_back(VERTEX_PC(D3DXVECTOR3(vecMax.x, vecMin.y, vecMin.z), green));

	temp.push_back(VERTEX_PC(D3DXVECTOR3(vecMin.x, vecMin.y, vecMax.z), green));
	temp.push_back(VERTEX_PC(D3DXVECTOR3(vecMin.x, vecMax.y, vecMax.z), green));
	temp.push_back(VERTEX_PC(D3DXVECTOR3(vecMax.x, vecMax.y, vecMax.z), green)); //Max
	temp.push_back(VERTEX_PC(D3DXVECTOR3(vecMax.x, vecMin.y, vecMax.z), green));

	for (size_t i = 0; i < CUBE_INDEX_SIZE; i++)
	{
		pBox->vecBoxVertex.push_back(temp[g_aCubeIndex[i]]);
	}


	// BoundingBox�� ����� �������� ���� �ִ´�
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

void IDisplayObject::initBoundingBox(ID3DXMesh * ObjectMesh)
{
	D3DXVECTOR3 vecMin, vecMax, vecMinWorld, vecMaxWorld;
	VOID *ptr = NULL;

	if (ObjectMesh != NULL)
	{
		// dwVertexNum = Mesh����->GetNumVertices()
		// dwFvfSize = Mesh����->GetFVF() -- �ٸ� �̰� VERTEX_PNT:FVF�� �ؾߵɵ���
		DWORD dwVertexNum = ObjectMesh->GetNumVertices();
		DWORD dwFvfSize = D3DXGetFVFVertexSize(ObjectMesh->GetFVF());

		// BoundingBox ����
		ObjectMesh->LockVertexBuffer(0, &ptr);
		D3DXComputeBoundingBox((D3DXVECTOR3 *)ptr, dwVertexNum, dwFvfSize, &vecMin, &vecMax);
		ObjectMesh->UnlockVertexBuffer();
	}
	else
	{
		// �޽� ���� ť�길 ���� ��� -> ť���� Min�� Max���� �ִ´�
		vecMin = g_aCubeVertex[0];
		vecMax = g_aCubeVertex[6];
	}

	MakeBoundingBox(&BoundingBox, vecMin, vecMax);
}

void IDisplayObject::UpdateBoundingBox()
{
	D3DXMATRIX matBox;

	// �ڽ��� transform�� �����´�.
	GetBoxTransform(&matBox, &BoundingBox);

	// �ڽ��� transform�� �ٲ۴�.
	matBox *= m_matWorld;
	SetBoxTransform(&matBox, &BoundingBox);

	// �ڽ��� center ��ǥ�� �ٲ۴�.
	BoundingBox.center[0] = m_pos.x;
	BoundingBox.center[1] = m_pos.y;
	BoundingBox.center[2] = m_pos.z;
}

void IDisplayObject::RenderBoundingBox()
{
	// 0 Ű�� ������ BoundingBox�� Render�ȴ�
	if (GetAsyncKeyState('0') && 0x8000)
	{
		g_pDevice->SetTexture(0, NULL);
		//g_pDevice->SetFVF(VERTEX_PC::FVF);
		g_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, BoundingBox.vecBoxVertex.size() - 1,
			&BoundingBox.vecBoxVertex[0], sizeof(VERTEX_PC));
	}
}

IDisplayObject * IDisplayObject::CollideCheckFunc()
{
	// �ٿ�� �ڽ� �浹 �˻�!
	// BSP�� �̿��� �������ҷ� �浹üũ�� �ؾߵ�����
	// �ϴ��� objManager�� ��ü��� ��� �浹üũ�� �������� �Ѵ�
	for (auto p : g_DisplayObjMgr->GetAllDisplayObjList())
	{
		if (p == this)
			continue;

		// Collision Detection Test!
		int nRet = BoxBoxIntersectionTest(BoundingBox, p->GetCBox());

		// �浹!
		// �ٸ� �̹���� ���� ó�� �浹�� �ϳ��� ���� �浹�ϹǷ�
		// �������� �ѹ��� �浹�ϴ� ����� ����ؾ��Ѵ�
		if (nRet == 1)
		{
			return p;
		}
	}

	return NULL;
}
