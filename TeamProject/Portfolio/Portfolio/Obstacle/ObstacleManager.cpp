#include "stdafx.h"
#include "ObstacleManager.h"
#include "MapObstacle.h"


ObstacleManager::ObstacleManager()
{
}


ObstacleManager::~ObstacleManager()
{
}

void ObstacleManager::AddObstacle(MapObstacle * Ob, WORD tag)
{
	m_AllObstacleList.insert(Ob);

	m_ObstacleList[tag].push_back(Ob);
	Ob->SetObstacleIndex(m_ObstacleList[tag].size() - 1);
}

void ObstacleManager::RemoveObstacle(MapObstacle * Ob, WORD tag)
{
	m_AllObstacleList.erase(Ob);

	m_ObstacleList[tag].erase(m_ObstacleList[tag].begin() + Ob->GetObstacleIndex());
}

void ObstacleManager::Destroy()
{
	m_ObstacleList.clear();
}
