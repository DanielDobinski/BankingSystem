#pragma once
#include "account.h"
#include "exceptions.h"
#include "transferInfo.h"

constexpr int NUMBER_OF_ACCOUNTS = 100;
constexpr int MAX_ACCOUNT_ID = 999;

class AccountList //singleton
{
	static AccountList* _instance;
	Account _accountList[NUMBER_OF_ACCOUNTS];
	int _accountCount = 0;
	int _loggedIndex = -1;     //used for logged Account
	AccountList() {};          //private Ctor

	public:
	static AccountList* getInstance();  		 			//static for without an object
	void reassignLoggedAccount(Account account); 			// copy values back to the list
	void AcccountReturnToList(Account account, int index); 
	void tranfserMoney(const TransferInfo& o);
	void createAccount(void);
	void createAccount(const string& name, const double& cash);
	Account getAccount(const int& ID) const;
	int getIndex(const int& ID) const;
	Account getAccountbyName(const string& owner); 
	Account getNewAccount(void); 
	void displayAllAccounts(void);
	int getAccountCount(void) const {return _accountCount;}
	bool isEmpty(void) const;
};



