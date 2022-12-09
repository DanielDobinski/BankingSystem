#include <cstdio>
#include <iostream>
#include <ctime> 
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
static Account createAccount(int currentCount);

int main()
{
    try
    {
        Account accountList[NUMBER_OF_ACCOUNTS];
        Account loggedAccount;
        static int accountCount = 1;
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
                accountList[accountCount] = move(createAccount(accountCount)); //RVO should work
                loggedAccount = move(accountList[accountCount]);
                accountCount++;
                showInstructions();
            }
            else if(ch == "l")
            {   
                int loginID = accountLogin();
                loggedAccount = move(accountList[loginID]);
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

static Account createAccount(int currentCount)
{
    cout << "I'm creating an account" << endl;
    cout << "Please, state your name" << endl;
    string name;
    cin >> name;

    if(currentCount >= NUMBER_OF_ACCOUNTS)
    {
        throw E("Maximum Number of Accounts Reached");
    }
    static int flagStart = 0;
    if (flagStart == 0)
    {
        srand((unsigned) time(NULL));
        flagStart++;
    }

    int randNumber = rand() % MAX_ACCOUNT_ID;

    Account createdAccount(randNumber, 0.0f, name);

    cout << "Thank you, " << name << ", your account has been set up" << endl;
    cout << "Your account ID is:" << randNumber << endl;
    cout << "------------------------" << endl;
    return createdAccount;
}