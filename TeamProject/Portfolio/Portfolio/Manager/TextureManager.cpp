#include "../stdafx.h"
#include "TextureManager.h"


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
	for (auto it : m_mapTexture)
	{
		SAFE_RELEASE(it.second);
	}
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(char * fullPath)
{
	if (fullPath == NULL) return NULL;

	return GetTexture(string(fullPath));
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(string fullPath)
{
	if (fullPath == "") return NULL;

	if (m_mapTexture.find(fullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFileA(g_pDevice, fullPath.c_str(),
			&m_mapTexture[fullPath]);
	}
	return m_mapTexture[fullPath];
}

LPDIRECT3DTEXTURE9 TextureManager::GetTextureEx(string fullPath)
{
	if (fullPath == "") return NULL;

	if (m_mapTexture.find(fullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFileExA(
			g_pDevice, fullPath.c_str(),
			0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, 
			D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR(0), NULL,
			NULL, &m_mapTexture[fullPath]);
		
	}
	return m_mapTexture[fullPath];
}

void TextureManager::Destroy()
{
	for (auto it : m_mapTexture)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapTexture.clear();
}
