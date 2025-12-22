#pragma once
#include <string>
#include <cstdint>
#include <iostream>

class Engine {
public:
	Engine() = default;

	Engine(const std::string& name,
	       const std::string& faction,
	       int64_t price,
	       int power_usage = 0,
	       int radiation_level = 0,
	       const std::string& description = "");

	~Engine() = default;

	void SetEngineName(const std::string& name) { name_ = name; }
	std::string GetEngineName() const { return name_; }
	std::string GetName() const { return name_; }


	void SetFactionName(const std::string& faction) { faction_name_ = faction; }
	std::string GetFactionName() const { return faction_name_; }

	void SetPrice(int64_t price) { price_ = price; }
	int64_t GetEnginePrice() const { return price_; }
	int64_t GetPrice() const { return price_; }


	void SetPowerUsage(int usage) { power_usage_ = usage; }
	int GetPowerUsage() const { return power_usage_; }

	void SetRadiationLevel(int level) { radiation_level_ = level; }
	int GetRadiationLevel() const { return radiation_level_; }

	void SetDescription(const std::string& desc) { description_ = desc; }
	std::string GetDescription() const { return description_; }

	friend std::ostream& operator<<(std::ostream& out, const Engine& engine);

private:
	std::string name_;
	std::string faction_name_;
	std::string description_;
	int64_t price_ = 0;
	int power_usage_ = 0;
	int radiation_level_ = 0;
};
