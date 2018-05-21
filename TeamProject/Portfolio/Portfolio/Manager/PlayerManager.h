#pragma once
#include "IDisplayObject.h"


#define g_pPlayerMGR  PlayerManager::GetInstance()

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
	void AddPlayer(Player* _Player)
	{
		_Player->SetTag(OTHERPLAYER);
		m_vecPlayer.push_back(_Player);
	}
	void Destory();
};

