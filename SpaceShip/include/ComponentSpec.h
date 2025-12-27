#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <iostream>

struct CargoSpec {
    std::string id;
    std::string name;
    std::string faction;
    std::string category;
    int64_t price;
    int atomic_number;
    double relative_atomic_mass;
    std::string state_at_20;
    std::string description;

    CargoSpec() : price(0), atomic_number(0), relative_atomic_mass(0.0) {}

    bool IsValid() const {
        return !id.empty() && !name.empty() && price >= 0;
    }
};

struct EngineSpec {
    std::string id;
    std::string name;
    std::string faction;
    std::string category;
    int64_t price;
    int power_usage;
    int radiation_level;
    std::string description;

    EngineSpec() : price(0), power_usage(0), radiation_level(0) {}

    bool IsValid() const {
        return !id.empty() && !name.empty() && price >= 0;
    }
};

struct ShieldSpec {
    std::string id;
    std::string name;
    std::string faction;
    std::string category;
    int64_t price;
    int armor_rating;
    int energy_capacity;
    int capacity;
    int regen_delay;
    int regeneration_rate;
    int regen_power;
    std::string description;

    ShieldSpec() : price(0), armor_rating(0), energy_capacity(0),
                   capacity(0), regen_delay(0), regeneration_rate(0),
                   regen_power(0) {}

    bool IsValid() const {
        return !id.empty() && !name.empty() && price >= 0;
    }
};

struct WeaponSpec {
    std::string id;
    std::string name;
    std::string faction;
    std::string category;
    int64_t price;
    int rotation;
    double life_time;
    int travel_range;
    int speed;
    int damage;
    std::string description;

    WeaponSpec() : price(0), rotation(0), life_time(0.0),
                   travel_range(0), speed(0), damage(0) {}

    bool IsValid() const {
        return !id.empty() && !name.empty() && price >= 0;
    }
};

class ComponentCatalog {
public:
    
    static ComponentCatalog& GetInstance() {
        static ComponentCatalog instance;
        return instance;
    }

    
    ComponentCatalog(const ComponentCatalog&) = delete;
    ComponentCatalog& operator=(const ComponentCatalog&) = delete;

    
    bool LoadFromJSON(const std::string& filepath);

    
    const CargoSpec* GetCargoSpec(const std::string& id) const;
    std::vector<std::string> GetAllCargoIDs() const;
    size_t GetCargoCount() const { return cargo_specs_.size(); }

    
    const EngineSpec* GetEngineSpec(const std::string& id) const;
    std::vector<std::string> GetAllEngineIDs() const;
    size_t GetEngineCount() const { return engine_specs_.size(); }

    
    const ShieldSpec* GetShieldSpec(const std::string& id) const;
    std::vector<std::string> GetAllShieldIDs() const;
    size_t GetShieldCount() const { return shield_specs_.size(); }

    
    const WeaponSpec* GetWeaponSpec(const std::string& id) const;
    std::vector<std::string> GetAllWeaponIDs() const;
    size_t GetWeaponCount() const { return weapon_specs_.size(); }

    
    void PrintComponentCatalog() const;

private:
    ComponentCatalog() = default;
    ~ComponentCatalog() = default;

    std::map<std::string, CargoSpec> cargo_specs_;
    std::map<std::string, EngineSpec> engine_specs_;
    std::map<std::string, ShieldSpec> shield_specs_;
    std::map<std::string, WeaponSpec> weapon_specs_;
};
