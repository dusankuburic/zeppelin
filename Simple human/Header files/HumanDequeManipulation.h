#pragma once
#include "Human.h"
#include<iostream>
#include<deque>
#include<limits>
#include<string>

void AddHuman(std::deque<Human>& humans) {
	std::string first_name;
	std::string last_name;
	int birth_year;

	std::cout << "------ Input ------ \n";
	std::cout << "First name: ";
	if (!(std::cin >> first_name)) {
		std::cerr << "Error: Invalid input for first name\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}

	std::cout << "Last name: ";
	if (!(std::cin >> last_name)) {
		std::cerr << "Error: Invalid input for last name\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}

	std::cout << "Birth year: ";
	if (!(std::cin >> birth_year) || birth_year < 1900 || birth_year > 2025) {
		std::cerr << "Error: Invalid birth year (must be between 1900-2025)\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}

	humans.push_back(Human(first_name, last_name, birth_year));
}

void AddMoreHumans(std::deque<Human>& humans, int num) {
	std::string first_name;
	std::string last_name;
	int birth_year;

	for (int i = 1; i <= num; i++) {
		std::cout << "------ Input ------ \n";
		std::cout << "First name: ";
		if (!(std::cin >> first_name)) {
			std::cerr << "Error: Invalid input for first name\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		std::cout << "Last name: ";
		if (!(std::cin >> last_name)) {
			std::cerr << "Error: Invalid input for last name\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		std::cout << "Birth year: ";
		if (!(std::cin >> birth_year) || birth_year < 1900 || birth_year > 2025) {
			std::cerr << "Error: Invalid birth year (must be between 1900-2025)\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		humans.push_back(Human(first_name, last_name, birth_year));
	}
}

void PrintHumans(const std::deque<Human>& humans) {
	if (humans.empty()) {
		std::cout << "No humans, deque is empty!!!" << "\n";
	}
	else {
		std::cout << "\n" << "_|_|>> OUTPUT <<|_|_" << "\n";
		for (const auto& human : humans) {
			std::cout << "======================" << "\n";
			std::cout << human << "\n";
		}
	}
}

void PrintHumansInventory(const std::deque<Human>& humans) {
	if (humans.empty()) {
		std::cout << "No humans, deque is empty!!!" << "\n";
	}
	else {
		for (const auto& human : humans) {
			human.WhatIsInInventory();
		}
	}
}

void PrintHumanInventory(const std::deque<Human>& humans, const std::string& first_name) {
	if (humans.empty()) {
		std::cout << "No humans, deque is empty!!!" << "\n";
	}
	else {
		for (const auto& human : humans) {
			if (human.GetFirstName() == first_name) {
				human.WhatIsInInventory();
			}
		}
	}
}