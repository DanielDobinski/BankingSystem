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

//Initialize pointer to zero so that it can be initialized in first call to getInstance
AccountList * AccountList::instance = NULL;   //put to init Function
int main()
{
    try
    {
        AccountList *list = AccountList::getInstance();
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

static void accountLoginMessage(Account& o)
{
    cout << "Hi," << o.getName() << "You have logged in" << endl;
    cout << "------------------------" << endl;
}

