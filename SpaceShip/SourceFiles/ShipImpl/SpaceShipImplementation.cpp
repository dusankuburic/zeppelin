#include "SpaceShip.h"
#include <stdexcept>

SpaceShip::SpaceShip() {

}

SpaceShip::SpaceShip(const std::string& faction) :
	faction_(faction) {

}

SpaceShip::SpaceShip(const std::string& faction, const int price) :
	faction_(faction),
	price_(price) {

}

std::string SpaceShip::GetFaction() const {
	return faction_;
}

void SpaceShip::SetFaction(const std::string& faction) {
	faction_ = faction;
}

int64_t SpaceShip::GetShipPrice() const {
	return price_;
}

void SpaceShip::SetShipPrice(const int64_t& price) {
	price_ = price;
}

void SpaceShip::ListCargo() {
	std::cout << "Cargo list:" << "\n";
	for (auto it = cargo_v.cbegin(); it != cargo_v.cend(); ++it) {
		AboutCargo(*it);
		std::cout << "-------------" << "\n";
	}
}

void SpaceShip::ListEngine() {
	std::cout << "Engine list:" << "\n";
	for (auto it = engine_m.cbegin(); it != engine_m.cend(); ++it) {
		AboutEngine(it->second);
		std::cout << "-------------" << "\n";
	}
}

void SpaceShip::ListShield() {
	std::cout << "Shield list:" << "\n";
	for (auto it = shield_v.cbegin(); it != shield_v.cend(); ++it) {
		AboutShield(*it);
		std::cout << "-------------" << "\n";
	}
}

void SpaceShip::ListWeapon() {
	std::cout << "Weapon list:" << "\n";
	for (auto it = guns_m.cbegin(); it != guns_m.cend(); ++it) {
		AboutWeapon(it->second);
		std::cout << "-------------" << "\n";
	}
		
}

void SpaceShip::AddCargo(const Cargo& cargo) {
	cargo_v.push_back(cargo);
	price_ += cargo.GetCargoPrice();
	
}

void SpaceShip::RemoveCargo() {
	if (cargo_v.empty()) {
		throw std::runtime_error("Cannot remove cargo: cargo bay is empty");
	}
	else {
		price_ -= cargo_v.back().GetCargoPrice();
		cargo_v.pop_back();
	}
}

void SpaceShip::AboutCargo(const Cargo& cargo) {
	std::cout << "\n";
	std::cout << "Name: " << cargo.GetCargoName() << "\n";
	std::cout << "Faction: " << cargo.GetFactionName() << "\n";
	std::cout << "Atomic Number: " << cargo.GetAtomicNumber() << "\n";
	std::cout << "Relative Atomic Mass: " << cargo.GetRelativeAtomicMass() << "\n";
	std::cout << "State at 20°C: " << cargo.GetStateAt20() << "\n";
	std::cout << "Price: " << cargo.GetCargoPrice() << "\n";
}



void SpaceShip::AddEngine(const Engine& engine) {
	int next_key = engine_m.empty() ? 1 : engine_m.rbegin()->first + 1;
	engine_m.insert(std::make_pair(next_key, engine));
	price_ += engine.GetEnginePrice();
}


void SpaceShip::RemoveEngine() {
	if (engine_m.empty()) {
		throw std::runtime_error("Cannot remove engine: no engines installed");
	}
	else {
		auto last_it = engine_m.rbegin();
		price_ -= last_it->second.GetEnginePrice();
		engine_m.erase(std::prev(last_it.base()));
	}
}

void SpaceShip::AboutEngine(const Engine& engine) {
	std::cout << "\n";
	std::cout << "Name: " << engine.GetEngineName() << "\n";
	std::cout << "Faction: " << engine.GetFactionName() << "\n";
	std::cout << "Power Usage: " << engine.GetPowerUsage() << "\n";
	std::cout << "Radiation Level: " << engine.GetRadiationLevel() << "\n";
	std::cout << "Price: " << engine.GetEnginePrice() << "\n";
}

void SpaceShip::AddShield(const Shield& shield) {
	shield_v.push_back(shield);
	price_ += shield.GetShieldPrice();
}

void SpaceShip::RemoveShield() {
	if (shield_v.empty()) {
		throw std::runtime_error("Cannot remove shield: no shields installed");
	}
	else {
		price_ -= shield_v.back().GetShieldPrice();
		shield_v.pop_back();
	}
}

void SpaceShip::AboutShield(const Shield& shield) {
	std::cout << "\n";
	std::cout << "Name: " << shield.GetName() << "\n";
	std::cout << "Faction: " << shield.GetFactionName() << "\n";
	std::cout << "Armor Rating: " << shield.GetArmorRating() << "\n";
	std::cout << "Energy Capacity: " << shield.GetEnergyCapacity() << "\n";
	std::cout << "Capacity: " << shield.GetCapacity() << "\n";
	std::cout << "Regen Delay: " << shield.GetRegenDelay() << "\n";
	std::cout << "Regeneration Rate: " << shield.GetRegenerationRate() << "\n";
	std::cout << "Regen Power: " << shield.GetRegenPower() << "\n";
	std::cout << "Price: " << shield.GetShieldPrice() << "\n";
}


void SpaceShip::AddWeapon(const Weapon& weapon) {
	int next_key = guns_m.empty() ? 1 : guns_m.rbegin()->first + 1;
	guns_m.insert(std::make_pair(next_key, weapon));
	price_ += weapon.GetWeaponPrice();
}

void SpaceShip::RemoveWeapon() {
	if (guns_m.empty()) {
		throw std::runtime_error("Cannot remove weapon: no weapons installed");
	}
	else {
		auto last_it = guns_m.rbegin();
		price_ -= last_it->second.GetWeaponPrice();
		guns_m.erase(std::prev(last_it.base()));
	}
}

void SpaceShip::AboutWeapon(const Weapon& weapon) {
	std::cout << "\n";
	std::cout << "Name: " << weapon.GetName() << "\n";
	std::cout << "Faction: " << weapon.GetFactionName() << "\n";
	std::cout << "Rotation: " << weapon.GetRotation() << "\n";
	std::cout << "Life Time: " << weapon.GetLifeTime() << "\n";
	std::cout << "Travel Range: " << weapon.GetTravelRange() << "\n";
	std::cout << "Speed: " << weapon.GetSpeed() << "\n";
	std::cout << "Damage: " << weapon.GetDamage() << "\n";
	std::cout << "Price: " << weapon.GetWeaponPrice() << "\n";
}