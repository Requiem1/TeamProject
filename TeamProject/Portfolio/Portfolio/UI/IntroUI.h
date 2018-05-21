#pragma once
#include"../Manager\IDisplayObject.h"
#include "IntroUIButton.h"

class UIObject;

class IntroUI :public IDisplayObject , public UIButtonDelegate
{
private:
	LPD3DXSPRITE m_pSprite;
	UIObject * m_pRootUI;
public:
	IntroUI();
	~IntroUI();


	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	// IntroUIButton��(��) ���� ��ӵ�
	virtual void OnClick(IntroUIButton * pSender) override;
};

