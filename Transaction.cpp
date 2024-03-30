#include "Transaction.h"

Transaction::Transaction(Account* s, Account* d, double amount, const char* date)  // נאתחל את המשתנים של המחלקה
{
	this->m_source = s;
	this->m_destination = d;
	this->m_amount = amount;
	/*if (m_date)
	{
		delete m_date;
	}*/
	this->m_date = _strdup(date);
}

Transaction::Transaction(const Transaction& other)
{
	this->m_source = other.m_source;
	this->m_destination = other.m_destination;
	this->m_amount = other.m_amount;
	if (m_date)
	{
		delete m_date;
	}
	this->m_date = _strdup(other.m_date);
}

void Transaction::SetSource(Account* src)
{
	this->m_source = src;
}

void Transaction::SetDes(Account* dst)
{
	this->m_destination = dst;
}

void Transaction::SetAmount(double amount)
{
	this->m_amount = amount;
}

void Transaction::SetDate(const char* date)
{
	if (m_date)
	{
		delete m_date;
	}
	this->m_date = _strdup(date);
}

Account* Transaction::GetSource() const
{
	return m_source;
}

Account* Transaction::GetDes() const
{
	return m_destination;
}

double Transaction::GetAmount() const
{
	return m_amount;
}

char* Transaction::GetDate() const
{
	return m_date;
}
