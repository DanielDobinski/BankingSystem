#include "accountList.h"
#include <ctime> 
#include <algorithm>
#include <vector>

void AccountList::createAccount(void)
{
    cout << "I'm creating an account" << endl;
    cout << "Please, state your name" << endl;
    string name;
    cin >> name;

    this->createAccount(name, 0.0f);

    cout << "Thank you, " << name << ", your account has been set up" << endl;
    cout << "Your account ID is:" << (this->getNewAccount()).getAccountID() << endl;
    cout << "------------------------" << endl;
}
/*
    creates an account with random number. Checks multiple time if the account already exists
*/
void AccountList::createAccount(const string& name, const double& cash)
{
    if(_accountCount >= NUMBER_OF_ACCOUNTS)
    {
        throw E("Maximum Number of Accounts Reached");
    }
    int randNumber = rand() % MAX_ACCOUNT_ID;
    Account createdAccount(randNumber, cash, name);
    auto result = std::find(_accountList, _accountList + NUMBER_OF_ACCOUNTS, createdAccount);
    //Check if that ID already exists
    if (result == (_accountList + NUMBER_OF_ACCOUNTS)) //if not found, iterator (pointer) points to the end.
    {
        _accountList[_accountCount] = move(createdAccount); 
    }
    else
    {
        while(result != (_accountList + NUMBER_OF_ACCOUNTS)) //try to create a number until it's not present
        {
            randNumber = rand() % MAX_ACCOUNT_ID;
            Account createdAccount(randNumber, 0.0f, name);
            result = std::find(_accountList, _accountList + NUMBER_OF_ACCOUNTS, createdAccount);
        }
        _accountList[_accountCount] = move(createdAccount);
    }
    _loggedIndex = _accountCount;
    _accountCount++;
}

Account AccountList::getAccountbyName(const string& owner)
{
    Account account;
    vector<Account> v_account;
    vector<int> v_index;
    int count = 0;

    for (int i = 0; i < NUMBER_OF_ACCOUNTS ; i++)
    {   
        if(_accountList[i].getName() == owner)
        {
            v_account.push_back(_accountList[i]);
            v_index.push_back(i);
            ++count;
        }
    }
    if(count == 0)
        throw E("The account not found");
    else if (count == 1)
    {
        _loggedIndex = v_index[0];
        return v_account[0];
    }
    else
        {
            cout << "We have found " << count << " entries" << endl;
            cout << "which you want to see " << endl;
            int selection;
            cin >> selection;
            if ((selection <= count) && (selection >=0))
            {
                _loggedIndex = v_index[selection -1];
                return v_account[selection -1];
            }
            else
                throw E("We didn't say that many accounts exists");
        }
}

void AccountList::tranfserMoney(const TransferInfo& o)
{
    int indexFrom = getIndex(o.getfromAccountID());
    int indexTo = getIndex(o.getToAccountID());
    double amount = o.getAmount();
    Account fromAccount = move(_accountList[indexFrom]);;
    Account toAccount = move(_accountList[indexTo]);;

    if (fromAccount.getCash() >= amount)
    {
        toAccount.deposit(amount);
        fromAccount.withdraw(amount);
        AcccountReturnToList(toAccount, indexTo);
        AcccountReturnToList(fromAccount, indexFrom);
    }else
    {
        throw E("You do possess so much money to tranfser");
    }
}

void AccountList::displayAllAccounts(void) 
{
    for (auto o : _accountList)
    {   
        if(o.getAccountID() != -1)
            cout << o << endl;
    }
}

Account AccountList::getNewAccount(void)
{
	if(this->isEmpty() == false)
		return (_accountList[_accountCount - 1]);
	else
		throw E("The List of accounts is empty, you cannot access any accounts");
}

Account AccountList::getAccount(const int& ID) const
{
    for (auto o : _accountList)
    {   
        if(o.getAccountID() == ID)
        {
            return o;
            break;
        }
    }
    throw E("The account with given ID not found");
}

int AccountList::getIndex(const int& ID) const
{
   for (int i = 0; i < NUMBER_OF_ACCOUNTS ; i++)
    {   
        if(_accountList[i].getAccountID() == ID)
        {
            return i;
            break;
        }
    }
    throw E("The account with given ID not found, getIndex didn't work");
}

bool AccountList::isEmpty (void) const 
{
	if(_accountCount == 0)
		return true;
	else
		return false;
}
AccountList* AccountList::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new AccountList;
	}
	srand((unsigned) time(NULL)); // could be done in some Init function
	return _instance;
}

void AccountList::reassignLoggedAccount(Account account) 
{
    _accountList[_loggedIndex] = move(account);
}

void AccountList::AcccountReturnToList(Account account, int index) 
{
    _accountList[index] = move(account);
}

