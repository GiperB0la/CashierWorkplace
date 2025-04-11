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
		std::cout << "\nВведите операцию:\n1 - добавить товар\n2 - пробить чек\n3 - отменить чек\n> ";
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
			std::cout << "Отмена чека." << std::endl;
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

	std::cout << "\nВведите штрих-код или наименование товара:\n> ";
	std::getline(std::cin, barcode_name);

	std::cout << "Введите количество:\n> ";
	if (!(std::cin >> quantity)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << "Неверный ввод количества.\n";
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
	std::cout << "К оплате: " << amountPaid << std::endl;
	size_t choice = 0;
	double paid = 0.0;

	while (choice != 1 && choice != 2) {
		std::cout << "\nОплата:\n1 - карта\n2 - наличные\n> ";
		std::cin >> choice;

		if (choice == 1) {
			std::cout << "Оплата картой." << std::endl;
		}
		else if (choice == 2) {
			std::cout << "Введите сумму:\n> ";
			while (paid - amountPaid < 0.0) {
				std::cin >> paid;
				if (paid - amountPaid < 0.0) {
					std::cout << "Недостаточно средств для оплаты.\nПопробуйте еще раз:\n> ";
				}
			}
			double change = paid - amountPaid;
			if (change != 0.0) {
				std::cout << "Сдача: " << change << std::endl;
			}
		}
		else {
			std::cout << "[!] Попробуйте еще раз." << std::endl;
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
	std::cout << "В кассе: " << amount << std::endl;
}

void CashBox::summingResults()
{
	if (cheques.empty()) {
		std::cout << "Нет чеков." << std::endl;
		return;
	}

	std::cout << "\nЧеки за смену: ";
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