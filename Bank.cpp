#include "Bank.h"

Bank::Bank()  // ����� �� ������� �� ������
{
	this->m_name = nullptr;
	this->m_account = nullptr;
	this->m_bankCode = 0;
	this->m_numbeOfAccounts = 0;
	this->m_totalBalance = 0;
}

Bank::Bank(const char* name, int code)
{
	if (m_name)
	{
		delete m_name;
	}
	this->m_name = _strdup(name);   // ����� ��� _
	this->m_account = nullptr;
	this->m_bankCode = code;
	this->m_numbeOfAccounts = 0;
	this->m_totalBalance = 0;
}

Bank::~Bank()
{
	if (m_name)
	{
		delete m_name;
	}
	for (int i = 0; i < m_numbeOfAccounts; i++)
	{
		delete m_account[i];
	}
	delete[] m_account;
}

void Bank::SetBankName(const char* name)
{
	if (m_name)
	{
		delete m_name;
	}
	m_name = _strdup(name);      // ����� ��� �� �����
}

void Bank::SetAccount(Account** account, int numbeOfAccounts)
{
	for (int i = 0; i < m_numbeOfAccounts; i++)
	{
		delete m_account[i];
	}
	delete[] m_account;

	m_totalBalance = 0;
	m_numbeOfAccounts = numbeOfAccounts;
	m_account = account;
	for (int i = 0; i < numbeOfAccounts; i++)
	{
		m_totalBalance += m_account[i]->GetBalance();
	}
}

void Bank::SetTotal(double total)
{
	m_totalBalance = total;
}

void Bank::SetCode(int code)
{
	m_bankCode = code;
}

const char* Bank::GetBankName() const
{
	return m_name;;
}

Account** Bank::GetAccounts() const
{
	return m_account;
}

int Bank::GetNumberOfAccounts() const
{
	return m_numbeOfAccounts;
}

double Bank::GetTotal() const
{
	return m_totalBalance;
}

int Bank::GetCode() const
{
	return m_bankCode;
}

void Bank::AddAccount(const Account& account)
{
	for (int i = 0; i < m_numbeOfAccounts; i++)
	{
		if (m_account[i]->GetAccountNumber()==account.GetAccountNumber())// �� �� ��� ��� ������ - ��� ��� ������ ��� ���� ���������
		{
			return;
		}
	}

	if (m_numbeOfAccounts==0)
	{
		m_account = new Account * [1];    // �� ����� ��� , ���� ���� ����� 1
		m_account[0] = new Account(account);  // ����� ����� 1 ����� ����
	}
	else
	{
		Account** myaccount = new Account * [m_numbeOfAccounts + 1];  // ���� ��� �� ��� ���� ������
		for (int i = 0; i < m_numbeOfAccounts; i++)
		{
			myaccount[i] = m_account[i];
		}
		myaccount[m_numbeOfAccounts] = new Account(account);
		delete[] m_account;
		m_account = myaccount;
	}

	m_numbeOfAccounts++;
	m_totalBalance += account.GetBalance();
}

void Bank::AddAccount(const Person& per, double amount)
{
	Person** p = new Person * [1];
	p[0] = new Person(per);
	AddAccount(Account(p, 1, amount));
}

void Bank::AddPerson(const Person& newPerson, const Account& account, double amount)
{
	for (int i = 0; i < m_numbeOfAccounts; i++)
	{
		if (m_account[i]->GetAccountNumber()==account.GetAccountNumber())   // ���� ����� �� ������ ���� ����� ����
		{
			int prev = m_account[i]->GetTotalPersons();
			m_account[i]->AddPerson(newPerson, amount); // ����� ����� ����� �� ������ ���� �� ����� 
			if (prev<m_account[i]->GetTotalPersons())
			{
				m_totalBalance += amount;
			}
			return;
		}
	}
	AddAccount(newPerson, amount);  //   �� ��� ����� ����� ���� ����� �� ������ ���
}

void Bank::DeleteAccount(const Account& account)
{
	int index = -1;
	for (int i = 0; i < m_numbeOfAccounts; i++)
	{
		if (m_account[i]->GetAccountNumber()==account.GetAccountNumber())// ���� ��� ����� ���� �� ������
		{
			index = i;
			break;    // ���� ������� ������� ����� ������ ����� ����� ���� !!
		}
	}
	if (index==-1)
	{
		return;   //   �� ����� ����� ����� ����� ���� , ��� ���� ����� ��� ���� ��� ��������
	}
	m_totalBalance -= m_account[index]->GetBalance();// ���� �� ���� �� ���� ����� ����� ����� ������ �����
	
	if (m_numbeOfAccounts==1)   // �� ����� ���� ����� ��� ���� ���� ��� �� �� ����� �������
	{
		delete m_account[0];
		delete[] m_account;
		m_account = nullptr;
	}
	else
	{
		Account** myaccount = new Account * [m_numbeOfAccounts - 1];  // ���� ��� ����� ��� ���� �� ������ 
		int k = 0;
		for (int i = 0; i < m_numbeOfAccounts; i++)
		{
			if (i!=index)   //  ����� ����� ���� �� ���� ��� ������ ����� ������ ����� ���� �����
			{
				myaccount[k] = m_account[i];
				k++;
			}
		}
		delete m_account[index];
		delete[] m_account;
		m_account = myaccount;
	}
	m_numbeOfAccounts--;   // ����� �� ���� ��������
}

void Bank::DeletePerson(const Person& p)
{
	int i = 0;
	while (i<m_numbeOfAccounts)
	{
		m_account[i]->DeletePerson(p);   // ���� �����
		if (m_account[i]->GetTotalPersons()==0)   // �� ������ ����� ����� ��� ����� - ���� �� ������ ���� -����� * ����� ������ ��� ����� ��� ����� ����� �� �����
		{
			DeleteAccount(*m_account[i]);
		}
		else
		{
			i++;
		}
	}

}
