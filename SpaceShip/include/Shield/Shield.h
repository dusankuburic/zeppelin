#pragma once
#include <string>
#include <cstdint>
#include <iostream>

class Shield {
public:
	Shield() = default;

	Shield(const std::string& name,
	       const std::string& faction,
	       int64_t price,
	       int armor_rating = 0,
	       int energy_capacity = 0,
	       int capacity = 0,
	       int regen_delay = 0,
	       int regeneration_rate = 0,
	       int regen_power = 0,
	       const std::string& description = "");

	~Shield() = default;

	void SetName(const std::string& name) { name_ = name; }
	std::string GetName() const { return name_; }


	void SetFactionName(const std::string& faction) { faction_name_ = faction; }
	std::string GetFactionName() const { return faction_name_; }

	void SetPrice(int64_t price) { price_ = price; }
	int64_t GetShieldPrice() const { return price_; }
	int64_t GetPrice() const { return price_; }


	void SetArmorRating(int rating) { armor_rating_ = rating; }
	int GetArmorRating() const { return armor_rating_; }

	void SetEnergyCapacity(int capacity) { energy_capacity_ = capacity; }
	int GetEnergyCapacity() const { return energy_capacity_; }

	void SetCapacity(int capacity) { capacity_ = capacity; }
	int GetCapacity() const { return capacity_; }

	void SetRegenDelay(int delay) { regen_delay_ = delay; }
	int GetRegenDelay() const { return regen_delay_; }

	void SetRegenerationRate(int rate) { regeneration_rate_ = rate; }
	int GetRegenerationRate() const { return regeneration_rate_; }

	void SetRegenPower(int power) { regen_power_ = power; }
	int GetRegenPower() const { return regen_power_; }

	void SetDescription(const std::string& desc) { description_ = desc; }
	std::string GetDescription() const { return description_; }

	friend std::ostream& operator<<(std::ostream& out, const Shield& shield);

private:
	std::string name_;
	std::string faction_name_;
	std::string description_;
	int64_t price_ = 0;
	int armor_rating_ = 0;
	int energy_capacity_ = 0;
	int capacity_ = 0;
	int regen_delay_ = 0;
	int regeneration_rate_ = 0;
	int regen_power_ = 0;
};