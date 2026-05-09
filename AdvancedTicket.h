#pragma once
#include "Ticket.h"
class AdvancedTicket : public Ticket
{
private:
	int advanceDays;
public:
	AdvancedTicket(double price, int advanceDays);
	double getPrice() const;
	int getAdvanceDays() const;
	void show() const;
};

