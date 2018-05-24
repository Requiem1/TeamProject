#pragma once

#define g_DisplayObjMgr DisplayObjManager::GetInstance()

class DisplayObjManager
{
	SINGLETON(DisplayObjManager);

private:
	set<IDisplayObject*> m_AllObstacleList;				// 모든 오브젝트 확인
	map<WORD, vector<IDisplayObject*>> m_ObstacleList;	// 특정 TAG의 오브젝트 확인

public:

	void AddObject(IDisplayObject* Obj);
	void AddObjectWithTag(IDisplayObject* Obj, WORD tag);

	void RemoveObject(IDisplayObject* Obj);
	void RemoveObjectWithTag(IDisplayObject* Obj, WORD tag);
	void Destroy();

	set<IDisplayObject*> GetAllDisplayObjList() { return m_AllObstacleList; }
	vector<IDisplayObject*> GetDisplayObjListAtTag(WORD tag) { return m_ObstacleList[tag]; }
};


enum OBSTACLE_TAG
{
	PLAYER_TAG,
	ENEMY_TAG,
	NORMAL_OBSTACLE_TAG,	// 부서지지 않는 일반 Obstacle
	EXPLODE_OBSTACLE_TAG,	// 드럼통 등 폭발하는 Obstacle
	PLAYER_WALL_TAG,		// 사용자가 만드는 벽
	MAP_TAG					// 맵
};

