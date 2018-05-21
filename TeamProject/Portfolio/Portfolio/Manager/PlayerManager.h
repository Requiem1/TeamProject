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

	// 서버에서 받아온 데이터를 통해 해당 함수를 호출한다.
	// 현재는 서버가 없기 때문에 호출하지 않는다.
	void AddPlayer(Player* _Player)
	{
		_Player->SetTag(OTHERPLAYER);
		m_vecPlayer.push_back(_Player);
	}
	void Destory();
};

