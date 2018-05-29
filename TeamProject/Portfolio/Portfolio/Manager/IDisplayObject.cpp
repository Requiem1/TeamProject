#include "../stdafx.h"
#include "IDisplayObject.h"
#include "../Obstacle/DrawingGroup.h"

IDisplayObject::IDisplayObject()
{
	m_pParent = NULL;
	D3DXMatrixIdentity(&m_matWorld);

	BoundingBox = new CBox();

	// ���� ��� �浹������ ���� �ʰ� RemoveObject�� �ؾ��Ѵ�!
	// �̰� �Ϲ� ������Ʈ�̹Ƿ� AddObject�� ��
	g_DisplayObjMgr->AddObject(this);
}


IDisplayObject::~IDisplayObject()
{
	SAFE_DELETE(BoundingBox);
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

void IDisplayObject::SetObjectOnMap(D3DXVECTOR3 WorldPos)
{
	m_matWorld._41 = WorldPos.x;
	m_matWorld._42 = WorldPos.y;
	m_matWorld._43 = WorldPos.z;

}
