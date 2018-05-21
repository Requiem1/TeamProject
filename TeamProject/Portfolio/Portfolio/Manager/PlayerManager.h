#pragma once
#include "IDisplayObject.h"
#define g_pPLAYERMGR   PlayerManager::GetInstance()

class PlayerManager
{
	SINGLETON(PlayerManager)
private:
	vector<Player*> m_vecPlayer;
public:
	void init();
	void Update();
	void Render();

	// �������� �޾ƿ� �����͸� ���� �ش� �Լ��� ȣ���Ѵ�.
	// ����� ������ ���� ������ ȣ������ �ʴ´�.
	void AddPlayer(Player* Player)
	{
		m_vecPlayer.push_back(Player);
	}
	void Destory();
};

