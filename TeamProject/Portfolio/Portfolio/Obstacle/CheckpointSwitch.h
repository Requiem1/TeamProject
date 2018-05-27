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

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void RenderDrawingGroup();
	void RenderMesh();
};

