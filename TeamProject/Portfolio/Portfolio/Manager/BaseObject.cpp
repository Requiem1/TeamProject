#include "../stdafx.h"
#include "BaseObject.h"


BaseObject::BaseObject()
	:m_refCount(1)
{
}

BaseObject::~BaseObject()
{
	assert(m_refCount <= 0 && "������ ������Ʈ �߿� ���� �������� ���� ������Ʈ�� �ֽ��ϴ�. Release�� �̿��� �����ؾ� �մϴ�.");
}

void BaseObject::AddRef()
{
	m_refCount++;
}

void BaseObject::Release()
{
	m_refCount--;
	if (m_refCount <= 0)
	{
		delete this;
	}
}
