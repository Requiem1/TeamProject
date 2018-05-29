#include "../stdafx.h"
#include "DisplayObjManager.h"


DisplayObjManager::DisplayObjManager()
{
	isBoundingBoxRender = false;
}


DisplayObjManager::~DisplayObjManager()
{
	Destroy();
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
	m_ObstacleList.clear();
}

IDisplayObject * DisplayObjManager::CollideCheckAllObjectFunc(IDisplayObject * myObj)
{
	// �ٿ�� �ڽ� �浹 �˻�!
	// BSP�� �̿��� �������ҷ� �浹üũ�� �ؾߵ�����
	// �ϴ��� objManager�� ��ü��� ��� �浹üũ�� �������� �Ѵ�
	for (auto p : m_AllObstacleList)
	{
		if (p == myObj)
			continue;
	
		// Collision Detection Test!
		int nRet = BoxBoxIntersectionTest(*(myObj->GetCBox()), *(p->GetCBox()));
	
		// ���� ó�� �浹�� �ϳ��� ���� ��ȯ�Ѵ�
		if (nRet == 1)
		{
			return p;
		}
	}
	
	return NULL;
}

IDisplayObject * DisplayObjManager::CollideCheckWithTagFunc(IDisplayObject * myObj, int tagNum, ...)
{
	// �������ڸ� �̿��Ͽ� �������� Tag�� �޴´�
	va_list argList;
	va_start(argList, tagNum);

	// �ٿ�� �ڽ� �浹 �˻�!
	// BSP�� �̿��� �������ҷ� �浹üũ�� �ؾߵ�����
	// �ϴ��� objManager�� ��ü��� ��� �浹üũ�� �������� �Ѵ�
	for (auto p : m_ObstacleList[va_arg(argList, WORD)])
	{
		if (p == myObj)
			continue;

		// Collision Detection Test!
		int nRet = BoxBoxIntersectionTest(*(myObj->GetCBox()), *(p->GetCBox()));

		// ���� ó�� �浹�� �ϳ��� ���� ��ȯ�Ѵ�
		if (nRet == 1)
		{
			va_end(argList);
			return p;
		}
	}

	va_end(argList);

	return NULL;
}


vector<IDisplayObject *> DisplayObjManager::CollideCheckAllObject_ReturnVecFunc(IDisplayObject * myObj)
{
	vector<IDisplayObject *> vec;

	// �ٿ�� �ڽ� �浹 �˻�!
	// BSP�� �̿��� �������ҷ� �浹üũ�� �ؾߵ�����
	// �ϴ��� objManager�� ��ü��� ��� �浹üũ�� �������� �Ѵ�
	for (auto p : m_AllObstacleList)
	{
		if (p == myObj)
			continue;

		// Collision Detection Test!
		int nRet = BoxBoxIntersectionTest(*(myObj->GetCBox()), *(p->GetCBox()));

		// �浹�� ��ü���� vecter�� �����Ѵ�
		if (nRet == 1)
		{
			vec.push_back(p);
		}
	}

	// ���͸� ��ȯ�Ѵ�
	return vec;
}

vector<IDisplayObject *> DisplayObjManager::CollideCheckWithTag_ReturnVecFunc(IDisplayObject * myObj, int tag, ...)
{
	vector<IDisplayObject *> vec;

	// �������ڸ� �̿��Ͽ� �������� Tag�� �޴´�
	va_list argList;
	va_start(argList, tag);

	// �ٿ�� �ڽ� �浹 �˻�!
	// BSP�� �̿��� �������ҷ� �浹üũ�� �ؾߵ�����
	// �ϴ��� objManager�� ��ü��� ��� �浹üũ�� �������� �Ѵ�
	for (auto p : m_ObstacleList[va_arg(argList, int)])
	{
		if (p == myObj)
			continue;

		// Collision Detection Test!
		int nRet = BoxBoxIntersectionTest(*(myObj->GetCBox()), *(p->GetCBox()));

		// �浹�� ��ü���� vecter�� �����Ѵ�
		if (nRet == 1)
		{
			vec.push_back(p);
		}
	}

	va_end(argList);

	// ���͸� ��ȯ�Ѵ�
	return vec;
}
