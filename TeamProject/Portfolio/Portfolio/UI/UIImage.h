#pragma once
#include "UIObject.h"

class UIImage :public UIObject
{
public:
	LPDIRECT3DTEXTURE9 m_pTex;


	UIImage(LPD3DXSPRITE pSprite, int uiTag = -1);
	virtual	~UIImage();

	virtual void Render()override;

	void SetTexture(string fullPath);

};

