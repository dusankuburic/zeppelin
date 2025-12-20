#include "HUMAN.h"
#include<iostream>
#include<algorithm>

void Human::SetFirstName(const std::string& first_name) {
	first_name_ = first_name;
}

std::string Human::GetFirstName() const {
	return first_name_;
}

void Human::SetLastName(const std::string& last_name) {
	last_name_ = last_name;
}

std::string Human::GetLastName() const {
	return last_name_;
}

void Human::SetBirthYear(int birth_year) {
	birth_year_ = birth_year;
}

int Human::GetBirthYear() const {
	return birth_year_;
}

void Human::AddElemToInventory(const std::string& elem) {
	inventory.push_back(elem);
}


void Human::AddMoreElemToInventory(int num) {
	std::string item;

	std::cout << "Adding items to inventory" << "\n";
	for (int i = 1; i <= num; ++i) {
		std::cout << "Item [" << i << "]: ";
		std::cin >> item;
		inventory.push_back(item);
	}
}

void Human::RemoveElemFromInventory() {
	inventory.pop_back();
}

void Human::WhatIsInInventory() const {
	if (inventory.empty()) {
		std::cout << "Inventory is empty!!!" << "\n";
	}
	else {
		std::cout << "\n" << this->GetFirstName() << " inventory:" << "\n";
		for (const auto& item : inventory) {
			std::cout << item << "\n";
		}

		std::cout << "\n";
	}
}

void Human::IsThisInInventory(const std::string& item) const {
	if (inventory.empty()) {
		std::cout << "Inventory is empty!!!" << "\n";
	}
	else {
		auto it = find(inventory.cbegin(), inventory.cend(), item);

		if (it != inventory.cend()) {
			std::cout << "Item " << *it << " found!" << "\n";
		}
		else {
			std::cout << "Item not found!" << "\n";
		}
	}
}


void Human::Trade(Human& toWho, const std::string& item) {
	if (inventory.empty()) {
		std::cout << "Inventory is empty, no items to send!!!" << "\n";
	}
	else
	{
		auto it = find(inventory.cbegin(), inventory.cend(), item);

		if (it != inventory.cend()) {
			toWho.AddElemToInventory(item);
			inventory.erase(it);
			std::cout << "Successfully sent" << "\n";
		}
		else {
			std::cout << "\n" << "Cannot send an item you don't have!!!" << "\n";
		}
	}
}

Human::Human(std::string first_name, std::string last_name, int birth_year) :
	first_name_(first_name), last_name_(last_name), birth_year_(birth_year)
{

}

std::ostream& operator<< (std::ostream& out, const Human& human) {
	out << "First name: " << human.GetFirstName() << "\n";
	out << "Last name: " << human.GetLastName() << "\n";
	out << "Birth year: " << human.GetBirthYear() << "\n";
	return out;
}