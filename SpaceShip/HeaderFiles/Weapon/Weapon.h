#pragma once
#include <string>
#include <cstdint>
#include <iostream>

class Weapon {
public:
	Weapon() = default;

	Weapon(const std::string& name,
	       const std::string& faction,
	       int64_t price,
	       int rotation = 0,
	       double life_time = 0.0,
	       int travel_range = 0,
	       int speed = 0,
	       int damage = 0,
	       const std::string& description = "");

	~Weapon() = default;

	void SetName(const std::string& name) { name_ = name; }
	std::string GetName() const { return name_; }


	void SetFactionName(const std::string& faction) { faction_name_ = faction; }
	std::string GetFactionName() const { return faction_name_; }

	void SetPrice(int64_t price) { price_ = price; }
	int64_t GetWeaponPrice() const { return price_; }
	int64_t GetPrice() const { return price_; }


	void SetRotation(int rotation) { rotation_ = rotation; }
	int GetRotation() const { return rotation_; }

	void SetLifeTime(double life_time) { life_time_ = life_time; }
	double GetLifeTime() const { return life_time_; }

	void SetTravelRange(int range) { travel_range_ = range; }
	int GetTravelRange() const { return travel_range_; }

	void SetSpeed(int speed) { speed_ = speed; }
	int GetSpeed() const { return speed_; }

	void SetDamage(int damage) { damage_ = damage; }
	int GetDamage() const { return damage_; }

	void SetDescription(const std::string& desc) { description_ = desc; }
	std::string GetDescription() const { return description_; }

	friend std::ostream& operator<<(std::ostream& out, const Weapon& weapon);

private:
	std::string name_;
	std::string faction_name_;
	std::string description_;
	int64_t price_ = 0;
	int rotation_ = 0;
	double life_time_ = 0.0;
	int travel_range_ = 0;
	int speed_ = 0;
	int damage_ = 0;
};