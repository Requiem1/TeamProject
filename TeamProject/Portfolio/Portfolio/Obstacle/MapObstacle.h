#pragma once
#include "IDisplayObject.h"

class DrawingGroup;

class MapObstacle :	public IDisplayObject
{
private:
	// OBB 바운싱 박스 변수
	CBox BoundingBox;

	// DrawingGroup, Mesh, MTLTex
	vector<DrawingGroup*>	m_vecDrawingGroup;
	LPD3DXMESH				m_pMeshMap;
	vector<MTLTEX*>			m_vecMtlTex;

	int m_ObstacleIndex;

public:
	MapObstacle();
	~MapObstacle();

	// map에서 불러온 Obstacle을 setting한다
	// 즉 x y z filename.obj를 받았을 때에 new를 해서 새로 obstacle 클래스를 만든 후
	// setObjstacleOnMap을 실행시키고 Obstacle매니저에 넣으면 된다 
	void SetObstacleOnMap(char *fileName, D3DXMATRIXA16 matWorld);

	// OBB 바운싱 박스 초기화 & 제작
	void initBoundingBox(CBox *pBox, const D3DXVECTOR3 &vecMin, const D3DXVECTOR3 &vecMax);
	void MakeBoundingBox(ID3DXMesh * ObjectMesh);

	// 바운싱박스의 update/render 함수
	bool UpdateBoundingBox();
	void RenderBoundingBox();

	// 바운싱 박스 충돌 체크
	// BSP를 이용한 공간분할로 충돌체크를 해야되지만
	// 일단은 objManager의 객체들과 모두 충돌체크를 돌리도록 한다
	IDisplayObject* CollideCheckFunc();
	CBox GetCBox() { return BoundingBox; }

	void RenderMesh();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	int GetObstacleIndex() { return m_ObstacleIndex; }
	void SetObstacleIndex(int index) { m_ObstacleIndex = index; }
};

