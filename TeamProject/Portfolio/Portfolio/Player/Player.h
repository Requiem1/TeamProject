#pragma once
#include "../Manager/IDisplayObject.h"


class Inventory;
// class ��
enum ITEMEQUIP
{
	HEAD = 1,
	BODY = 2,
	REG  = 4
};

struct PlAYERINFO
{
	int HP;
	int SP;
	int BodyDEF;
	int HeadDEF;
	int RegDEF;

	PlAYERINFO(int H, int S, int B, int Head, int R) :HP(H), SP(S), BodyDEF(B), HeadDEF(Head), RegDEF(R) {}

};

class Player :public IDisplayObject
{
private:
	vector<D3DXVECTOR3>     m_pVecVertex;
	vector<DWORD>           m_pIndexbuffer;
	vector<VERTEX_PC>		m_vecVertex;
	vector<WORD>			m_vecIndex;
	//Grid*                   TestGrid;
	PlAYERINFO              m_INFO;
	int                     m_EquipInfo;

	D3DXVECTOR3		m_DeltaPos;
	D3DXVECTOR3		m_DeltaRot;
	D3DXVECTOR3		m_forward;

	bool			m_isMoving;
	float			m_moveSpeed;
	float			m_currMoveSpeedRate;
	float			m_rotationSpeed;

	bool			m_IsJumping;
	float			m_jumpPower;
	float			m_gravity;
	float			m_currGravity;

	float			m_maxStepHeight;

	Inventory *             m_pInventory;
	// ��                   m_pCharacterWall;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9	m_pIB;
	D3DVERTEXBUFFER_DESC	m_VBDesc;
	D3DINDEXBUFFER_DESC		m_IBDesc;

	bool                    m_bHead;
	bool                    m_bBody;
	bool                    m_bReg;



public:
	Player();
	~Player();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	// ���ؽ� ���� �����
	void VertexBuffer(LPDIRECT3DVERTEXBUFFER9 &pVb,
		LPDIRECT3DINDEXBUFFER9 &pIb,
		vector<VERTEX_PC> &vecVertex, vector<WORD> &vecIndex);

	bool &   GetBoolHead()
	{
		return m_bHead;
	}

	bool &  GetBoolBody()
	{
		return m_bBody;
	}

	bool & GetBoolReg()
	{
		return m_bReg;
	}
	
	void Equip();

	Inventory* GetInveontory()
	{
		return m_pInventory;
	}

	void SetPlayerInfo(PlAYERINFO _P)
	{
		m_INFO = _P;
	}

	PlAYERINFO  GetPlayerInfo()
	{
		return m_INFO;
	}
};

