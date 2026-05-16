#include "Ticket.h"

int Ticket::count = 0;
Ticket::Ticket(double price)
{   
    this->price = price;
    this->number = ++Ticket::count;
}

int Ticket::getNumber() const
{
    return this->number;
}

double Ticket::getPrice() const
{
    return this->price;
}

void Ticket::setPrice(const double& price)
{
    this->price = price;
}

void Ticket::show() const
{
    cout << "티켓 번호 : " << number << endl;
    cout << "가격 정보 : " << price << endl;
}
