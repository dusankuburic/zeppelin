#include "../HeaderFiles/Ships/Ship.h"
#include <sstream>
#include <iomanip>

Ship::Ship(const ShipSpec& spec, const std::string& faction)
    : SpaceShip(faction.empty() ? spec.faction : faction, spec.price),
      ship_id_(spec.id),
      ship_name_(spec.name),
      category_(spec.category),
      hull_strength_(spec.hull),
      max_shield_class_(spec.max_shield),
      cargo_space_(spec.cargo),
      max_impulse_speed_(spec.speed),
      description_(spec.description) {
    try {
        spec.Validate();
    } catch (const std::exception& e) {
        throw std::invalid_argument(
            std::string("Invalid ship specification: ") + e.what()
        );
    }
}

Ship::Ship(const std::string& ship_id, const std::string& faction)
    : Ship(ShipCatalog::GetInstance().GetSpecByID(ship_id), faction) {
}

Ship::Ship(const Ship& other)
    : SpaceShip(other),
      ship_id_(other.ship_id_),
      ship_name_(other.ship_name_),
      category_(other.category_),
      hull_strength_(other.hull_strength_),
      max_shield_class_(other.max_shield_class_),
      cargo_space_(other.cargo_space_),
      max_impulse_speed_(other.max_impulse_speed_),
      description_(other.description_) {
}

Ship& Ship::operator=(const Ship& other) {
    if (this != &other) {
        SpaceShip::operator=(other);
        ship_id_ = other.ship_id_;
        ship_name_ = other.ship_name_;
        category_ = other.category_;
        hull_strength_ = other.hull_strength_;
        max_shield_class_ = other.max_shield_class_;
        cargo_space_ = other.cargo_space_;
        max_impulse_speed_ = other.max_impulse_speed_;
        description_ = other.description_;
    }
    return *this;
}

const std::string& Ship::GetShipID() const {
    return ship_id_;
}

const std::string& Ship::GetShipName() const {
    return ship_name_;
}

const std::string& Ship::GetCategory() const {
    return category_;
}

double Ship::GetHullStrength() const {
    return hull_strength_;
}

int Ship::GetMaxShieldClass() const {
    return max_shield_class_;
}

int Ship::GetCargoSpace() const {
    return cargo_space_;
}

int Ship::GetMaxImpulseSpeed() const {
    return max_impulse_speed_;
}

const std::string& Ship::GetDescription() const {
    return description_;
}

// ============================================================================
// Setters
// ============================================================================

void Ship::SetHullStrength(double hull) {
    hull_strength_ = hull;
}

void Ship::SetMaxShieldClass(int shield_class) {
    max_shield_class_ = shield_class;
}

void Ship::SetCargoSpace(int cargo) {
    cargo_space_ = cargo;
}

void Ship::SetMaxImpulseSpeed(int speed) {
    max_impulse_speed_ = speed;
}

void Ship::SetDescription(const std::string& description) {
    description_ = description;
}

std::string Ship::GetInfo() const {
    std::ostringstream oss;

    oss << "\n";
    oss << "================================================================================\n";
    oss << "Ship Information\n";
    oss << "================================================================================\n";
    oss << std::setw(25) << std::left << "ID:" << ship_id_ << "\n";
    oss << std::setw(25) << std::left << "Name:" << ship_name_ << "\n";
    oss << std::setw(25) << std::left << "Category:" << category_ << "\n";
    oss << std::setw(25) << std::left << "Faction:" << GetFaction() << "\n";

    oss << "\nPhysical Properties:\n";
    oss << std::setw(25) << std::left << "  Hull Strength:" << hull_strength_ << "\n";
    oss << std::setw(25) << std::left << "  Max Shield Class:" << max_shield_class_ << "\n";
    oss << std::setw(25) << std::left << "  Cargo Space:" << cargo_space_ << "\n";
    oss << std::setw(25) << std::left << "  Max Impulse Speed:" << max_impulse_speed_ << "\n";

    oss << "\nEconomic Properties:\n";
    oss << std::setw(25) << std::left << "  Base Price:" << GetShipPrice() << "\n";

    if (!description_.empty()) {
        oss << "\nDescription:\n";
        oss << "  " << description_ << "\n";
    }

    oss << "================================================================================\n";

    return oss.str();
}

std::ostream& operator<<(std::ostream& out, const Ship& ship) {
    out << "\n";
    out << "Name: " << ship.GetShipName() << "\n";
    out << "ID: " << ship.GetShipID() << "\n";
    out << "Category: " << ship.GetCategory() << "\n";
    out << "Faction: " << ship.GetFaction() << "\n";
    out << "Hull strength: " << ship.GetHullStrength() << "\n";
    out << "Max Shield class: " << ship.GetMaxShieldClass() << "\n";
    out << "Cargo space: " << ship.GetCargoSpace() << "\n";
    out << "Max Impulse speed: " << ship.GetMaxImpulseSpeed() << "\n";
    out << "Price: " << ship.GetShipPrice() << "\n";

    if (!ship.GetDescription().empty()) {
        out << "Description: " << ship.GetDescription() << "\n";
    }

    return out;
}

Ship Ship::CloneWithFaction(const std::string& faction) const {
    Ship cloned(*this);
    cloned.SetFaction(faction);
    return cloned;
}
