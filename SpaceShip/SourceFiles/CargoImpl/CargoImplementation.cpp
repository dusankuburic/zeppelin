#include "Cargo.h"
#include <iostream>
#include <iomanip>

Cargo::Cargo(const std::string& name,
             const std::string& faction,
             int64_t price,
             int atomic_number,
             double relative_atomic_mass,
             const std::string& state_at_20,
             const std::string& description)
    : name_(name),
      faction_name_(faction),
      state_at_20_(state_at_20),
      description_(description),
      price_(price),
      atomic_number_(atomic_number),
      relative_atomic_mass_(relative_atomic_mass) {
}

std::ostream& operator<<(std::ostream& out, const Cargo& cargo) {
	out << "Name: " << cargo.GetCargoName() << "\n";
	out << "Faction: " << cargo.GetFactionName() << "\n";
	out << "Price: " << cargo.GetPrice() << "\n";
	out << "Atomic Number: " << cargo.GetAtomicNumber() << "\n";
	out << "Relative Atomic Mass: " << std::fixed << std::setprecision(3)
	    << cargo.GetRelativeAtomicMass() << "\n";
	out << "State at 20°C: " << cargo.GetStateAt20() << "\n";
	if (!cargo.GetDescription().empty()) {
		out << "Description: " << cargo.GetDescription() << "\n";
	}
	return out;
}