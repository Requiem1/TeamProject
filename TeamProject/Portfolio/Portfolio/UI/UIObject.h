#pragma once
#include "../Manager/IDisplayObject.h"
class UIObject :public IDisplayObject
{
protected:
	LPD3DXSPRITE m_pSprite;
public:
	D3DXVECTOR3 m_combinedPos;
	D3DXVECTOR3 m_pivot;
	D3DXVECTOR3 m_size;
	D3DCOLOR	m_color;

	bool m_bDrawBorder; // ī�޶� �տ� ������ ����, �������� ���


	UIObject(LPD3DXSPRITE pSprite);
	virtual~UIObject();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void DrawBorder();
	void UpdateCombinedPosition();// �θ�� �ڽ��� �������� ��ģ ī�޶� ������ ����
	void GetFinalRect(RECT* rect);
	const D3DXVECTOR3& GetCombinedPosition() { return m_combinedPos; }
};

