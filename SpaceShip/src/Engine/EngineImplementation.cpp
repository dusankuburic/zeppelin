#include "Engine.h"
#include <iomanip>

Engine::Engine(const std::string& name,
               const std::string& faction,
               int64_t price,
               int power_usage,
               int radiation_level,
               const std::string& description)
    : name_(name),
      faction_name_(faction),
      description_(description),
      price_(price),
      power_usage_(power_usage),
      radiation_level_(radiation_level) {
}

std::ostream& operator<<(std::ostream& out, const Engine& engine) {
	out << "Name: " << engine.GetEngineName() << "\n";
	out << "Faction: " << engine.GetFactionName() << "\n";
	out << "Price: " << engine.GetPrice() << "\n";
	out << "Power Usage: " << engine.GetPowerUsage() << "\n";
	out << "Radiation Level: " << engine.GetRadiationLevel() << "\n";
	if (!engine.GetDescription().empty()) {
		out << "Description: " << engine.GetDescription() << "\n";
	}
	return out;
}