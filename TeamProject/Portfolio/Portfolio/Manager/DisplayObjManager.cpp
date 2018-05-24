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

void DisplayObjManager::AddObjectWithTag(IDisplayObject * Obj, WORD tag)
{
	m_ObstacleList[tag].push_back(Obj);
}

void DisplayObjManager::RemoveObject(IDisplayObject * Obj)
{
	m_AllObstacleList.erase(Obj);
}

void DisplayObjManager::RemoveObjectWithTag(IDisplayObject * Obj, WORD tag)
{
	vector<IDisplayObject*>::iterator iter;
	iter = find(m_ObstacleList[tag].begin(), m_ObstacleList[tag].end(), Obj);

	m_ObstacleList[tag].erase(iter);
}

void DisplayObjManager::Destroy()
{
	m_AllObstacleList.clear();
}
