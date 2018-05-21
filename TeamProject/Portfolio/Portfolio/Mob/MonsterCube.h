#pragma once
class MonsterCube : public IDisplayObject
{
private:
	vector<VERTEX_PC>		m_vecVertex;
	vector<WORD>			m_vecIndex;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9	m_pIB;
	D3DVERTEXBUFFER_DESC	m_VBDesc;
	D3DINDEXBUFFER_DESC		m_IBDesc;

	D3DXVECTOR3				m_pos;
	D3DXVECTOR3				m_rot;
	D3DXVECTOR3				m_Destination;
	D3DXMATRIXA16			m_matWorld;


public:
	MonsterCube();
	~MonsterCube();

	void Init();
	void Update();
	void Render();

	void SetVertex(vector<VERTEX_PC> &vecVertexOut,
		vector<WORD> &vecIndexOut, vector<D3DXVECTOR3> vecPos);
	void SetBuffer(LPDIRECT3DVERTEXBUFFER9 &pVb,
		LPDIRECT3DINDEXBUFFER9 &pIb,
		vector<VERTEX_PC> &vecVertex, vector<WORD> &vecIndex);
};