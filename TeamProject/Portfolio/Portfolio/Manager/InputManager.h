#pragma once

#define g_pINPUTMGR InputManager::GetInstance()

#define MAX_INPUT_MOUSE 8

class InputManager
{
	SINGLETON(InputManager)
private:
	D3DXVECTOR3 *Pos;
	D3DXVECTOR3 *Rot;

	bool *IsJump;

	bool *InputI;
	bool *InputF;

	bool *UILButtonDown;
	bool *UIRButtonDown;


	byte buttonStatus[MAX_INPUT_MOUSE];
	byte buttonOldStatus[MAX_INPUT_MOUSE];
	byte buttonMap[MAX_INPUT_MOUSE];

	enum INPUT_STATUS
	{
		BUTTON_INPUT_STATUS_NONE = 0,
		BUTTON_INPUT_STATUS_DOWN,
		BUTTON_INPUT_STATUS_UP,
		BUTTON_INPUT_STATUS_PRESS,
		BUTTON_INPUT_STATUS_DBLCLK
	};
	


public:
	// ���� �ʱ�ȭ
	void Init();
	/*
	    ĳ������ �̵�, Ű���� IŰ�� FŰ �Է¿� ���� ó��
	*/
	void Update();
    /*
	   ĳ������ �̵� ���� ���� ����
	   ù��° ���� -> �̵�
	   �ι�° ���� -> ȸ��
	   ����° ���� -> ����
	*/
	void SetPosition(D3DXVECTOR3 *_Pos,D3DXVECTOR3 *_Rot,bool * isJump);

	// Ű���� IŰ(LŰ �ƴ�)�Է� Ȯ�ο� �� ���� ����
	void SetKeyboardInputI(bool * _InputI);
	// Ű���� FŰ �Է� Ȯ�ο� �� ���� ����
	void SetKeyboardInputF(bool *_InputF);



	bool ButtonDown(DWORD button) { return buttonMap[button] == BUTTON_INPUT_STATUS_DOWN; }
	bool ButtonUp(DWORD button) { return buttonMap[button] == BUTTON_INPUT_STATUS_UP; }
	bool ButtonPress(DWORD button) { return buttonMap[button] == BUTTON_INPUT_STATUS_PRESS; }
	bool ButtonDB(DWORD button) { return buttonMap[button] == BUTTON_INPUT_STATUS_DBLCLK; }

	enum INPUT_TYPE
	{
		LBUTTON,
		RBUTTON,
		MBUTTON
	};


};