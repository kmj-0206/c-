#include "AdvancedTicket.h"

AdvancedTicket::AdvancedTicket(double price, int advanceDays) :Ticket(price)
{
	this->advanceDays = advanceDays;
	
}

double AdvancedTicket::getPrice() const
{
	if (this->getAdvanceDays() > 29)
		return this->price * 0.5;
	else if (this->getAdvanceDays() > 19)
		return this->price * 0.7;
	else if (this->getAdvanceDays() > 9)
		return this->price * 0, 9;
	else
		return this->price;
}

int AdvancedTicket::getAdvanceDays() const
{
    return this->advanceDays;
}

void AdvancedTicket::show() const
{
    cout << "티켓 번호 :" << this->number << endl;
    cout << "가격정보 : " << this->price << endl;
	cout << "사전예약일 : " << this->advanceDays << endl;
    cout << "지불금액 : " << this->getPrice() << endl;
}
