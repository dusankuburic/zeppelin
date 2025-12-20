#pragma once
#include "INVENTORY_MANIPULATION.h"
#include<vector>

class Human : public InventoryManipulation {
public:
	Human() {}
	Human(std::string, std::string, int);
	~Human() {}

	void SetFirstName(const std::string&);
	std::string GetFirstName() const;

	void SetLastName(const std::string&);
	std::string GetLastName() const;

	void SetBirthYear(int);
	int GetBirthYear() const;

	virtual void AddElemToInventory(const std::string&);
	virtual void AddMoreElemToInventory(int);
	virtual void RemoveElemFromInventory();
	virtual void WhatIsInInventory() const;
	virtual void IsThisInInventory(const std::string&) const;

	friend std::ostream& operator<< (std::ostream&, const Human&);
	void Trade(Human& toWho, const std::string& item);

private:
	std::string first_name_;
	std::string last_name_;
	int birth_year_;
	std::vector<std::string> inventory;
};
