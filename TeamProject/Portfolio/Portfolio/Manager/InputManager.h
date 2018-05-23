#pragma once

#define g_pINPUTMGR InputManager::GetInstance()


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

	bool *CharacterLButtonDown;
	bool *CharacterRButtonDown;
	


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
	// (UIŬ���� ����) ���콺 ��Ŭ�� Ȯ�ο� ���� ����
	void SetUIMouseLButton(bool * LButton);
	// (UIŬ���� ����) ���콺 ��Ŭ�� Ȯ�ο� ���� ����
	void SetUIMouseRButton(bool * RButton);

	// ĳ���� ���� ���콺 ��Ŭ�� Ȯ�ο� ���� ����
	void CharacterMouseLButton(bool * LButton);
	// ĳ���� ���� ���콺 ��Ŭ�� Ȯ�ο� ���� ����
	void CharacterMouseRButton(bool * RButton);

	/*
	   ���콺 �Է� ó��
	   �� ���콺 DOWN�޼��� �Է½ÿ� �´� ���� true ����
	   ���콺 UP�޼����� �߻��ϸ� false
	*/
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


};