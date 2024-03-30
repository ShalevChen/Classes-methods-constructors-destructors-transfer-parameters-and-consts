#include "Person.h"

Person::Person()  // ���� ����� ����
{
	this->m_name =nullptr ;  // ����� ��� ����� ���� ����� ����
	this->m_id = 0;
}

Person::Person(const char* name, int id) // ���� �� ����� ������
{
	if (name) //  ����� �� �� ���
	{
		this->m_name = _strdup(name);  // ����� ����� ��� ����� �������� �� ������
	/*	m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);*/
		// ��� ����� , ���� ����� ���� ��� ������� ����� ��� ������� �������� ����
	}

	this->m_id = id;
}

Person::Person(const Person& other)  // ���� ������
{
	this->m_id = other.m_id;
	if (other.m_name)
	{
		this->m_name = _strdup(other.m_name);
	}

}

Person::~Person()
{
	//delete this->m_id;
	if (m_name)
	{
		delete this->m_name; // ���� �� ������
	}
	//delete this->m_name; // ���� �� ������ 
//	free(m_name);
}

void Person::SetName(const char* newName)
{
	if (newName)
	{
		delete m_name;
		this->m_name = _strdup(newName);
	}
}

void Person::SetId(int newId)
{
	this->m_id = newId;
}

char* Person::GetName() const
{
	return this->m_name;
}

int Person::GetId() const
{
	return this->m_id;
}
