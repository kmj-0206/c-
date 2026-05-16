#pragma once
#include <iostream>
using namespace std;
class Ticket
{
protected:
	int number;
	double price;

public:
	static int count;
	Ticket(double price);
	int getNumber() const;
	double getPrice() const;
	void setPrice(const double& price);
	void show() const;
};
