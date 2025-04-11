#include "../include/ProductDatabase.hpp"
#include <sstream>


ProductDatabase::ProductDatabase(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open()) {
		throw std::runtime_error("[-] Error: couldn't open the product file: " + path);
	}

	std::string line;
	bool isHeader = true;

	while (std::getline(file, line)) {
		if (isHeader) {
			isHeader = false;
			continue;
		}
		if (line.empty()) continue;

		std::istringstream ss(line);
		std::vector<std::string> tokens;
		std::string token;

		while (std::getline(ss, token, ',')) {
			tokens.push_back(token);
		}

		if (tokens.size() != 3) {
			std::cerr << "[!] Malformed line: " << line << std::endl;
			continue;
		}

		try {
			const std::string& name = tokens[0];
			const std::string& barcode = tokens[1];
			double price = std::stod(tokens[2]);

			auto it = products.find(barcode);
			if (it != products.end()) {
				it->second.second++;
			}
			else {
				products[barcode] = { Product(name, barcode, price), 1 };
			}
		}
		catch (const std::exception&) {
			std::cerr << "[!] String parsing error: " << line << std::endl;
		}
	}
}

const std::unordered_map<std::string, std::pair<Product, size_t>>& ProductDatabase::getProducts() const
{ 
	return products;
}

void ProductDatabase::changeDatabase(const std::unordered_map<std::string, std::pair<Product, size_t>>& productsChange)
{
	for (const auto& [barcode, pair] : productsChange) {
		auto it = products.find(barcode);
		if (it == products.end()) {
			std::cerr << "[!] Ќе удалось найти товар с barcode: " << barcode << " в базе.\n";
			continue;
		}

		size_t& stock = it->second.second;
		size_t quantityToRemove = pair.second;

		if (stock < quantityToRemove) {
			std::cerr << "[!] Ќевозможно списать " << quantityToRemove << " единиц товара {"
				<< it->second.first.name << "} Ч в наличии только " << stock << "\n";
			continue;
		}

		stock -= quantityToRemove;
	}
}