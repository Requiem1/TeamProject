#pragma once

#define g_DisplayObjMgr DisplayObjManager::GetInstance()

class DisplayObjManager
{
	SINGLETON(DisplayObjManager);

private:
	set<IDisplayObject*> m_AllObstacleList;				// ��� ������Ʈ Ȯ��
	map<WORD, vector<IDisplayObject*>> m_ObstacleList;	// Ư�� TAG�� ������Ʈ Ȯ��

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
	NORMAL_OBSTACLE_TAG,	// �μ����� �ʴ� �Ϲ� Obstacle
	EXPLODE_OBSTACLE_TAG,	// �巳�� �� �����ϴ� Obstacle
	PLAYER_WALL_TAG,		// ����ڰ� ����� ��
	MAP_TAG					// ��
};

