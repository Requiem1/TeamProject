#include "../stdafx.h"
#include "InputManager.h"

InputManager::InputManager()
{

}
InputManager::~InputManager()
{

}

void InputManager::Init()
{
	Pos = NULL;
	Rot = NULL;
	InputI = false;
	InputF = false;

	LButtonDown = false;
	RButtonDown = false;
}

void InputManager::Update()
{
	if (GetKeyState('W') & 0x8000)
		Pos->z = 1;
	else if (GetKeyState('S') & 0x8000)
		Pos->z = -1;
	else
		Pos->z = 0;
    
	if (GetAsyncKeyState('A') & 0x8000)
	{
		Rot->y = -1;

	}

	else if (GetAsyncKeyState('D') & 0x8000)
		Rot->y = 1;
	else
		Rot->y = 0;

	if (GetAsyncKeyState('I') & 0x8000)
		InputI = true;
	else
		InputI = false;

	if (GetAsyncKeyState('F') & 0x8000)
		InputF = true;
	else
		InputF = false;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		IsJump = true;
	else
		IsJump = false;


}

void InputManager::SetPosition(D3DXVECTOR3 *_Pos, D3DXVECTOR3 *_Rot, bool * isJump)
{
	Pos = _Pos;
	Rot = _Rot;
	IsJump = *isJump;
}

void InputManager::SetKeyboardInputI(bool & _InputI)
{
	InputI = _InputI;
}

void InputManager::SetKeyboardInputF(bool & _InputF)
{
	InputF = _InputF;
}

void InputManager::SetMouseLButton(bool & LButton)
{
	LButtonDown = LButtonDown;
}

void InputManager::SetMouseRButton(bool & RButton)
{
	RButtonDown = RButtonDown;
}

void InputManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		LButtonDown = true;
		break;
	case WM_LBUTTONUP:
		LButtonDown = false;
		break;
	case WM_RBUTTONDOWN:
		RButtonDown = true;
		break;
	case WM_RBUTTONUP:
		RButtonDown = false;
		break;
	}
}
