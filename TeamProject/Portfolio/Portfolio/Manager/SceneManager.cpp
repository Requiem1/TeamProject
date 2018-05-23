#include "../stdafx.h"
#include "SceneManager.h"
#include "../Scene/IScene.h"
#include "../Scene/IntroScene.h"
SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{

}

void SceneManager::Init()
{
	m_vecScene.push_back(new IntroScene());

	SetCurrentScene(SCENE_INTRO);
}

void SceneManager::Destroy()
{
	for (auto p : m_vecScene)
	{
		SAFE_RELEASE(p);
	}
}

void SceneManager::Update()
{
	SAFE_UPDATE(m_pCurrScene);
}

void SceneManager::Render()
{
	SAFE_RENDER(m_pCurrScene);
}

void SceneManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCurrScene)
		m_pCurrScene->WndProc(hWnd, message, wParam, lParam);
}

void SceneManager::SetCurrentScene(size_t index)
{
	if (index >= m_vecScene.size()) return;

	IScene* pScene = m_vecScene[index];
	if (pScene)
	{
		pScene->Init();
		m_pCurrScene = pScene;
	}
}
