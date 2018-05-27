#pragma once
#include "UIObject.h"
class UIText :
	public UIObject
{
public:
	LPD3DXFONT m_pFont;
	LPCTSTR m_text;
	DWORD  m_drawTextFormat;


	UIText(LPD3DXFONT m_pFont, LPD3DXSPRITE pSprite);
	virtual	~UIText();

	virtual void Render() override;
};
