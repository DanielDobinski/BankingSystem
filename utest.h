#pragma once
#include <cstdio>
#include "account.h"

extern void doSomeTests(void);
constexpr const char * _pstr = "pass";
constexpr const char * _fstr = "fail";
constexpr bool summary_flag = true;

class AccountTest {
    Account _testObject;
    
    int _pass_count = 0;
    int _fail_count = 0;
    bool _summary_flag = false;
    
    AccountTest( AccountTest & );                   // no copy constructor
    AccountTest operator = ( AccountTest & );       // no assignment operator
    AccountTest(){}                            		// no default constructor
public:
    AccountTest(Account testObject);
    void init (Account testObject);
    bool summary ( bool flag ) { return _summary_flag = flag; }
    bool summary() { return _summary_flag; }
    int pass_count() const { return _pass_count; }
    int fail_count() const { return _fail_count; }
    void test ( const char * description, const int flag );
    void report() const;
};
