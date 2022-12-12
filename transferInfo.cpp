#include "transferInfo.h"

void TransferInfo::reset(void)
{
	_fromAccountID = -1;
	_toAccountID = -1;
	_amount = -1;
}

TransferInfo::~TransferInfo(void)
{
	reset();
}

void TransferInfo::swap(TransferInfo & o)
{
	_fromAccountID = std::move(o._fromAccountID);
	_toAccountID = std::move(o._toAccountID);
	_amount = std::move(o._amount);
}

TransferInfo & TransferInfo::operator = (TransferInfo && rhs) noexcept
{
	swap(rhs);
	return *this;
}

TransferInfo gatherTransferInfo(void)
{
    int from;
    int to;
    double amount;
    cout << "state ID number of account that money will be taken FROM" << endl;
    cin >> from;
    cout << "state ID number of account that money will be taken TO" << endl;
    cin >> to;
    cout << "How much do you need to tranfser" << endl;
    cin >> amount; //try to catch if not enough money and message about success
    TransferInfo o(from, to, amount);
    return o;
}
