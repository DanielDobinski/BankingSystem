#include "accountList.h"


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
    static int flagStart = 0;
    if (flagStart == 0)
    {
        srand((unsigned) time(NULL));
        flagStart++;
    }
    int randNumber = rand() % MAX_ACCOUNT_ID;

    Account createdAccount(randNumber, 0.0f, name);
    accountList[accountCount] = move(createdAccount); //RVO should work
    cout << "Thank you, " << name << ", your account has been set up" << endl;
    cout << "Your account ID is:" << randNumber << endl;
    cout << "------------------------" << endl;
    accountCount++;
}