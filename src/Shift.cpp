#include "../include/Shift.hpp"


Shift::Shift(const std::string& nameCashier, double startAmount)
	: cashier(nameCashier), cashBox(startAmount)
{

}

void Shift::newCheque()
{
	cashBox.newCheque();
}

void Shift::summingResults()
{
	cashBox.summingResults();
}

double Shift::amountCashBox()
{
	return cashBox.amountCash();
}

double Shift::amountCashShift()
{
	return cashBox.amountCashPerShift();
}

Cashier& Shift::getCashier()
{
	return cashier;
}