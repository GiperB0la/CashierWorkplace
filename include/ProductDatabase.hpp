#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include "Product.hpp"


class ProductDatabase
{
public:
	ProductDatabase(const std::string& path);

public:
	const std::unordered_map<std::string, std::pair<Product, size_t>>& getProducts() const;
	void changeDatabase(const std::unordered_map<std::string, std::pair<Product, size_t>>& productsChange);

private:
	std::unordered_map<std::string, std::pair<Product, size_t>> products;
};