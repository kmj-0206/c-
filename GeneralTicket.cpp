#include "GeneralTicket.h"

void GeneralTicket::show() const
{
	string str = payByCredit ? ("true") : ("false");
	cout << "티켓 번호 : " << getNumber() << endl;
	cout << "가격 정보 : " << getPrice() << endl;
	cout << "카드결제여부 :" << str << endl;
	cout << "지불금액 :";
	if (payByCredit)
		cout << getPrice() * 1.1 << endl;
	else
		cout << getPrice() << endl;
}

GeneralTicket::GeneralTicket(double price, bool payByCredit) : Ticket(price)
{
	this->payByCredit = payByCredit;
}

double GeneralTicket::getPrice() const
{
	return this->price;
}

bool GeneralTicket::getPayByCredit() const
{
	return this->payByCredit;
}
