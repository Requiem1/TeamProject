#include "../stdafx.h"
#include "IntroUI.h"
#include "UIObject.h"
#include "UIImage.h"

enum
{
	UITAG_TEXTVIEW,
	UITAG_BUTTON1,
	UITAG_BUTTON2
};

IntroUI::IntroUI()
{
	m_pSprite = NULL;
	m_pRootUI = NULL;
}


IntroUI::~IntroUI()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pRootUI);
	m_pRootUI->ReleaseAll();

}

void IntroUI::Init()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);

	UIImage* pImage = new UIImage(m_pSprite);
	//pImage->SetTexture("UI/resources/panel-info.png.png");
	pImage->SetPosition(&D3DXVECTOR3(0, 0, 0));
	m_pRootUI = pImage;

	IntroUIButton * pButton = new IntroUIButton(this, m_pSprite);
	m_pRootUI->AddChild(pButton);
	pButton->SetPosition(&D3DXVECTOR3(135, 330, 0));
	pButton->SetTexture("UI/resources/START_Off.png", "UI/resources/START_On.png", "UI/resources/START_Off.png");


	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 0.7f, 0.7, 1);

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, -100, 240, 0);
	m_matWorld = matS * matT;
}

void IntroUI::Update()
{
	SAFE_UPDATE(m_pRootUI);
}

void IntroUI::Render()
{
	g_pDevice->SetTexture(0, NULL);
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->SetTransform(&m_matWorld);
	SAFE_RENDER(m_pRootUI);
	m_pSprite->End();
}

void IntroUI::OnClick(IntroUIButton * pSender)
{
}
