#include "../include/CashierWorkplace.hpp"


void CashierWorkplace::openShift()
{
	std::string nameCashier;
	double amount;
	std::cout << "������� ��� �������: ";
	std::getline(std::cin, nameCashier);
	std::cout << "������� ��������� ����� � �������� �������: ";
	std::cin >> amount;

	Shift shift(nameCashier, amount);

	while (isShifting) {
		size_t operation;
		std::cout << "\n�������� ��������:\n 1 - ����� ���\n 2 - ������� ����\n 3 - ������� �����\n> ";
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
	std::cout << "\n������ " << shift.getCashier().name << std::endl;
	std::cout << "����� �� �����: " << shift.amountCashShift() << std::endl;
	std::cout << "� �����: " << shift.amountCashBox() << std::endl;
	isShifting = false;
	std::cout << "����� �������." << std::endl;
}