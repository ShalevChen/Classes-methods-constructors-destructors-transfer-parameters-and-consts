#include "Account.h"

Account::Account()
{
	this->m_transactionList = nullptr;
	this->m_numberOfTransaction = 0;
	this->m_persons = nullptr;
	this->m_totalPersons = 0;
	this->m_accountNumber = 0;
	this->m_balance = 0; // ����

}

Account::Account(Person** persons, int count, double balance)
{
	this->m_transactionList = nullptr;
	this->m_numberOfTransaction = 0;
	this->m_persons = nullptr; // ���� ���� , ����
	this->m_totalPersons = count;
	this->m_accountNumber = 0;
	this->m_balance = balance;
	
	

		SetPersons(persons, count); // ���� 
	for (int i = 0; i < m_totalPersons; i++)   // 
	{
		m_accountNumber = this->m_persons[i]->GetId();
	}

}

Account::Account(const Person& person, double balance)
{
	this->m_transactionList = nullptr;
	this->m_numberOfTransaction = 0;
	this->m_persons = nullptr; // ���� ���� , ����
	this->m_totalPersons = 1;
	this->m_balance = balance;
	this->m_accountNumber = person.GetId();
	

	m_persons = new Person * [1]; //    ���� ����� ���� �� 1 ��� ����
	m_persons[0] = new Person(person);   // ����� ���� ���� �� ������ ����
}

Account::Account(const Account& other)
{
	this->m_transactionList = nullptr;
	this->m_numberOfTransaction = other.m_numberOfTransaction;
	this->m_totalPersons = other.m_totalPersons;
	this->m_balance = other.m_balance;
	this->m_accountNumber = other.m_accountNumber;
	this->m_persons = nullptr; // ���� ���� , ����

	SetTransactions(other.m_transactionList, other.m_numberOfTransaction);
	SetPersons(other.m_persons, other.m_totalPersons);
}

Account::~Account()
{
	clearTransactions();
	clearPersons();

}

void Account::SetPersons(Person** persons, int count)
{
	clearPersons();
	//delete[] persons;
	m_totalPersons = count;
	m_persons = new Person * [m_totalPersons];  // ���� ����� �� **  ����� * ��� ���� ������ ���

	for (int i = 0; i < m_totalPersons; ++i)
		m_persons[i] = new Person(*persons[i]);
//       *�� ��� ����� ** ����   , ��� �� ����� �� ���� ���� �� �� ������ ���    
}

void Account::SetAccountNumber(int number)
{
	this->m_accountNumber = number;
}

void Account::SetBalance(double balance)
{
	this->m_balance = balance;
}

void Account::SetTransactions(Transaction** newTransaction, int count)
{
	clearTransactions();
	this->m_numberOfTransaction = count;
	if (m_numberOfTransaction > 0)
	{
		m_transactionList = new Transaction * [m_numberOfTransaction];  // ���� ������ ����� ������ 
		for (int i = 0; i < m_numberOfTransaction; i++)
		{
			m_transactionList[i] = new Transaction(*newTransaction[i]);            //���� �� �� ����� ����� 
		}
	}

}

Transaction** Account::GetTransactions()
{
	return m_transactionList;
}

int Account::GetNumOfTransactions()
{
	return m_numberOfTransaction;
}

Person** Account::GetPersons() const
{
	return m_persons;
}

int Account::GetTotalPersons() const
{
	return m_totalPersons;
}

int Account::GetAccountNumber() const
{
	return m_accountNumber;
}

double Account::GetBalance() const
{
	return m_balance;
}

void Account::Withdraw(double amount, const char* date)
{
	AddTransaction(Transaction(this, this, -amount, date));

}

void Account::Deposit(double amount, const char* date)
{
	AddTransaction(Transaction(this, this, +amount, date));
}

void Account::AddPerson(const Person& newPerson, double amount)
{
	for (int i = 0; i < m_totalPersons; i++)
	{
		if (m_persons[i]->GetId()==newPerson.GetId() )  //  ������ �� ������ ���� ��� ����  ��� ���� ���� -����� ��� ��� ���������
 		{
			return;
		}
	}
	if (m_totalPersons==0 && m_persons==nullptr)  // �� ��� ����� ���� ��� ����� ���
	{
		m_persons = new Person * [1];//    ���� ����� ���� �� 1 ��� ����

		m_persons[0] = new Person(newPerson);  // ����� ���� ���� �� ������ ����
	}
	else
	{
		Person** myperson = new Person * [m_totalPersons + 1];   // ���� ���� ��� �� ���� 1 ����
		for (int i = 0; i < m_totalPersons; i++)
		{
			myperson[i] = m_persons[i];  // ����� �� ���� ����
		}
		myperson[m_totalPersons] = new Person(newPerson);  // ����� �� ������ ���� ���� ����� ����
		delete[]m_persons;  // ���� �� ����
		m_persons = myperson; // ����� �� ����� ���� ����
	}
	m_totalPersons++;  // ����� �� ���� ���� ���
	m_balance += amount;    // ����� �� ������
}

void Account::DeletePerson(const Person& oldPerson)
{
	int myindex = -5;
	for (int  i = 0; i < m_totalPersons; i++)  
	{
		if (m_persons[i]->GetId()==oldPerson.GetId())  //����� ��� ������ ���� ������ ����� , ���� ����� ��� ���� ����
		{
			myindex = i;
			break;   // ����� ����� - ���� ������� 
		}
	}

	if (-5==myindex) //  ����� ��� ����� ����� ����� �����, ������� ���� ����� ��� ������� ���� ��� ���������
	{
		return;
	}

	if (m_totalPersons==1) // ������ �� ������ ����� 1 
	{
		delete m_persons[0];
		delete[] m_persons;

		m_persons = nullptr;
	}
	else
	{
		Person** myperson = new Person * [m_totalPersons - 1];  // ���� ���� �����
		int i;
		int k = 0;
		for ( i = 0; i < m_totalPersons; i++)
		{
			if (i != myindex)   // ����� ����� ���� �� ���� ��� ���� ��� ������� ����� �����
			{
				myperson[k] = m_persons[i];
				k++;
			}
		}
		delete m_persons[myindex];
		delete[] m_persons;

		m_persons = myperson;  // ����� ���� �����

	}
	m_totalPersons--;  // ���� �����
}

void Account::AddTransaction(const Transaction& newTransaction)
{
	Account* src = newTransaction.GetSource();  // �����
	Account* dst = newTransaction.GetDes();  // �����
	if (src != nullptr)
	{
		if (src->m_transactionList==nullptr) // �� ���
		{
			src->m_transactionList = new Transaction * [1]; //���� ����� ���� 1 
			src->m_transactionList[0] = new Transaction(newTransaction);
			src->m_numberOfTransaction++; // ����� �� ���� �������
		}
		else  // �� �� ��� , ����� ��� ����
		{
			Transaction** mytran = new Transaction*[src->m_numberOfTransaction+1];  // ���� ������ ���
			for (int i = 0; i < src->m_numberOfTransaction; i++)
			{
				mytran[i] = src->m_transactionList[i];  // ����� ��� ����� ����
			}
			mytran[src->m_numberOfTransaction] = new Transaction(newTransaction);  // ����� ���� ����� ���� �� ������ ������ �����

			delete src->m_transactionList;
			src->m_transactionList = mytran;
			src->m_numberOfTransaction++;
		}
		if (src==dst) // �� ����� ������ ���� ���
		{
			src->m_balance += newTransaction.GetAmount();   // �� ���� ��� ���� ���� ���� ����
			return;
		}
		else
		{
			src->m_balance -= newTransaction.GetAmount();  //  �� �� ���� ��� -����� ��� ������ 
		}
	}
	if (dst != nullptr)  // �� ����� �� ���
	{
		if (dst->m_transactionList == nullptr)   // �� ����� �� ����� ���
		{
			dst->m_transactionList = new Transaction * [1];  // ���� ���� 1
			dst->m_transactionList[0] = new Transaction(newTransaction);
			dst->m_numberOfTransaction++;
		}
		else // �� ����� �� ����� �� ���
		{
			Transaction** mytrann = new Transaction * [dst->m_numberOfTransaction + 1];  // ���� ��� +1 ���� �� ����� ����
			for (int i = 0; i < dst->m_numberOfTransaction; i++)
			{
				mytrann[i] = dst->m_transactionList[i];  // ����� ����� ����
			}
			mytrann[dst->m_numberOfTransaction] = new Transaction(newTransaction);  // ����� �� ����� ����� ���� �����
			delete[]dst->m_transactionList; // ����� ���� ���
			dst->m_transactionList = mytrann;  // ���� �� ���� ����
			dst->m_numberOfTransaction++;  // ����� ���� ������
		}
		dst->m_balance += newTransaction.GetAmount();  // ����� ������
	}
}

void Account::clearTransactions()
{
	if (m_transactionList)  // �� ����
	{
		for (int i = 0; i < m_numberOfTransaction; i++)
		{
			delete m_transactionList[i];  // ����� ��� ��� ����� ������
		}
		delete[]m_transactionList;  // ���� ��� ����� �� �� ����� ����
		m_transactionList = nullptr;
	}
}

void Account::clearPersons()
{
	if (m_persons)  // �� ���� �����
	{
		for (int i = 0; i < m_totalPersons; i++)
		{
			delete m_persons[i];  // ����� �� ��� ��� ����� ������
		}
		delete[]m_persons;  // ���� ��� ���� �� ����� ����
		m_persons = nullptr;
	}
}
