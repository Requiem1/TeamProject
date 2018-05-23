#include "../stdafx.h"
#include "UIImage.h"


UIImage::UIImage(LPD3DXSPRITE pSprite, int uiTag) :UIObject(pSprite), m_pTex(NULL)
{
}

UIImage::~UIImage()
{
	SAFE_RELEASE(m_pTex);
}

void UIImage::Render()
{
	if (m_pTex)
	{
		RECT rect;
		//텍스쳐의 사이즈
		SetRect(&rect, 0, 0, m_size.x, m_size.y);

		m_pSprite->Draw(m_pTex, &rect, &m_pivot, &m_combinedPos, m_color);
	}
	// 루트가 호출해 주면 차일드에 렌더로 간다.
	UIObject::Render();
}

void UIImage::SetTexture(string fullPath)
{
	D3DXIMAGE_INFO info;
	m_pTex = g_pTextureManager->GetTexture(fullPath);
	D3DXGetImageInfoFromFileA(fullPath.c_str(), &info);
	m_size.x = info.Width;
	m_size.y = info.Height;
}
