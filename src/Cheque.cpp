#include "../include/Cheque.hpp"


void Cheque::addProduct(const ProductDatabase& productDatabase, const std::string& barcodeOrName, size_t quantity)
{
	const auto& db = productDatabase.getProducts();
	auto it = db.find(barcodeOrName);

	if (it == db.end()) {
		for (const auto& [code, pair] : db) {
			if (pair.first.name == barcodeOrName) {
				it = db.find(code);
				break;
			}
		}

		if (it == db.end()) {
			std::cerr << "[!] Товар с названием или штрих-кодом \"" << barcodeOrName << "\" не найден." << std::endl;
			return;
		}
	}

	const Product& product = it->second.first;
	const std::string& barcode = it->first;
	size_t available = it->second.second;

	size_t alreadyInCheque = 0;
	auto prodIt = products.find(barcode);
	if (prodIt != products.end()) {
		alreadyInCheque = prodIt->second.second;
	}

	if (available < alreadyInCheque + quantity) {
		std::cerr << "[!] Недостаточно товара {" << product.name << "}. В наличии: "
			<< (available - alreadyInCheque) << ", запрошено: " << quantity << std::endl;
		return;
	}

	if (products.find(barcode) != products.end()) {
		products[barcode].second += quantity;
	}
	else {
		products[barcode] = { product, quantity };
	}

	amount += product.price * quantity;

	std::cout << "Товар {" << product.name << "} x" << quantity << " добавлен." << std::endl;
	std::cout << "Сумма чека: " << amount << std::endl;
}

void Cheque::printCheque()
{
	if (products.empty()) {
		std::cout << "\n[!] Чек пуст.\n";
		return;
	}

	std::cout << "\n====================== ЧЕК ======================\n";
	std::cout << std::left
		<< std::setw(4) << "№"
		<< std::setw(20) << "Наименование"
		<< std::setw(10) << "Кол-во"
		<< std::setw(10) << "Цена"
		<< std::setw(12) << "Сумма"
		<< "\n";

	std::cout << std::string(49, '-') << "\n";

	size_t i = 0;
	for (const auto& [barcode, pair] : products) {
		const Product& product = pair.first;
		size_t quantity = pair.second;
		double total = quantity * product.price;

		std::cout << std::left
			<< std::setw(4) << (++i)
			<< std::setw(20) << product.name
			<< std::setw(10) << quantity
			<< std::setw(10) << std::fixed << std::setprecision(2) << product.price
			<< std::setw(12) << std::fixed << std::setprecision(2) << total
			<< "\n";
	}

	std::cout << std::string(49, '-') << "\n";
	std::cout << std::right << std::setw(44) << "ИТОГО: "
		<< std::fixed << std::setprecision(2) << amount << "\n";

	if (paymentMethod != PaymentMethod::None) {
		std::cout << std::setw(44) << "ОПЛАТА: ";
		if (paymentMethod == PaymentMethod::Card) {
			std::cout << "Карта\n";
		}
		else if (paymentMethod == PaymentMethod::Cash) {
			std::cout << "Наличные (" << cashPaid << ")\n";
			std::cout << std::setw(44) << "СДАЧА: " << std::fixed << std::setprecision(2) << change << "\n";
		}
	}

	std::cout << "=================================================\n";
}

const std::unordered_map<std::string, std::pair<Product, size_t>>& Cheque::getProducts() const
{
	return products;
}

double Cheque::getAmount()
{
	return amount;
}

void Cheque::setPayment(PaymentMethod method, double paid)
{
	paymentMethod = method;

	if (method == PaymentMethod::Cash) {
		cashPaid = paid;
		change = paid - amount;
	}
	else {
		cashPaid = 0.0;
		change = 0.0;
	}
}