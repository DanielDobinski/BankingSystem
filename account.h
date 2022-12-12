#pragma once
#include <string>
#include <iostream>
using namespace std;

class Account
{
	int _accountID;
	double _cash;
	string _name;

	public:
	Account() {reset();};																	//default ctor
	Account(int id, double c, string n) : _accountID(id), _cash(c), _name(n) {}				//ctor
	Account(const Account & o) : _accountID(o._accountID), _cash(o._cash), _name(o._name) {}//copy ctor
	Account & operator = (Account && rhs) noexcept;											//copy assigment
	void swap(Account &);										
	~Account(void);																			//de-ctor
	void reset();

	//getters & setters
	int getAccountID(void) const {return _accountID;}
	double getCash(void) const {return _cash;}
	string getName(void) const {return _name;}
	void setAccountID(const int& accountID) {_accountID = accountID;}
	void setCash(const double& cash) {_cash = cash;}
	void etName(const string& name)  {_name = name;}

	//comparator
	bool operator==(Account const& e) const 
	{return _accountID == e._accountID;}
	bool operator!=(Account const& e) const 
	{return _accountID != e._accountID;}

	//functionalities
	void withdraw(double amount);
	void deposit(double amount);
};

ostream& operator<<(ostream& os, const Account& o);