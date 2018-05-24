#include "../stdafx.h"
#include "IDisplayObject.h"
#include "../Obstacle/DrawingGroup.h"

IDisplayObject::IDisplayObject()
{
	m_pParent = NULL;
	D3DXMatrixIdentity(&m_matWorld);

	// 맵의 경우 충돌감지를 하지 않게 RemoveObject를 해야한다!
	// 이건 일반 오브젝트이므로 AddObject를 함
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

	// Obj파일인 경우 load
	//ObjLoader loader;
	//m_pMeshMap = loader.LoadMesh("resources/myGame", "fileName", &m_matWorld, m_vecMtlTex);	// 메쉬 로드 

	// 충돌 검사용 바운싱박스 제작
	initBoundingBox(m_pMeshMap);
}

void IDisplayObject::MakeBoundingBox(CBox * pBox, const D3DXVECTOR3 & vecMin, const D3DXVECTOR3 & vecMax)
{
	// Boundingbox를 렌더하기 위한 선을 만든다
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


	// BoundingBox의 연산용 변수들의 값을 넣는다
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
		// dwVertexNum = Mesh변수->GetNumVertices()
		// dwFvfSize = Mesh변수->GetFVF() -- 다만 이건 VERTEX_PNT:FVF를 해야될듯함
		DWORD dwVertexNum = ObjectMesh->GetNumVertices();
		DWORD dwFvfSize = D3DXGetFVFVertexSize(ObjectMesh->GetFVF());

		// BoundingBox 제작
		ObjectMesh->LockVertexBuffer(0, &ptr);
		D3DXComputeBoundingBox((D3DXVECTOR3 *)ptr, dwVertexNum, dwFvfSize, &vecMin, &vecMax);
		ObjectMesh->UnlockVertexBuffer();
	}
	else
	{
		// 메쉬 없이 큐브만 있을 경우 -> 큐브의 Min과 Max값을 넣는다
		vecMin = g_aCubeVertex[0];
		vecMax = g_aCubeVertex[6];
	}

	MakeBoundingBox(&BoundingBox, vecMin, vecMax);
}

void IDisplayObject::UpdateBoundingBox()
{
	D3DXMATRIX matBox;

	// 박스의 transform을 가져온다.
	GetBoxTransform(&matBox, &BoundingBox);

	// 박스의 transform을 바꾼다.
	matBox *= m_matWorld;
	SetBoxTransform(&matBox, &BoundingBox);

	// 박스의 center 좌표도 바꾼다.
	BoundingBox.center[0] = m_pos.x;
	BoundingBox.center[1] = m_pos.y;
	BoundingBox.center[2] = m_pos.z;
}

void IDisplayObject::RenderBoundingBox()
{
	// 0 키를 누르면 BoundingBox가 Render된다
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
	// 바운싱 박스 충돌 검사!
	// BSP를 이용한 공간분할로 충돌체크를 해야되지만
	// 일단은 objManager의 객체들과 모두 충돌체크를 돌리도록 한다
	for (auto p : g_DisplayObjMgr->GetAllDisplayObjList())
	{
		if (p == this)
			continue;

		// Collision Detection Test!
		int nRet = BoxBoxIntersectionTest(BoundingBox, p->GetCBox());

		// 충돌!
		// 다만 이방법은 가장 처음 충돌한 하나의 값만 충돌하므로
		// 여러개를 한번에 충돌하는 방법을 고안해야한다
		if (nRet == 1)
		{
			return p;
		}
	}

	return NULL;
}
