#pragma once
#include "../Manager/IDisplayObject.h"

class DrawingGroup;

class MapObstacle :	public IDisplayObject
{
private:
	// DrawingGroup, Mesh, MTLTex
	vector<DrawingGroup*>	m_vecDrawingGroup;
	LPD3DXMESH				m_pMesh;
	vector<MTLTEX*>			m_vecMtlTex;

public:
	MapObstacle();
	~MapObstacle();

	// map���� �ҷ��� Obstacle�� setting�Ѵ�
	// �� x y z filename.obj�� �޾��� ���� new�� �ؼ� ���� obstacle Ŭ������ ���� ��
	// setObjstacleOnMap�� �����Ű�� Obstacle�Ŵ����� ������ �ȴ� 
	void SetObstacle(const char *fileName, D3DXVECTOR3 WorldPos);
	
	void RenderDrawingGroup();
	void RenderMesh();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

