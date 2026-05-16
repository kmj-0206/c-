#pragma once
#include "Ticket.h"
class GeneralTicket : public Ticket
{
private:
	bool payByCredit;
public:
	GeneralTicket(double price, bool payByCredit);
	double getPrice() const;
	bool getPayByCredit() const;
	void show() const;
	
};

