#include "../stdafx.h"
#include "DisplayObjManager.h"


DisplayObjManager::DisplayObjManager()
{
}


DisplayObjManager::~DisplayObjManager()
{
}

void DisplayObjManager::AddObject(IDisplayObject * Obj)
{
	m_AllObstacleList.insert(Obj);
}

void DisplayObjManager::RemoveObject(IDisplayObject * Obj, WORD tag)
{
	m_AllObstacleList.erase(Obj);

	vector<IDisplayObject*>::iterator iter;
	iter = find(m_ObstacleList[tag].begin(), m_ObstacleList[tag].end(), Obj);

	m_ObstacleList[tag].erase(iter);
}

void DisplayObjManager::AddObjectWithTag(IDisplayObject * Obj, WORD tag)
{
	// 업다면 추가
	if(m_AllObstacleList.find(Obj) == m_AllObstacleList.end())
		m_AllObstacleList.insert(Obj);

	m_ObstacleList[tag].push_back(Obj);
}


void DisplayObjManager::Destroy()
{
	m_AllObstacleList.clear();
}
