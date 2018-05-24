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

	// 0523 - 재익
	// DrawingGroup, Mesh, MTLTex
	vector<DrawingGroup*>	m_vecDrawingGroup;
	LPD3DXMESH				m_pMeshMap;
	vector<MTLTEX*>			m_vecMtlTex;

	// 충돌 감지 바운싱 박스
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

	// 0523 - 재익
	// 충돌 계산용 메서드 -> map file에서 불러온 오브젝트를 Set
	void SetObjectOnMap(char *fileName, D3DXMATRIXA16 matWorld);

	// OBB 바운싱 박스 초기화 & 제작
	void initBoundingBox(ID3DXMesh * ObjectMesh);
	void MakeBoundingBox(CBox *pBox, const D3DXVECTOR3 &vecMin, const D3DXVECTOR3 &vecMax);

	// 바운싱박스의 update/render 함수
	void UpdateBoundingBox();
	void RenderBoundingBox();

	// 충돌 검사 함수!
	D3DXVECTOR3 * CollideCheckFunc();

	CBox GetCBox() { return BoundingBox; }
};

