#include "ComponentFactory.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

Cargo ComponentFactory::CreateCargoByID(const std::string& id) {
    const CargoSpec* spec = ComponentCatalog::GetInstance().GetCargoSpec(id);
    if (!spec) {
        std::cerr << "Warning: Cargo ID '" << id << "' not found. Creating default cargo." << std::endl;
        return Cargo();
    }

    return Cargo(spec->name,
                 spec->faction,
                 spec->price,
                 spec->atomic_number,
                 spec->relative_atomic_mass,
                 spec->state_at_20,
                 spec->description);
}

Cargo ComponentFactory::CreateCargoByName(const std::string& name) {
    const CargoSpec* spec = FindCargoByName(name);
    if (!spec) {
        std::cerr << "Warning: Cargo '" << name << "' not found. Creating default cargo." << std::endl;
        return Cargo();
    }
    return CreateCargoByID(spec->id);
}

std::vector<Cargo> ComponentFactory::CreateAllCargo() {
    std::vector<Cargo> all_cargo;
    std::vector<std::string> ids = ComponentCatalog::GetInstance().GetAllCargoIDs();

    for (const auto& id : ids) {
        all_cargo.push_back(CreateCargoByID(id));
    }

    return all_cargo;
}

void ComponentFactory::PrintCargoCatalog() {
    ComponentCatalog::GetInstance().PrintComponentCatalog();
}

Engine ComponentFactory::CreateEngineByID(const std::string& id) {
    const EngineSpec* spec = ComponentCatalog::GetInstance().GetEngineSpec(id);
    if (!spec) {
        std::cerr << "Warning: Engine ID '" << id << "' not found. Creating default engine." << std::endl;
        return Engine();
    }

    return Engine(spec->name,
                  spec->faction,
                  spec->price,
                  spec->power_usage,
                  spec->radiation_level,
                  spec->description);
}

Engine ComponentFactory::CreateEngineByName(const std::string& name) {
    const EngineSpec* spec = FindEngineByName(name);
    if (!spec) {
        std::cerr << "Warning: Engine '" << name << "' not found. Creating default engine." << std::endl;
        return Engine();
    }
    return CreateEngineByID(spec->id);
}

std::vector<Engine> ComponentFactory::CreateAllEngines() {
    std::vector<Engine> all_engines;
    std::vector<std::string> ids = ComponentCatalog::GetInstance().GetAllEngineIDs();

    for (const auto& id : ids) {
        all_engines.push_back(CreateEngineByID(id));
    }

    return all_engines;
}

void ComponentFactory::PrintEngineCatalog() {
    ComponentCatalog::GetInstance().PrintComponentCatalog();
}

Shield ComponentFactory::CreateShieldByID(const std::string& id) {
    const ShieldSpec* spec = ComponentCatalog::GetInstance().GetShieldSpec(id);
    if (!spec) {
        std::cerr << "Warning: Shield ID '" << id << "' not found. Creating default shield." << std::endl;
        return Shield();
    }

    return Shield(spec->name,
                  spec->faction,
                  spec->price,
                  spec->armor_rating,
                  spec->energy_capacity,
                  spec->capacity,
                  spec->regen_delay,
                  spec->regeneration_rate,
                  spec->regen_power,
                  spec->description);
}

Shield ComponentFactory::CreateShieldByName(const std::string& name) {
    const ShieldSpec* spec = FindShieldByName(name);
    if (!spec) {
        std::cerr << "Warning: Shield '" << name << "' not found. Creating default shield." << std::endl;
        return Shield();
    }
    return CreateShieldByID(spec->id);
}

std::vector<Shield> ComponentFactory::CreateAllShields() {
    std::vector<Shield> all_shields;
    std::vector<std::string> ids = ComponentCatalog::GetInstance().GetAllShieldIDs();

    for (const auto& id : ids) {
        all_shields.push_back(CreateShieldByID(id));
    }

    return all_shields;
}

void ComponentFactory::PrintShieldCatalog() {
    ComponentCatalog::GetInstance().PrintComponentCatalog();
}

Weapon ComponentFactory::CreateWeaponByID(const std::string& id) {
    const WeaponSpec* spec = ComponentCatalog::GetInstance().GetWeaponSpec(id);
    if (!spec) {
        std::cerr << "Warning: Weapon ID '" << id << "' not found. Creating default weapon." << std::endl;
        return Weapon();
    }

    return Weapon(spec->name,
                  spec->faction,
                  spec->price,
                  spec->rotation,
                  spec->life_time,
                  spec->travel_range,
                  spec->speed,
                  spec->damage,
                  spec->description);
}

Weapon ComponentFactory::CreateWeaponByName(const std::string& name) {
    const WeaponSpec* spec = FindWeaponByName(name);
    if (!spec) {
        std::cerr << "Warning: Weapon '" << name << "' not found. Creating default weapon." << std::endl;
        return Weapon();
    }
    return CreateWeaponByID(spec->id);
}

std::vector<Weapon> ComponentFactory::CreateAllWeapons() {
    std::vector<Weapon> all_weapons;
    std::vector<std::string> ids = ComponentCatalog::GetInstance().GetAllWeaponIDs();

    for (const auto& id : ids) {
        all_weapons.push_back(CreateWeaponByID(id));
    }

    return all_weapons;
}

void ComponentFactory::PrintWeaponCatalog() {
    ComponentCatalog::GetInstance().PrintComponentCatalog();
}

const CargoSpec* ComponentFactory::FindCargoByName(const std::string& name) {
    std::vector<std::string> ids = ComponentCatalog::GetInstance().GetAllCargoIDs();
    std::string lower_name = ToLower(name);

    for (const auto& id : ids) {
        const CargoSpec* spec = ComponentCatalog::GetInstance().GetCargoSpec(id);
        if (spec && ToLower(spec->name) == lower_name) {
            return spec;
        }
    }
    return nullptr;
}

const EngineSpec* ComponentFactory::FindEngineByName(const std::string& name) {
    std::vector<std::string> ids = ComponentCatalog::GetInstance().GetAllEngineIDs();
    std::string lower_name = ToLower(name);

    for (const auto& id : ids) {
        const EngineSpec* spec = ComponentCatalog::GetInstance().GetEngineSpec(id);
        if (spec && ToLower(spec->name) == lower_name) {
            return spec;
        }
    }
    return nullptr;
}

const ShieldSpec* ComponentFactory::FindShieldByName(const std::string& name) {
    std::vector<std::string> ids = ComponentCatalog::GetInstance().GetAllShieldIDs();
    std::string lower_name = ToLower(name);

    for (const auto& id : ids) {
        const ShieldSpec* spec = ComponentCatalog::GetInstance().GetShieldSpec(id);
        if (spec && ToLower(spec->name) == lower_name) {
            return spec;
        }
    }
    return nullptr;
}

const WeaponSpec* ComponentFactory::FindWeaponByName(const std::string& name) {
    std::vector<std::string> ids = ComponentCatalog::GetInstance().GetAllWeaponIDs();
    std::string lower_name = ToLower(name);

    for (const auto& id : ids) {
        const WeaponSpec* spec = ComponentCatalog::GetInstance().GetWeaponSpec(id);
        if (spec && ToLower(spec->name) == lower_name) {
            return spec;
        }
    }
    return nullptr;
}

std::string ComponentFactory::ToLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
