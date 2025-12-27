#include "Shield.h"
#include <iomanip>

Shield::Shield(const std::string& name,
               const std::string& faction,
               int64_t price,
               int armor_rating,
               int energy_capacity,
               int capacity,
               int regen_delay,
               int regeneration_rate,
               int regen_power,
               const std::string& description)
    : name_(name),
      faction_name_(faction),
      description_(description),
      price_(price),
      armor_rating_(armor_rating),
      energy_capacity_(energy_capacity),
      capacity_(capacity),
      regen_delay_(regen_delay),
      regeneration_rate_(regeneration_rate),
      regen_power_(regen_power) {
}

std::ostream& operator<<(std::ostream& out, const Shield& shield) {
	out << "Name: " << shield.GetName() << "\n";
	out << "Faction: " << shield.GetFactionName() << "\n";
	out << "Price: " << shield.GetPrice() << "\n";
	out << "Armor Rating: " << shield.GetArmorRating() << "\n";
	out << "Energy Capacity: " << shield.GetEnergyCapacity() << "\n";
	out << "Capacity: " << shield.GetCapacity() << "\n";
	out << "Regen Delay: " << shield.GetRegenDelay() << "\n";
	out << "Regeneration Rate: " << shield.GetRegenerationRate() << "\n";
	out << "Regen Power: " << shield.GetRegenPower() << "\n";
	if (!shield.GetDescription().empty()) {
		out << "Description: " << shield.GetDescription() << "\n";
	}
	return out;
}
