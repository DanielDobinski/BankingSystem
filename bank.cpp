/* Short description:
The banking system is using a fixed array size with following data:
ID, name, cash for each owner. ID is unique and created randomly.
You can:
- log in
- withdraw
- deposit
- see current account
- see all acounts
- see accounts' count
- transfer money
- create new account
    accountList is a singletone class which is mainly a list of accounts.
Created by Daniel Dobinski
*/ 

#include <cstdio>
#include <iostream>
#include "account.h"
#include "exceptions.h"
#include "accountList.h"
#include "utest.h"

using namespace std;

//static functions
static void showInstructions(void);
static void accountWithdraw(Account& o);
static void accountDeposit(Account& o);
static int accountLogin(void);
static void accountLoginMessage(Account& o); 
static string getName(void);
static void createAccounts(AccountList * l);

//Initialize pointer to zero so that it can be initialized in first call to getInstance
AccountList * AccountList::_instance = NULL;   //put to init Function
int main()
{
    AccountList *list = AccountList::getInstance();
    createAccounts(list);
    Account loggedAccount;
    string input;
    showInstructions();
    
    while(cin >> input)
    {
        try
        {
            if(input == "w")
            {   
                accountWithdraw(loggedAccount);
            }
            else if (input == "d")
            {
                accountDeposit(loggedAccount);
            }
            else if (input == "s")
            {
                cout << loggedAccount << endl;
            }
            else if (input == "c")
            {

                list->createAccount();
                loggedAccount = move(list->getNewAccount()); //RVO shall work
            }
            else if(input == "l")
            {   

                int loginID = accountLogin();
                if(loggedAccount.getAccountID() != -1)
                    list->reassignLoggedAccount(loggedAccount);
                loggedAccount = move(list->getAccount(loginID));     //RVO shall work
                accountLoginMessage(loggedAccount);
            }
            else if(input == "f")
            {   
                string name = getName();
                if(loggedAccount.getAccountID() != -1)
                    list->reassignLoggedAccount(loggedAccount);
                loggedAccount = move(list->getAccountbyName(name));  //RVO shall work
                accountLoginMessage(loggedAccount);
            }
            else if( input == "u")
            {
                list->displayAllAccounts();
            }
            else if( input == "t") 
            {
                list->tranfserMoney(gatherTransferInfo());
            }
            else if( input == "q") 
            {
                cout << "Accounts' count " << list->getAccountCount() << endl;;
            }
            else
            {
                cout << "invalid input";
            }

        }
        catch(E & e)
        {
            cout << "exception:";
            cout << e.what() << endl;

        }
        showInstructions(); 
    } //end of while
    return 0;
}

static void showInstructions(void)
{
    cout << "welcome to our banking system" << endl;
    cout << "press l to login" << endl;
    cout << "press w to withdraw" << endl;
    cout << "press d to deposit" << endl;
    cout << "press s to display" << endl;
    cout << "press c to create an Account" << endl;
    cout << "press f to find account and login" << endl;
    cout << "press u to display all acounts" << endl;
    cout << "press t to transfer money" << endl;
    cout << "press q to show accounts' count" << endl;
    cout << "------------------------" << endl;
}
static void accountWithdraw(Account& o)
{
    cout << "Withdraw: how much?" << endl;
    double amount;
    cin >> amount;
    if(o.getAccountID() != -1)
        o.withdraw(amount);
    else
        throw E("You need to log in first");
}
static void accountDeposit(Account& o)
{
    cout << "Deposit: how much?" << endl;
    double amount;
    cin >> amount;
     if(o.getAccountID() != -1)
        o.deposit(amount);
    else
        throw E("You need to log in first");
}

static int accountLogin(void)
{
    cout << "State your ID?" << endl;
    int loginID;
    cin >> loginID;
    return loginID;
}

static void accountLoginMessage(Account& o) //Change name
{
    cout << "Hi," << o.getName() << " " <<"You have logged in" << endl;
    cout << "------------------------" << endl;
}

static string getName(void)
{
    cout << "State name of account that you are looking for:" << endl;
    string name;
    cin >> name;
    return name;
}

static void createAccounts(AccountList * l)
{
    l->createAccount("Ola", 1000);
    l->createAccount("Daniel", 800);
    l->createAccount("Stanilaw", 2000);
    l->createAccount("ktos", 8000);
    l->createAccount("kaczka", 10000);
    doSomeTests();
}


