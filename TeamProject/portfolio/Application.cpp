#include "stdafx.h"
#include "Application.h"


Application::Application()
{
}


Application::~Application()
{
}

void Application::Init()
{
	g_pDeviceManager->Init();
	g_pCamera->Init();
}

void Application::Destroy()
{
	g_pDeviceManager->Destroy();
}

void Application::Update()
{
	g_pCamera->Update();
}

void Application::Render()
{
	g_pDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(50, 50, 50), 1.0f, 0);

	g_pDevice->BeginScene();

	

	g_pDevice->EndScene();
	g_pDevice->Present(NULL, NULL, NULL, NULL);
}

void Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_pCamera->WndProc(hWnd, message, wParam, lParam);
}
