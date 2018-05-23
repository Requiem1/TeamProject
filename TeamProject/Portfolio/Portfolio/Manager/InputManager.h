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
	// 변수 초기화
	void Init();
	/*
	    캐릭터의 이동, 키보드 I키와 F키 입력에 관한 처리
	*/
	void Update();
    /*
	   캐릭터의 이동 관련 변수 설정
	   첫번째 인자 -> 이동
	   두번째 인자 -> 회전
	   세번째 인자 -> 점프
	*/
	void SetPosition(D3DXVECTOR3 *_Pos,D3DXVECTOR3 *_Rot,bool * isJump);

	// 키보드 I키(L키 아님)입력 확인에 쓸 변수 설정
	void SetKeyboardInputI(bool * _InputI);
	// 키보드 F키 입력 확인에 쓸 변수 설정
	void SetKeyboardInputF(bool *_InputF);
	// (UI클래스 전용) 마우스 좌클릭 확인용 변수 설정
	void SetUIMouseLButton(bool * LButton);
	// (UI클래스 전용) 마우스 우클릭 확인용 변수 설정
	void SetUIMouseRButton(bool * RButton);

	// 캐릭터 전용 마우스 좌클릭 확인용 변수 설정
	void CharacterMouseLButton(bool * LButton);
	// 캐릭터 전용 마우스 우클릭 확인용 변수 설정
	void CharacterMouseRButton(bool * RButton);

	/*
	   마우스 입력 처리
	   각 마우스 DOWN메세지 입력시에 맞는 변수 true 설정
	   마우스 UP메세지가 발생하면 false
	*/
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


};