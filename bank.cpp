#include <cstdio>
#include <iostream>
#include "account.h"
#include "exceptions.h"
#include "accountList.h"

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
AccountList * AccountList::instance = NULL;   //put to init Function
int main()
{
    try
    {
        AccountList *list = AccountList::getInstance();
        createAccounts(list);
        Account loggedAccount;
        string ch;
        showInstructions();
        
        while(cin >> ch)
        {
            if(ch == "w")
            {   
                accountWithdraw(loggedAccount);
            }
            else if (ch == "d")
            {
                accountDeposit(loggedAccount);
            }
            else if (ch == "s")
            {
                loggedAccount.accountDisplay();
                showInstructions();
            }
            else if (ch == "c")
            {
                list->createAccount();
                loggedAccount = move(list->getNewAccount());
                showInstructions();
            }
            else if(ch == "l")
            {   
                int loginID = accountLogin();
                loggedAccount = move(list->getAccount(loginID));
                accountLoginMessage(loggedAccount);
                showInstructions();
            }
            else if(ch == "f")
            {   
                string name = getName();
                try
                {
                    list->reassignLoggedAccount(loggedAccount);
                    loggedAccount = move(list->findAccountID(name));
                    accountLoginMessage(loggedAccount);
                }
                catch (E & e)
                {
                    cout << e.what() << endl;
                }
                showInstructions(); 
            }
            else if( ch == "u")
            {
                list->displayAllAccounts();
                showInstructions(); 
            }
            else
            {
                cout << "invalid input";
            }
        }
    }
    catch(E & e)
    {
        cout << "exception:";
        cout << e.what() << endl;
    }
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
    cout << "------------------------" << endl;
}
static void accountWithdraw(Account& o)
{
    cout << "Withdraw: how much?" << endl;
    double amount;
    cin >> amount;
    o.withdraw(amount);
    showInstructions();
}
static void accountDeposit(Account& o)
{
    cout << "Deposit: how much?" << endl;
    double amount;
    cin >> amount;
    o.deposit(amount);
    showInstructions();
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
}


