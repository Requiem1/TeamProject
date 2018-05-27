#pragma once

#include "IDisplayObject.h"


enum ITEMTYPE
{
	HEALING,
	SHOOT,
	AMOR
};
enum FIRETYPE
{
	SINGLESHOT,
	AUTOMATICFIRE
};

struct ITEMINFO
{
	int HP;
	int Attack;
	int Defence;
	float RateTime; // ġ�� �������� ��� �������� ����ϴµ� �ɸ��� �ð��� ���.
	ITEMTYPE Type;
};

class ITEM : public IDisplayObject
{
private:
	vector<VERTEX_PC>		m_vecVertex;
	vector<WORD>			m_vecIndex;


	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9	m_pIB;

	D3DVERTEXBUFFER_DESC	m_VBDesc;
	D3DINDEXBUFFER_DESC		m_IBDesc;
	
	D3DXMATRIXA16           m_pMat;
	D3DXMATRIXA16           m_CSMat;
	D3DXMATRIXA16           m_CTransMat;
	D3DXVECTOR3             m_forward;

	bool                    m_IsClick;
	FIRETYPE                m_fireType;

	float			        m_moveSpeed;
	float			        m_currMoveSpeedRate;

	ITEMINFO INFO;

public:
	ITEM();
	~ITEM();

	// ���� �ϼ��Ÿ� �ε��� ��
	void Load(string Path);
	
	void SetClick(bool isClick)
	{
		m_IsClick = isClick;

	}
	void Update();
	void Render();
	void SetBullet(D3DXVECTOR3* m_pForward,D3DXVECTOR3 *m_ParantPos);

	void VertexBuffer(LPDIRECT3DVERTEXBUFFER9 &pVb,
		LPDIRECT3DINDEXBUFFER9 &pIb,
		vector<VERTEX_PC> &vecVertex, vector<WORD> &vecIndex);

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
};