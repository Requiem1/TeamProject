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

	bool m_bDrawBorder; // 카메라 앞에 보일지 말지, 렌더에서 사용


	UIObject(LPD3DXSPRITE pSprite);
	virtual~UIObject();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void DrawBorder();
	void UpdateCombinedPosition();// 부모와 자신의 포지션을 합친 카메라 포지션 구함
	void GetFinalRect(RECT* rect);
	const D3DXVECTOR3& GetCombinedPosition() { return m_combinedPos; }
};

