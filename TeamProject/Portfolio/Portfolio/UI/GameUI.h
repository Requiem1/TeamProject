#pragma once
#include "../Manager/IDisplayObject.h"
#include "IntroUIButton.h"

class Player;
class UIObject;

class GameUI :public IDisplayObject, public UIButtonDelegate
{
private:
	LPD3DXSPRITE m_pSprite;
	UIObject * m_pRootUI;
	LPD3DXFONT m_pFont;
	vector<Player*>	m_pPlayer;
	char m_text[128];
public:
	GameUI();
	~GameUI();


	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	// IntroUIButton��(��) ���� ��ӵ�
	virtual void OnClick(IntroUIButton * pSender) override;
	//void CharToWChar(const char* pstrSrc, wchar_t pwstrDest[]);
};