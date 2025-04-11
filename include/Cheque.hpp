#pragma once
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "Product.hpp"
#include "ProductDatabase.hpp"


enum class PaymentMethod 
{
	None,
	Card,
	Cash
};

class Cheque
{
public:
	void addProduct(const ProductDatabase& productDatabase, const std::string& barcode_name, size_t quantity);
	void printCheque();
	const std::unordered_map<std::string, std::pair<Product, size_t>>& getProducts() const;
	double getAmount();
	void setPayment(PaymentMethod method, double paid = 0.0);

private:
	std::unordered_map<std::string, std::pair<Product, size_t>> products;
	double amount;
	PaymentMethod paymentMethod = PaymentMethod::None;
	double cashPaid = 0.0;
	double change = 0.0;
};