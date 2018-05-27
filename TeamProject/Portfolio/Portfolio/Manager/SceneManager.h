#pragma once

#define g_SceneMgr SceneManager::GetInstance()

class IScene;
class SceneHeightMap;

class SceneManager
{
private:
	SceneManager();
	~SceneManager();

public:
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}
	vector<IScene*> m_vecScene;

	IScene* m_pCurrScene;

	
	void Init();
	void Destroy();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetCurrentScene(size_t index);
};

