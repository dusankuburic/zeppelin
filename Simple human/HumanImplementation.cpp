#include "Header files/Human.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <utility>

void Human::SetFirstName(const std::string& first_name) {
	FirstName = first_name;
}

const std::string& Human::GetFirstName() const {
	return FirstName;
}

void Human::SetLastName(const std::string& last_name) {
	LastName = last_name;
}

const std::string& Human::GetLastName() const {
	return LastName;
}

void Human::SetBirthYear(int birth_year) {
	BirthYear = birth_year;
}

int Human::GetBirthYear() const {
	return BirthYear;
}

void Human::AddElemToInventory(const std::string& elem) {
	Inventory.push_back(elem);
}


void Human::AddMoreElemToInventory(int num) {
	std::string item;

	std::cout << "Adding items to inventory" << "\n";
	for (int i = 1; i <= num; ++i) {
		std::cout << "Item [" << i << "]: ";
		if (!(std::cin >> item)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
		Inventory.push_back(item);
	}
}

void Human::RemoveElemFromInventory() {
	if (!Inventory.empty()) {
		Inventory.pop_back();
	}
}

void Human::WhatIsInInventory() const {
	if (Inventory.empty()) {
		std::cout << "Inventory is empty!!!" << "\n";
	}
	else {
		std::cout << "\n" << this->GetFirstName() << " inventory:" << "\n";
		for (const auto& item : Inventory) {
			std::cout << item << "\n";
		}

		std::cout << "\n";
	}
}

void Human::IsThisInInventory(const std::string& item) const {
	if (Inventory.empty()) {
		std::cout << "Inventory is empty!!!" << "\n";
	}
	else {
		auto it = std::find(Inventory.cbegin(), Inventory.cend(), item);

		if (it != Inventory.cend()) {
			std::cout << "Item " << *it << " found!" << "\n";
		}
		else {
			std::cout << "Item not found!" << "\n";
		}
	}
}


void Human::Trade(Human& toWho, const std::string& item) {
	if (Inventory.empty()) {
		std::cout << "Inventory is empty, no items to send!!!" << "\n";
	}
	else
	{
		auto it = std::find(Inventory.cbegin(), Inventory.cend(), item);

		if (it != Inventory.cend()) {
			toWho.AddElemToInventory(item);
			Inventory.erase(it);
			std::cout << "Successfully sent" << "\n";
		}
		else {
			std::cout << "\n" << "Cannot send an item you don't have!!!" << "\n";
		}
	}
}

Human::Human(std::string first_name, std::string last_name, int birth_year) :
	FirstName(std::move(first_name)), LastName(std::move(last_name)), BirthYear(birth_year)
{

}

std::ostream& operator<< (std::ostream& out, const Human& human) {
	out << "First name: " << human.GetFirstName() << "\n";
	out << "Last name: " << human.GetLastName() << "\n";
	out << "Birth year: " << human.GetBirthYear() << "\n";
	return out;
}