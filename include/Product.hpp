#pragma once
#include <iostream>


struct Product
{
	std::string name;
	std::string barcode;
	double price;

	Product() = default;
	Product(const std::string& name, const std::string& barcode, double price)
		: name(name), barcode(barcode), price(price) {
	}
};