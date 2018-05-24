#pragma once
#include "BaseObject.h"
#include "../Obstacle/CollisionDetection.hpp"

class DrawingGroup;

class IDisplayObject : public BaseObject
{
protected:
	D3DXVECTOR3				m_pos;
	D3DXVECTOR3				m_rot;
	D3DXMATRIXA16			m_matWorld;
	IDisplayObject*			m_pParent;
	vector<IDisplayObject*> m_vecPChild;

	// 0523 - ����
	// DrawingGroup, Mesh, MTLTex
	vector<DrawingGroup*>	m_vecDrawingGroup;
	LPD3DXMESH				m_pMeshMap;
	vector<MTLTEX*>			m_vecMtlTex;

	// �浹 ���� �ٿ�� �ڽ�
	CBox BoundingBox;

public:
	IDisplayObject();
	virtual ~IDisplayObject();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void AddChild(IDisplayObject* pChild);
	virtual void ReleaseAll();

	D3DXVECTOR3		GetPosition() { return m_pos; }
	void			SetPosition(D3DXVECTOR3* pos) { m_pos = *pos; }
	D3DXVECTOR3		GetRotation() { return m_rot; }
	D3DXMATRIXA16	GetWorldMatrix() { return m_matWorld; }

	// 0523 - ����
	// �浹 ���� �޼��� -> map file���� �ҷ��� ������Ʈ�� Set
	void SetObjectOnMap(char *fileName, D3DXMATRIXA16 matWorld);

	// OBB �ٿ�� �ڽ� �ʱ�ȭ & ����
	void initBoundingBox(ID3DXMesh * ObjectMesh);
	void MakeBoundingBox(CBox *pBox, const D3DXVECTOR3 &vecMin, const D3DXVECTOR3 &vecMax);

	// �ٿ�̹ڽ��� update/render �Լ�
	void UpdateBoundingBox();
	void RenderBoundingBox();

	// �浹 �˻� �Լ�!
	D3DXVECTOR3 * CollideCheckFunc();

	CBox GetCBox() { return BoundingBox; }
};

