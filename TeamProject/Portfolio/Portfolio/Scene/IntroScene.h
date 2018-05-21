#pragma once
#include "IScene.h"


class MonsterCube;

class IntroScene :public IScene
{
public:
	IntroScene();
	~IntroScene();

	vector<MonsterCube*> m_pMonsterCubeList;
	//MonsterCube* m_pMonsterCube;

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

