#include "Person.h"

Person::Person()  // áğàé áøéøú îçãì
{
	this->m_name =nullptr ;  // ä÷öàä ìëï ğùååä ìğàì áøéøú îçãì
	this->m_id = 0;
}

Person::Person(const char* name, int id) // áğàé òí àúçåì îùúğéí
{
	if (name) //  ğáãå÷ àí ìà ğàì
	{
		this->m_name = _strdup(name);  // ä÷öàä îäéøä åâí äòú÷ä ìàåáéé÷è ùì äîçì÷ä
	/*	m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);*/
		// ãøê àøåëä , ÷åãí î÷öéí î÷åí ìôé äîçøåæú äçãùä åàæ îòáéøéí ìàåééá÷è ùìğå
	}

	this->m_id = id;
}

Person::Person(const Person& other)  // áğàé ääòú÷ä
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
		delete this->m_name; // ğîç÷ ø÷ ä÷öàåú
	}
	//delete this->m_name; // ğîç÷ ø÷ ä÷öàåú 
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
