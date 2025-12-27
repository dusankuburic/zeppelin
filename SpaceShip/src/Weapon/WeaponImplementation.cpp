#include "Weapon.h"
#include <iomanip>

Weapon::Weapon(const std::string& name,
               const std::string& faction,
               int64_t price,
               int rotation,
               double life_time,
               int travel_range,
               int speed,
               int damage,
               const std::string& description)
    : name_(name),
      faction_name_(faction),
      description_(description),
      price_(price),
      rotation_(rotation),
      life_time_(life_time),
      travel_range_(travel_range),
      speed_(speed),
      damage_(damage) {
}

std::ostream& operator<<(std::ostream& out, const Weapon& weapon) {
	out << "Name: " << weapon.GetName() << "\n";
	out << "Faction: " << weapon.GetFactionName() << "\n";
	out << "Price: " << weapon.GetPrice() << "\n";
	out << "Rotation: " << weapon.GetRotation() << "\n";
	out << "Life Time: " << std::fixed << std::setprecision(2) << weapon.GetLifeTime() << "\n";
	out << "Travel Range: " << weapon.GetTravelRange() << "\n";
	out << "Speed: " << weapon.GetSpeed() << "\n";
	out << "Damage: " << weapon.GetDamage() << "\n";
	if (!weapon.GetDescription().empty()) {
		out << "Description: " << weapon.GetDescription() << "\n";
	}
	return out;
}