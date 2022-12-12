#pragma once
#include <string>
#include <iostream>
using namespace std;

class TransferInfo
{
	int _fromAccountID;
	int _toAccountID;
	double _amount;
	
	public:
	TransferInfo() {reset();};																		//default ctor
	TransferInfo(int from, int to, double a) : 														//ctor
	_fromAccountID(from), _toAccountID(to), _amount(a) {}												
	TransferInfo(const TransferInfo & o) : 															//copy ctor
	_fromAccountID(o._fromAccountID), _toAccountID(o._toAccountID), _amount(o._amount) {}  				
	TransferInfo & operator = (TransferInfo && rhs) noexcept;										//copy assigment
	void swap(TransferInfo &);										
	~TransferInfo(void);																			//de-ctor
	void reset();

	//getters & setters
	int getfromAccountID(void) const {return _fromAccountID;}
	int getToAccountID(void) const {return _toAccountID;}
	double getAmount(void) const {return _amount;}
	void setAccountID(const int& fromAccountID) {_fromAccountID = fromAccountID;}
	void setCash(const int& toAccountID) {_toAccountID = toAccountID;}
	void setName(const double& amount)  {_amount = amount;}
};

TransferInfo gatherTransferInfo(void);