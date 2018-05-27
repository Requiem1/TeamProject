#pragma once
#include "../Manager/IDisplayObject.h"

class CheckpointSwitch : public IDisplayObject
{
private:
	vector<DrawingGroup*>	m_vecDrawingGroup;
	LPD3DXMESH				m_pMesh;
	vector<MTLTEX*>			m_vecMtlTex;

public:
	CheckpointSwitch();
	~CheckpointSwitch();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void RenderDrawingGroup();
	void RenderMesh();
};

