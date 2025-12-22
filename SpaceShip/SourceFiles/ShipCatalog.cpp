#include "../HeaderFiles/Ships/ShipSpec.h"
#include "../HeaderFiles/json/json.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>

using json = nlohmann::json;

ShipCatalog& ShipCatalog::GetInstance() {
    static ShipCatalog instance;
    return instance;
}

bool ShipCatalog::LoadFromJSON(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file: " << filepath << std::endl;
        return false;
    }

    try {
        json j;
        file >> j;
        file.close();

        if (!j.contains("ships") || !j["ships"].is_array()) {
            std::cerr << "Error: JSON does not contain 'ships' array" << std::endl;
            return false;
        }

        for (const auto& item : j["ships"]) {
            ShipSpec spec;
            spec.id = item.value("id", "");
            spec.name = item.value("name", "");
            spec.faction = item.value("faction", "");
            spec.category = item.value("category", "");
            spec.hull = item.value("hull", 0.0);
            spec.max_shield = item.value("max_shield", 0);
            spec.cargo = item.value("cargo", 0);
            spec.speed = item.value("speed", 0);
            spec.price = item.value("price", 0);
            spec.description = item.value("description", "");

            try {
                spec.Validate();
                ships_[spec.id] = spec;
                ships_by_name_[ToLower(spec.name)] = spec.id;
                category_index_[spec.category].push_back(spec.id);
            } catch (const std::exception& e) {
                std::cerr << "Warning: Invalid ship spec '" << spec.name
                          << "': " << e.what() << std::endl;
            }
        }

        if (ships_.empty()) {
            std::cerr << "Error: No valid ships found in JSON" << std::endl;
            return false;
        }

        std::cout << "Successfully loaded " << ships_.size() << " ships" << std::endl;
        return true;

    } catch (const json::exception& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error loading ships: " << e.what() << std::endl;
        return false;
    }
}

const ShipSpec& ShipCatalog::GetSpecByID(const std::string& id) const {
    auto it = ships_.find(id);
    if (it == ships_.end()) {
        throw std::runtime_error("Ship ID not found: " + id);
    }
    return it->second;
}

const ShipSpec* ShipCatalog::GetSpecByIDSafe(const std::string& id) const {
    auto it = ships_.find(id);
    return (it != ships_.end()) ? &it->second : nullptr;
}

const ShipSpec& ShipCatalog::GetSpecByName(const std::string& name) const {
    auto it = ships_by_name_.find(ToLower(name));
    if (it == ships_by_name_.end()) {
        throw std::runtime_error("Ship name not found: " + name);
    }
    return GetSpecByID(it->second);
}

std::vector<ShipSpec> ShipCatalog::GetShipsByCategory(const std::string& category) const {
    std::vector<ShipSpec> result;
    auto it = category_index_.find(category);
    if (it != category_index_.end()) {
        for (const auto& id : it->second) {
            result.push_back(ships_.at(id));
        }
    }
    return result;
}

std::vector<std::string> ShipCatalog::GetAllShipIDs() const {
    std::vector<std::string> ids;
    for (const auto& pair : ships_) {
        ids.push_back(pair.first);
    }
    return ids;
}

std::vector<std::string> ShipCatalog::GetAllShipNames() const {
    std::vector<std::string> names;
    for (const auto& pair : ships_) {
        names.push_back(pair.second.name);
    }
    return names;
}

std::string ShipCatalog::ToLower(const std::string& str) const {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
