#include "account.h"
#include "exceptions.h"
using namespace std;


void Account::accountDisplay(void)
{
	cout << "------------------------" << endl;
	cout << "Your account:" << endl;
	cout << "ID: " << getAccountID() << "  ";
	cout << "name:  " << getName() << "  ";
	cout << "cash:  " << getCash() << endl;
	cout << "------------------------" << endl;
}

void Account::reset(void)
{
	cash = 0;
	accountID = -1;
	name = "";
}

Account::~Account(void)
{
	reset();
}

void Account::swap(Account & o)
{
	accountID = std::move(o.accountID);
	cash = std::move(o.cash);
	name = std::move(o.name);
}

Account & Account::operator = (Account && rhs) noexcept
{
	swap(rhs);
	return *this;
}

void Account::withdraw(double amount)
{
	if (amount > cash)
		 throw E("You don't have enough cash on your acccount");
	else
		cash -=amount;
}

void Account::deposit(double amount)
{
		cash +=amount;
}