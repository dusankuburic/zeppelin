#include "ComponentSpec.h"
#include "json/json.hpp"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>

using json = nlohmann::json;

bool ComponentCatalog::LoadFromJSON(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open components file: " << filepath << std::endl;
        return false;
    }

    try {
        json j;
        file >> j;
        file.close();

        if (j.contains("cargo") && j["cargo"].is_array()) {
            for (const auto& item : j["cargo"]) {
                CargoSpec spec;
                spec.id = item.value("id", "");
                spec.name = item.value("name", "");
                spec.faction = item.value("faction", "");
                spec.category = item.value("category", "");
                spec.price = item.value("price", 0);
                spec.atomic_number = item.value("atomic_number", 0);
                spec.relative_atomic_mass = item.value("relative_atomic_mass", 0.0);
                spec.state_at_20 = item.value("state_at_20", "");
                spec.description = item.value("description", "");

                if (spec.IsValid()) {
                    cargo_specs_[spec.id] = spec;
                }
            }
        }

        if (j.contains("engines") && j["engines"].is_array()) {
            for (const auto& item : j["engines"]) {
                EngineSpec spec;
                spec.id = item.value("id", "");
                spec.name = item.value("name", "");
                spec.faction = item.value("faction", "");
                spec.category = item.value("category", "");
                spec.price = item.value("price", 0);
                spec.power_usage = item.value("power_usage", 0);
                spec.radiation_level = item.value("radiation_level", 0);
                spec.description = item.value("description", "");

                if (spec.IsValid()) {
                    engine_specs_[spec.id] = spec;
                }
            }
        }

        if (j.contains("shields") && j["shields"].is_array()) {
            for (const auto& item : j["shields"]) {
                ShieldSpec spec;
                spec.id = item.value("id", "");
                spec.name = item.value("name", "");
                spec.faction = item.value("faction", "");
                spec.category = item.value("category", "");
                spec.price = item.value("price", 0);
                spec.armor_rating = item.value("armor_rating", 0);
                spec.energy_capacity = item.value("energy_capacity", 0);
                spec.capacity = item.value("capacity", 0);
                spec.regen_delay = item.value("regen_delay", 0);
                spec.regeneration_rate = item.value("regeneration_rate", 0);
                spec.regen_power = item.value("regen_power", 0);
                spec.description = item.value("description", "");

                if (spec.IsValid()) {
                    shield_specs_[spec.id] = spec;
                }
            }
        }

        if (j.contains("weapons") && j["weapons"].is_array()) {
            for (const auto& item : j["weapons"]) {
                WeaponSpec spec;
                spec.id = item.value("id", "");
                spec.name = item.value("name", "");
                spec.faction = item.value("faction", "");
                spec.category = item.value("category", "");
                spec.price = item.value("price", 0);
                spec.rotation = item.value("rotation", 0);
                spec.life_time = item.value("life_time", 0.0);
                spec.travel_range = item.value("travel_range", 0);
                spec.speed = item.value("speed", 0);
                spec.damage = item.value("damage", 0);
                spec.description = item.value("description", "");

                if (spec.IsValid()) {
                    weapon_specs_[spec.id] = spec;
                }
            }
        }

        std::cout << "Loaded " << cargo_specs_.size() << " cargo types, "
                  << engine_specs_.size() << " engine types, "
                  << shield_specs_.size() << " shield types, "
                  << weapon_specs_.size() << " weapon types" << std::endl;

        return !cargo_specs_.empty() || !engine_specs_.empty() ||
               !shield_specs_.empty() || !weapon_specs_.empty();

    } catch (const json::exception& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        return false;
    }
}

const CargoSpec* ComponentCatalog::GetCargoSpec(const std::string& id) const {
    auto it = cargo_specs_.find(id);
    return (it != cargo_specs_.end()) ? &it->second : nullptr;
}

std::vector<std::string> ComponentCatalog::GetAllCargoIDs() const {
    std::vector<std::string> ids;
    for (const auto& pair : cargo_specs_) {
        ids.push_back(pair.first);
    }
    return ids;
}

const EngineSpec* ComponentCatalog::GetEngineSpec(const std::string& id) const {
    auto it = engine_specs_.find(id);
    return (it != engine_specs_.end()) ? &it->second : nullptr;
}

std::vector<std::string> ComponentCatalog::GetAllEngineIDs() const {
    std::vector<std::string> ids;
    for (const auto& pair : engine_specs_) {
        ids.push_back(pair.first);
    }
    return ids;
}

const ShieldSpec* ComponentCatalog::GetShieldSpec(const std::string& id) const {
    auto it = shield_specs_.find(id);
    return (it != shield_specs_.end()) ? &it->second : nullptr;
}

std::vector<std::string> ComponentCatalog::GetAllShieldIDs() const {
    std::vector<std::string> ids;
    for (const auto& pair : shield_specs_) {
        ids.push_back(pair.first);
    }
    return ids;
}

const WeaponSpec* ComponentCatalog::GetWeaponSpec(const std::string& id) const {
    auto it = weapon_specs_.find(id);
    return (it != weapon_specs_.end()) ? &it->second : nullptr;
}

std::vector<std::string> ComponentCatalog::GetAllWeaponIDs() const {
    std::vector<std::string> ids;
    for (const auto& pair : weapon_specs_) {
        ids.push_back(pair.first);
    }
    return ids;
}


void ComponentCatalog::PrintComponentCatalog() const {
    std::cout << "\n=== COMPONENT CATALOG ===" << std::endl;

    std::cout << "\nCARGO (" << cargo_specs_.size() << " types):" << std::endl;
    for (const auto& pair : cargo_specs_) {
        const auto& spec = pair.second;
        std::cout << "  - " << spec.name << " (ID: " << spec.id << ", Price: "
                  << spec.price << ")" << std::endl;
    }

    std::cout << "\nENGINES (" << engine_specs_.size() << " types):" << std::endl;
    for (const auto& pair : engine_specs_) {
        const auto& spec = pair.second;
        std::cout << "  - " << spec.name << " (ID: " << spec.id << ", Price: "
                  << spec.price << ")" << std::endl;
    }

    std::cout << "\nSHIELDS (" << shield_specs_.size() << " types):" << std::endl;
    for (const auto& pair : shield_specs_) {
        const auto& spec = pair.second;
        std::cout << "  - " << spec.name << " (ID: " << spec.id << ", Price: "
                  << spec.price << ")" << std::endl;
    }

    std::cout << "\nWEAPONS (" << weapon_specs_.size() << " types):" << std::endl;
    for (const auto& pair : weapon_specs_) {
        const auto& spec = pair.second;
        std::cout << "  - " << spec.name << " (ID: " << spec.id << ", Price: "
                  << spec.price << ")" << std::endl;
    }
}
