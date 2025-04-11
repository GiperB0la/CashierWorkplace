#pragma once
#include <iostream>


struct Cashier
{
	std::string name;

	Cashier(const std::string& name)
		: name(name) {
	}
};