#pragma once

#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <stdexcept>

struct ShipSpec {
    std::string id;
    std::string name;
    std::string faction;
    std::string category;

    double hull;
    int max_shield;
    int cargo;
    int speed;

    int64_t price;

    std::string description;

    void Validate() const {
        if (id.empty()) throw std::invalid_argument("ShipSpec: id is empty");
        if (name.empty()) throw std::invalid_argument("ShipSpec: name is empty");
        if (category.empty()) throw std::invalid_argument("ShipSpec: category is empty");
        if (hull <= 0) throw std::invalid_argument("ShipSpec: hull must be > 0");
        if (max_shield < 0) throw std::invalid_argument("ShipSpec: max_shield cannot be negative");
        if (cargo < 0) throw std::invalid_argument("ShipSpec: cargo cannot be negative");
        if (speed < 0) throw std::invalid_argument("ShipSpec: speed cannot be negative");
        if (price < 0) throw std::invalid_argument("ShipSpec: price cannot be negative");
    }

    bool IsValid() const {
        try {
            Validate();
            return true;
        } catch (...) {
            return false;
        }
    }

    bool operator==(const ShipSpec& other) const {
        return id == other.id;
    }
};

class ShipCatalog {
public:
    static ShipCatalog& GetInstance();

    bool LoadFromJSON(const std::string& filename);

    const ShipSpec& GetSpecByID(const std::string& id) const;

    const ShipSpec* GetSpecByIDSafe(const std::string& id) const;

    const ShipSpec& GetSpecByName(const std::string& name) const;

    std::vector<std::string> GetAllShipIDs() const;

    std::vector<std::string> GetAllShipNames() const;

    std::vector<ShipSpec> GetShipsByCategory(const std::string& category) const;

    size_t GetShipCount() const { return ships_.size(); }

    bool HasShip(const std::string& id) const { return ships_.find(id) != ships_.end(); }

    void Clear() { ships_.clear(); ships_by_name_.clear(); category_index_.clear(); }

private:
    ShipCatalog() = default;

    ShipCatalog(const ShipCatalog&) = delete;
    ShipCatalog& operator=(const ShipCatalog&) = delete;

    std::string ToLower(const std::string& str) const;

    std::map<std::string, ShipSpec> ships_;
    std::map<std::string, std::string> ships_by_name_;
    std::map<std::string, std::vector<std::string>> category_index_;
};
