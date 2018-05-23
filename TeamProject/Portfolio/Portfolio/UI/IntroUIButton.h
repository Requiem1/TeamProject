#pragma once
#include "UIObject.h"

class IntroUIButton;

class UIButtonDelegate
{
public:
	virtual void OnClick(IntroUIButton* pSender) = 0;
};


class IntroUIButton : public UIObject
{
private:
	enum ButtonState
	{
		MOUSE_ON, MOUSE_OFF,MOUSE_CLICKED,COUNT
	};
	ButtonState m_buttonState;
public:
	UIButtonDelegate *m_pDelegate;
	//COUNT 갯수만큼 상태에 따라 다르게 보이도록
	LPDIRECT3DTEXTURE9 m_aTexture[COUNT-1];

	IntroUIButton(UIButtonDelegate* pDelegate, LPD3DXSPRITE pSprite);
	virtual	~IntroUIButton();

	virtual void Update() override;
	virtual void Render() override;

	void SetTexture(string normal, string mouseOver, string selected);
	void SetText(LPD3DXFONT font, LPCTSTR text);
};

