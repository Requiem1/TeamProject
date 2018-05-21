#pragma once

#define g_ObstacleMgr ObstacleManager::GetInstance()

class IDisplayObject;
class MapObstacle;

class ObstacleManager
{
	SINGLETON(ObstacleManager);

private:
	set<MapObstacle*> m_AllObstacleList;			// ��� ������Ʈ Ȯ��
	map<WORD, vector<MapObstacle*>> m_ObstacleList; // Ư�� TAG�� ������Ʈ Ȯ��

public:

	void AddObstacle(MapObstacle* Ob, WORD tag);
	void RemoveObstacle(MapObstacle* Ob, WORD tag);
	void Destroy();

	set<MapObstacle*> GetAllObstacleList() { return m_AllObstacleList; }
	vector<MapObstacle*> GetObstacleListAtTag(WORD tag) { return m_ObstacleList[tag]; }
};

enum OBSTACLE_TAG
{
	NORMAL_OBSTACLE,	// �μ����� �ʴ� �Ϲ� Obstacle
	EXPLODE_OBSTACLE,	// �巳�� �� �����ϴ� Obstacle
	PLAYER_WALL			// ����ڰ� ����� ��
};