#pragma once
#include "IScene.h"

class HeightMap;
class Player;

class SceneHeightMap : public IScene
{
private:
	HeightMap * S_HeightMap;
	Player * S_Player;

public:
	SceneHeightMap();
	~SceneHeightMap();

	// IScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

