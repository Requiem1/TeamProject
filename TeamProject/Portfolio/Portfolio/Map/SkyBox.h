#pragma once
#include "../Manager/IDisplayObject.h"

// ���� : http://egloos.zum.com/lsrsp/v/851394
// �̹��� ���� : https://www.quake3world.com/forum/viewtopic.php?t=9242

#define D3DFVF_SKYVERTEX (D3DFVF_XYZ | D3DFVF_TEX1)
#define MAX_SKY_TEX 6

struct SkyVertex
{
	float x, y, z, u, v;
};

class SkyBox : public IDisplayObject
{
private:
	LPDIRECT3DTEXTURE9			m_pTex[6];		// �ؽ�ó
	LPDIRECT3DVERTEXBUFFER9		m_pVB;			// ���ؽ� ����

public:
	SkyBox();
	~SkyBox();

private:
	void		_Destroy();
	void		_LoadTextures(const char* filePath, const char* fileName);
	void		_CreateVertex();

public:
	void		Create(const char* filePath, const char* fileName);

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};