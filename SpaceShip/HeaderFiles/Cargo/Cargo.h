#pragma once
#include <string>
#include <cstdint>
#include <iostream>

class Cargo {
public:
	Cargo() = default;

	Cargo(const std::string& name,
	      const std::string& faction,
	      int64_t price,
	      int atomic_number = 0,
	      double relative_atomic_mass = 0.0,
	      const std::string& state_at_20 = "",
	      const std::string& description = "");

	~Cargo() = default;

	void SetName(const std::string& name) { name_ = name; }
	std::string GetCargoName() const { return name_; }
	std::string GetName() const { return name_; }


	void SetFactionName(const std::string& faction) { faction_name_ = faction; }
	std::string GetFactionName() const { return faction_name_; }

	void SetPrice(int64_t price) { price_ = price; }
	int64_t GetCargoPrice() const { return price_; }
	int64_t GetPrice() const { return price_; }


	void SetAtomicNumber(int number) { atomic_number_ = number; }
	int GetAtomicNumber() const { return atomic_number_; }

	void SetRelativeAtomicMass(double mass) { relative_atomic_mass_ = mass; }
	double GetRelativeAtomicMass() const { return relative_atomic_mass_; }

	void SetStateAt20(const std::string& state) { state_at_20_ = state; }
	std::string GetStateAt20() const { return state_at_20_; }

	void SetDescription(const std::string& desc) { description_ = desc; }
	std::string GetDescription() const { return description_; }

	friend std::ostream& operator<<(std::ostream& out, const Cargo& cargo);

private:
	std::string name_;
	std::string faction_name_;
	std::string state_at_20_;
	std::string description_;
	int64_t price_ = 0;
	int atomic_number_ = 0;
	double relative_atomic_mass_ = 0.0;
};
