#include "accountList.h"
#include <ctime> 
#include <algorithm>

void AccountList::createAccount(void)
{
    cout << "I'm creating an account" << endl;
    cout << "Please, state your name" << endl;
    string name;
    cin >> name;

    if(accountCount >= NUMBER_OF_ACCOUNTS)
    {
        throw E("Maximum Number of Accounts Reached");
    }

    int randNumber = rand() % MAX_ACCOUNT_ID;
    Account createdAccount(randNumber, 0.0f, name);
    auto result = std::find(accountList, accountList + NUMBER_OF_ACCOUNTS, createdAccount);

    if (result == (accountList + NUMBER_OF_ACCOUNTS)) //if not found, iterator (pointer) points to the end.
    {
    	accountList[accountCount] = move(createdAccount); //RVO should work
    }
    else
    {
        while(result != (accountList + NUMBER_OF_ACCOUNTS)) //try to create a number until it's not present
        {
            randNumber = rand() % MAX_ACCOUNT_ID;
            Account createdAccount(randNumber, 0.0f, name);
            result = std::find(accountList, accountList + NUMBER_OF_ACCOUNTS, createdAccount);
        }
        accountList[accountCount] = move(createdAccount); //RVO should work
    }

    cout << "Thank you, " << name << ", your account has been set up" << endl;
    cout << "Your account ID is:" << randNumber << endl;
    cout << "------------------------" << endl;
    accountCount++;
}

Account AccountList::getNewAccount(void)
{
	if(this->isEmpty() == false)
		return (accountList[accountCount - 1]);
	else
		throw E("The List of accounts is empty, you cannot access any accounts");
}

bool AccountList::isEmpty(void)
{
	if(accountCount == 0)
		return true;
	else
		return false;
}
AccountList* AccountList::getInstance()
{
	if(instance == NULL)
	{
		instance = new AccountList;
	}
	srand((unsigned) time(NULL)); // could be done in some Init function
	return instance;
}

