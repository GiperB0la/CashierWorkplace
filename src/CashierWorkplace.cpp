#include "../include/CashierWorkplace.hpp"


void CashierWorkplace::openShift()
{
	std::string nameCashier;
	double amount;
	std::cout << "Введите имя кассира: ";
	std::getline(std::cin, nameCashier);
	std::cout << "Введите начальную сумму в кассовый аппарат: ";
	std::cin >> amount;

	Shift shift(nameCashier, amount);

	while (isShifting) {
		size_t operation;
		std::cout << "\nВыберите операцию:\n 1 - новый чек\n 2 - вывести чеки\n 3 - закрыть смены\n> ";
		std::cin >> operation;

		switch (operation)
		{
		case 1: {
			shift.newCheque();
			break;
		}
		case 2: {
			shift.summingResults();
			break;
		}
		case 3: {
			closeShift(shift);
			break;
		}
		default:
			break;
		}
	}
}

void CashierWorkplace::closeShift(Shift& shift)
{
	shift.summingResults();
	std::cout << "\nКассир " << shift.getCashier().name << std::endl;
	std::cout << "Итого за смену: " << shift.amountCashShift() << std::endl;
	std::cout << "В кассе: " << shift.amountCashBox() << std::endl;
	isShifting = false;
	std::cout << "Смена закрыта." << std::endl;
}