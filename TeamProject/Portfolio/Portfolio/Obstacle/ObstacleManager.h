#pragma once

#define g_ObstacleMgr ObstacleManager::GetInstance()

class IDisplayObject;
class MapObstacle;

class ObstacleManager
{
	SINGLETON(ObstacleManager);

private:
	set<MapObstacle*> m_AllObstacleList;			// 모든 오브젝트 확인
	map<WORD, vector<MapObstacle*>> m_ObstacleList; // 특정 TAG의 오브젝트 확인

public:

	void AddObstacle(MapObstacle* Ob, WORD tag);
	void RemoveObstacle(MapObstacle* Ob, WORD tag);
	void Destroy();

	set<MapObstacle*> GetAllObstacleList() { return m_AllObstacleList; }
	vector<MapObstacle*> GetObstacleListAtTag(WORD tag) { return m_ObstacleList[tag]; }
};

enum OBSTACLE_TAG
{
	NORMAL_OBSTACLE,	// 부서지지 않는 일반 Obstacle
	EXPLODE_OBSTACLE,	// 드럼통 등 폭발하는 Obstacle
	PLAYER_WALL			// 사용자가 만드는 벽
};