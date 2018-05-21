#pragma once
#include "IDisplayObject.h"

class DrawingGroup;

class MapObstacle :	public IDisplayObject
{
private:
	// OBB �ٿ�� �ڽ� ����
	CBox BoundingBox;

	// DrawingGroup, Mesh, MTLTex
	vector<DrawingGroup*>	m_vecDrawingGroup;
	LPD3DXMESH				m_pMeshMap;
	vector<MTLTEX*>			m_vecMtlTex;

	int m_ObstacleIndex;

public:
	MapObstacle();
	~MapObstacle();

	// map���� �ҷ��� Obstacle�� setting�Ѵ�
	// �� x y z filename.obj�� �޾��� ���� new�� �ؼ� ���� obstacle Ŭ������ ���� ��
	// setObjstacleOnMap�� �����Ű�� Obstacle�Ŵ����� ������ �ȴ� 
	void SetObstacleOnMap(char *fileName, D3DXMATRIXA16 matWorld);

	// OBB �ٿ�� �ڽ� �ʱ�ȭ & ����
	void initBoundingBox(CBox *pBox, const D3DXVECTOR3 &vecMin, const D3DXVECTOR3 &vecMax);
	void MakeBoundingBox(ID3DXMesh * ObjectMesh);

	// �ٿ�̹ڽ��� update/render �Լ�
	bool UpdateBoundingBox();
	void RenderBoundingBox();

	// �ٿ�� �ڽ� �浹 üũ
	// BSP�� �̿��� �������ҷ� �浹üũ�� �ؾߵ�����
	// �ϴ��� objManager�� ��ü��� ��� �浹üũ�� �������� �Ѵ�
	IDisplayObject* CollideCheckFunc();
	CBox GetCBox() { return BoundingBox; }

	void RenderMesh();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	int GetObstacleIndex() { return m_ObstacleIndex; }
	void SetObstacleIndex(int index) { m_ObstacleIndex = index; }
};

