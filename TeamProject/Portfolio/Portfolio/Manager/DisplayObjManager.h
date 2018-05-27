#pragma once
#include <stdarg.h>
#define g_DisplayObjMgr DisplayObjManager::GetInstance()

class DisplayObjManager
{
	SINGLETON(DisplayObjManager);

private:
	set<IDisplayObject*> m_AllObstacleList;				// ��� ������Ʈ Ȯ��
	map<WORD, vector<IDisplayObject*>> m_ObstacleList;	// Ư�� TAG�� ������Ʈ Ȯ��

	bool isBoundingBoxRender;

public:

	void AddObject(IDisplayObject* Obj);
	void AddObjectWithTag(IDisplayObject* Obj, WORD tag);

	void RemoveObject(IDisplayObject* Obj);
	void RemoveObjectWithTag(IDisplayObject* Obj, WORD tag);
	void Destroy();

	set<IDisplayObject*> GetAllDisplayObjList() { return m_AllObstacleList; }
	vector<IDisplayObject*> GetDisplayObjListAtTag(WORD tag) { return m_ObstacleList[tag]; }

	// �浹 �˻� �Լ�!
	IDisplayObject * CollideCheckAllObjectFunc(IDisplayObject * myObj);
	IDisplayObject * CollideCheckWithTagFunc(IDisplayObject * myObj, int tag, ...);

	// �浹 �˻� -> �浹�ϰ� �ִ� ��� ��ü���� vector�� �־� 
	vector<IDisplayObject *> CollideCheckAllObject_ReturnVecFunc(IDisplayObject * myObj);
	vector<IDisplayObject *> CollideCheckWithTag_ReturnVecFunc(IDisplayObject * myObj, int tag, ...);

	void SetBoundingBoxRender() { isBoundingBoxRender = !isBoundingBoxRender; }
	bool GetBoundingBoxRender() { return isBoundingBoxRender; }
};


enum OBSTACLE_TAG
{
	PLAYER_TAG,
	ENEMY_TAG,
	BULLET_TAG,				// �Ѿ� Object
	NORMAL_OBSTACLE_TAG,	// �μ����� �ʴ� �Ϲ� Obstacle
	EXPLODE_OBSTACLE_TAG,	// �巳�� �� �����ϴ� Obstacle
	PLAYER_WALL_TAG,		// ����ڰ� ����� ��
	MAP_TAG					// ��
};

