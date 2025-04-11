#pragma once
#include <iostream>
#include <vector>
#include "Cheque.hpp"
#include "ProductDatabase.hpp"


class CashBox
{
public:
	CashBox(double startAmount);

public:
	void newCheque();
	void summingResults();
	double amountCash();
	double amountCashPerShift();

private:
	void addProduct(Cheque& cheque);
	void punchThrough(Cheque& cheque);
	void payment(Cheque& cheque);

private:
	double amount;
	double perShift;
	std::vector<Cheque> cheques;
	ProductDatabase productDatabase;
};