#include "../stdafx.h"
#include "IntroUIButton.h"




IntroUIButton::IntroUIButton(UIButtonDelegate * pDelegate, LPD3DXSPRITE pSprite)
	:UIObject(pSprite), m_pDelegate(pDelegate), m_buttonState(MOUSE_OFF)
{
}

IntroUIButton::~IntroUIButton()
{
}

void IntroUIButton::Update()
{
	UIObject::Update();

	//렉트에 버튼의 위치와 사이즈 값을 넣어줌
	RECT rect;
	GetFinalRect(&rect);

	POINT mousePoint;
	//윈도위 기준이 아닌 스크린 기준임
	GetCursorPos(&mousePoint);
	ScreenToClient(g_hWnd, &mousePoint);

	//마우스포인터가 버튼 영역 안에 있다면
	if (PtInRect(&rect, mousePoint))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{    //버튼위에 마우스가 올려진 상태라면
			if (m_buttonState == MOUSE_ON)
			{
				m_buttonState = MOUSE_CLICKED;
			}
		}
		else
		{
			if (m_buttonState == MOUSE_CLICKED)
			{
				if (m_pDelegate)
					m_pDelegate->OnClick(this);
			}
			m_buttonState = MOUSE_ON;
		}
	}
	else // 마우스 포인터가 버튼 영역 밖에 있을 때
	{//버튼을 누른상태에서 영역 밖으로 나갔을 경우  유지하기 위하여
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{

		}
		else
		{
			m_buttonState = MOUSE_OFF;
		}
	}

}

void IntroUIButton::Render()
{
	if (m_aTexture[m_buttonState])
	{
		RECT rect;
		SetRect(&rect, 0, 0, m_size.x, m_size.y);
		m_pSprite->Draw(m_aTexture[m_buttonState], &rect, &m_pivot, &m_combinedPos, m_color);
	}
	UIObject::Render();
}

void IntroUIButton::SetTexture(string normal, string mouseOver, string selected)
{
	/*D3DXIMAGE_INFO info;
	m_aTexture[MOUSE_OFF] = g_pTextureManager->GetTexture(normal);
	m_aTexture[MOUSE_ON] = g_pTextureManager->GetTexture(mouseOver);
	m_aTexture[MOUSE_CLICKED] = g_pTextureManager->GetTexture(selected);

	D3DXGetImageInfoFromFileA(normal.c_str(), &info);
	m_size.x = info.Width;
	m_size.y = info.Height;*/
}

void IntroUIButton::SetText(LPD3DXFONT font, LPCTSTR text)
{
}
