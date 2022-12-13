#include "utest.h"
#include <string>
extern void doSomeTests(void)
{
    int tpass = 0, tfail = 0;
    Account x(1, 999, "Zosia");
    Account y(2, 1000, "Gosia");
    AccountTest u(x);
    printf("\nTesting some accounts \n");
    u.test("x != y",   (x != y));
    u.test("x == x",   (x == x));

    tpass += u.pass_count();
    tfail += u.fail_count();
    u.report();
    printf("\nTotals: pass: %d, fail: %d\n\n\n", tpass, tfail);
}

AccountTest::AccountTest(Account testObject) 
{
    init(testObject);
}

void AccountTest::init(Account testObject) 
{
    _testObject = move(testObject);
    _pass_count = _fail_count = 0;
}

void AccountTest::test ( const char * description, const int flag ) {
    const char * pf = nullptr;
    if (flag) {
        pf = _pstr;
        ++_pass_count;
    } else {
        pf = _fstr;
        ++_fail_count;
    }
    if(!_summary_flag) cout << _testObject << ": " << description << "->" << pf << endl;
}

void AccountTest::report() const 
{cout << _testObject <<  "  pass: " << pass_count() << "  fail: " << fail_count() << endl;}
    
