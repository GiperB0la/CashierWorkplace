#pragma once
#include "Cashier.hpp"
#include "CashBox.hpp"


class Shift
{
public:
	Shift(const std::string& nameCashier, double startAmount);

public:
	void summingResults();
	void newCheque();
	double amountCashBox();
	double amountCashShift();
	Cashier& getCashier();

private:
	Cashier cashier;
	CashBox cashBox;
};