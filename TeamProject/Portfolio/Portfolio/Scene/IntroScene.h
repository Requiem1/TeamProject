#pragma once
#include "IScene.h"



class IntroScene :public IScene
{
public:
	IntroScene();
	~IntroScene();

	// IScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

