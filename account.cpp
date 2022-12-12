#include "account.h"
#include "exceptions.h"
using namespace std;

ostream& operator<<(ostream& os, const Account& o)
{
    os << "Your account:  " << o.getAccountID() << "  name:  "  << o.getName() << "  cash:  " << o.getCash();
    return os;
}

void Account::reset(void)
{
	_cash = 0;
	_accountID = -1;
	_name = "";
}

Account::~Account(void)
{
	reset();
} 

void Account::swap(Account & o)
{
	_accountID = std::move(o._accountID);
	_cash = std::move(o._cash);
	_name = std::move(o._name);
}

Account & Account::operator = (Account && rhs) noexcept
{
	swap(rhs);
	return *this;
}

void Account::withdraw(double amount)
{
	if (amount > _cash)
		 throw E("You don't have enough cash on your acccount");
	else
		_cash -=amount;
}

void Account::deposit(double amount)
{
		_cash +=amount;
}