#pragma once
#include "InventoryManipulation.h"
#include <vector>
#include <string>
#include <iostream>

class Human : public InventoryManipulation {
public:
	Human() {}
	Human(std::string, std::string, int);
	~Human() {}

	void SetFirstName(const std::string&);
	const std::string& GetFirstName() const;

	void SetLastName(const std::string&);
	const std::string& GetLastName() const;

	void SetBirthYear(int);
	int GetBirthYear() const;

	void AddElemToInventory(const std::string&) override;
	void AddMoreElemToInventory(int) override;
	void RemoveElemFromInventory() override;
	void WhatIsInInventory() const override;
	void IsThisInInventory(const std::string&) const override;

	friend std::ostream& operator<< (std::ostream&, const Human&);
	void Trade(Human& toWho, const std::string& item);

private:
	std::string FirstName;
	std::string LastName;
	int BirthYear;
	std::vector<std::string> Inventory;
};
