#pragma once
#include "IMap.h"

class HeightMap : public IMap
{
protected:
	MTLTEX *	m_pMtlTex;
	LPD3DXMESH	m_pMesh;

	vector<D3DXVECTOR3> m_vecSurfaceVertex;

	D3DXVECTOR3 m_charPos;


public:
	HeightMap();
	virtual ~HeightMap();

	void Load(const char* fullPath, D3DXMATRIXA16* pMat = NULL);
	void SetMtlTex(D3DMATERIAL9 &mtl, LPDIRECT3DTEXTURE9 pTex);

	// IMap��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual bool GetHeight(OUT float & height, const D3DXVECTOR3 & pos) override;
	virtual bool CalcPickedPosition(D3DXVECTOR3 & vOut, WORD screenX, WORD screenY) override;

	// picking üũ ������ 5x5������ ������ �� ��ġ�� �̵��ϴ� �Լ�
	void SetSurface();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

