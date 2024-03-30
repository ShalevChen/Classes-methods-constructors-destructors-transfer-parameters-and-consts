#include "Account.h"

Account::Account()
{
	this->m_transactionList = nullptr;
	this->m_numberOfTransaction = 0;
	this->m_persons = nullptr;
	this->m_totalPersons = 0;
	this->m_accountNumber = 0;
	this->m_balance = 0; // סכום

}

Account::Account(Person** persons, int count, double balance)
{
	this->m_transactionList = nullptr;
	this->m_numberOfTransaction = 0;
	this->m_persons = nullptr; // לפני השמה , נאפס
	this->m_totalPersons = count;
	this->m_accountNumber = 0;
	this->m_balance = balance;
	
	

		SetPersons(persons, count); // השמה 
	for (int i = 0; i < m_totalPersons; i++)   // 
	{
		m_accountNumber = this->m_persons[i]->GetId();
	}

}

Account::Account(const Person& person, double balance)
{
	this->m_transactionList = nullptr;
	this->m_numberOfTransaction = 0;
	this->m_persons = nullptr; // לפני השמה , נאפס
	this->m_totalPersons = 1;
	this->m_balance = balance;
	this->m_accountNumber = person.GetId();
	

	m_persons = new Person * [1]; //    נקצא למערך גודל של 1 לפי נתון
	m_persons[0] = new Person(person);   // במקום האפס נשים את הבנאדם החדש
}

Account::Account(const Account& other)
{
	this->m_transactionList = nullptr;
	this->m_numberOfTransaction = other.m_numberOfTransaction;
	this->m_totalPersons = other.m_totalPersons;
	this->m_balance = other.m_balance;
	this->m_accountNumber = other.m_accountNumber;
	this->m_persons = nullptr; // לפני השמה , נאפס

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
	m_persons = new Person * [m_totalPersons];  // נשלח למערך של **  בנאדם * לפי כמות האנשים שיש

	for (int i = 0; i < m_totalPersons; ++i)
		m_persons[i] = new Person(*persons[i]);
//       *יש לנו אנשים ** מערך   , לכן אם נסתכל על איבר בודד זה עם כוכבית אחת    
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
		m_transactionList = new Transaction * [m_numberOfTransaction];  // מספר מעודכן למערך העברות 
		for (int i = 0; i < m_numberOfTransaction; i++)
		{
			m_transactionList[i] = new Transaction(*newTransaction[i]);            //השמה של כל העברה בנפרד 
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
		if (m_persons[i]->GetId()==newPerson.GetId() )  //  בודקים אם הבנאדם החדש כבר קיים  לפי מספר זהות -במידה וכן נצא מהפונקציה
 		{
			return;
		}
	}
	if (m_totalPersons==0 && m_persons==nullptr)  // אם אין אנשים בכלל וגם המערך ריק
	{
		m_persons = new Person * [1];//    נקצא למערך גודל של 1 לפי נתון

		m_persons[0] = new Person(newPerson);  // במקום האפס נשים את הבנאדם החדש
	}
	else
	{
		Person** myperson = new Person * [m_totalPersons + 1];   // נקצה מערך חדש עם מקום 1 נוסף
		for (int i = 0; i < m_totalPersons; i++)
		{
			myperson[i] = m_persons[i];  // נעביר את הישן לחדש
		}
		myperson[m_totalPersons] = new Person(newPerson);  // נאתחל את הבנאדם החדש בסוף המערך החדש
		delete[]m_persons;  // נמחק את הישן
		m_persons = myperson; // נעביר את המערך החדש לישן
	}
	m_totalPersons++;  // נגדיל את כמות הבני אדם
	m_balance += amount;    // נגדיל את האיזון
}

void Account::DeletePerson(const Person& oldPerson)
{
	int myindex = -5;
	for (int  i = 0; i < m_totalPersons; i++)  
	{
		if (m_persons[i]->GetId()==oldPerson.GetId())  //נבדוק האם הבנאדם שאנו מחפשים למחוק , נמצא במערך לפי מספר זהות
		{
			myindex = i;
			break;   // במידה ומגיע - יוצא מהלולאה 
		}
	}

	if (-5==myindex) //  במידה ולא מצאנו בנאדם שנרצה למחוק, האינדקס צריך להיות כפי שהגדרנו ולכן נצא מהפונקציה
	{
		return;
	}

	if (m_totalPersons==1) // שהמערך של האנשים בגודל 1 
	{
		delete m_persons[0];
		delete[] m_persons;

		m_persons = nullptr;
	}
	else
	{
		Person** myperson = new Person * [m_totalPersons - 1];  // פחות אדחד במערך
		int i;
		int k = 0;
		for ( i = 0; i < m_totalPersons; i++)
		{
			if (i != myindex)   // נעתיק למערך החדש את כולם חוץ מהבן אדם באינדקס שנרצה להסיר
			{
				myperson[k] = m_persons[i];
				k++;
			}
		}
		delete m_persons[myindex];
		delete[] m_persons;

		m_persons = myperson;  // נעתיק לאחר מחיקה

	}
	m_totalPersons--;  // נחסר בנאדם
}

void Account::AddTransaction(const Transaction& newTransaction)
{
	Account* src = newTransaction.GetSource();  // השולח
	Account* dst = newTransaction.GetDes();  // המקבל
	if (src != nullptr)
	{
		if (src->m_transactionList==nullptr) // אם ריק
		{
			src->m_transactionList = new Transaction * [1]; //נקצה העברה חדשה 1 
			src->m_transactionList[0] = new Transaction(newTransaction);
			src->m_numberOfTransaction++; // נגדיל את מספר ההעברות
		}
		else  // אם לא ריק , נעתיק הכל לחדש
		{
			Transaction** mytran = new Transaction*[src->m_numberOfTransaction+1];  // מערך העברות חדש
			for (int i = 0; i < src->m_numberOfTransaction; i++)
			{
				mytran[i] = src->m_transactionList[i];  // נעביר הכל מהישן לחדש
			}
			mytran[src->m_numberOfTransaction] = new Transaction(newTransaction);  // נעביר לסוף המערך החדש את ההעברה הנוספת החדשה

			delete src->m_transactionList;
			src->m_transactionList = mytran;
			src->m_numberOfTransaction++;
		}
		if (src==dst) // אם השולח והמקבל אותו אחד
		{
			src->m_balance += newTransaction.GetAmount();   // אם אותו אחד הכסף ישאר אותו הדבר
			return;
		}
		else
		{
			src->m_balance -= newTransaction.GetAmount();  //  אם לא אותו אחד -נוריד כסף מהשולח 
		}
	}
	if (dst != nullptr)  // אם המקבל לא ריק
	{
		if (dst->m_transactionList == nullptr)   // אם המערך של המקבל ריק
		{
			dst->m_transactionList = new Transaction * [1];  // נקצה מקום 1
			dst->m_transactionList[0] = new Transaction(newTransaction);
			dst->m_numberOfTransaction++;
		}
		else // אם המערך של המקבל לא ריק
		{
			Transaction** mytrann = new Transaction * [dst->m_numberOfTransaction + 1];  // מערך חדש +1 מקום של העברה חדשה
			for (int i = 0; i < dst->m_numberOfTransaction; i++)
			{
				mytrann[i] = dst->m_transactionList[i];  // התעקה מהישן לחדש
			}
			mytrann[dst->m_numberOfTransaction] = new Transaction(newTransaction);  // הוספה של העברה החדשה לסוף המערך
			delete[]dst->m_transactionList; // מחיקה מערך ישן
			dst->m_transactionList = mytrann;  // השמה את החדש לישן
			dst->m_numberOfTransaction++;  // הגדלה מספר העברות
		}
		dst->m_balance += newTransaction.GetAmount();  // הגדלת האיזון
	}
}

void Account::clearTransactions()
{
	if (m_transactionList)  // אם קיים
	{
		for (int i = 0; i < m_numberOfTransaction; i++)
		{
			delete m_transactionList[i];  // נעבור אחד אחד במערך ונמחוק
		}
		delete[]m_transactionList;  // לאחר מכן נמחוק את כל המערך עצמו
		m_transactionList = nullptr;
	}
}

void Account::clearPersons()
{
	if (m_persons)  // אם קיים המערך
	{
		for (int i = 0; i < m_totalPersons; i++)
		{
			delete m_persons[i];  // נעבור על אחד אחד במערך ונמחוק
		}
		delete[]m_persons;  // לאחר מכן נמחק את המערך עצמו
		m_persons = nullptr;
	}
}
