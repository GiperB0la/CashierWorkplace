#pragma once
#include <string>
#include "Shift.hpp"


class CashierWorkplace
{
public:
	void openShift();

private:
	void closeShift(Shift& shift);

private:
	bool isShifting = true;
};