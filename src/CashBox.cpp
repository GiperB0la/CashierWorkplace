#include "../include/CashBox.hpp"


CashBox::CashBox(double startAmount)
	: amount(startAmount), productDatabase("products.csv")
{

}

void CashBox::newCheque()
{
	bool run = true;
	Cheque cheque;

	while (run) {
		size_t operation;
		std::cout << "\n������� ��������:\n1 - �������� �����\n2 - ������� ���\n3 - �������� ���\n> ";
		std::cin >> operation;

		switch (operation)
		{
		case 1: {
			addProduct(cheque);
			break;
		}
		case 2: {
			punchThrough(cheque);
			run = false;
			break;
		}
		case 3: {
			std::cout << "������ ����." << std::endl;
			run = false;
			break;
		}
		default:
			break;
		}
	}
}

void CashBox::addProduct(Cheque& cheque)
{
	std::string barcode_name;
	size_t quantity;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "\n������� �����-��� ��� ������������ ������:\n> ";
	std::getline(std::cin, barcode_name);

	std::cout << "������� ����������:\n> ";
	if (!(std::cin >> quantity)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << "�������� ���� ����������.\n";
		return;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cheque.addProduct(productDatabase, barcode_name, quantity);
}

void CashBox::punchThrough(Cheque& cheque)
{
	payment(cheque);
	productDatabase.changeDatabase(cheque.getProducts());
	if (!cheque.getProducts().empty()) {
		cheque.printCheque();
		cheques.push_back(cheque);
	}
}

void CashBox::payment(Cheque& cheque)
{
	double amountPaid = cheque.getAmount();
	std::cout << "� ������: " << amountPaid << std::endl;
	size_t choice = 0;
	double paid = 0.0;

	while (choice != 1 && choice != 2) {
		std::cout << "\n������:\n1 - �����\n2 - ��������\n> ";
		std::cin >> choice;

		if (choice == 1) {
			std::cout << "������ ������." << std::endl;
		}
		else if (choice == 2) {
			std::cout << "������� �����:\n> ";
			while (paid - amountPaid < 0.0) {
				std::cin >> paid;
				if (paid - amountPaid < 0.0) {
					std::cout << "������������ ������� ��� ������.\n���������� ��� ���:\n> ";
				}
			}
			double change = paid - amountPaid;
			if (change != 0.0) {
				std::cout << "�����: " << change << std::endl;
			}
		}
		else {
			std::cout << "[!] ���������� ��� ���." << std::endl;
		}
	}

	if (choice == 1) {
		cheque.setPayment(PaymentMethod::Card);
	}
	else if (choice == 2) {
		cheque.setPayment(PaymentMethod::Cash, paid);
	}

	amount += amountPaid;
	perShift += amountPaid;
	std::cout << "� �����: " << amount << std::endl;
}

void CashBox::summingResults()
{
	if (cheques.empty()) {
		std::cout << "��� �����." << std::endl;
		return;
	}

	std::cout << "\n���� �� �����: ";
	for (auto& cheque : cheques) {
		cheque.printCheque();
	}
}

double CashBox::amountCash()
{
	return amount;
}

double CashBox::amountCashPerShift()
{
	return perShift;
}