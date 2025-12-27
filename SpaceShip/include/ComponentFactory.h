#pragma once
#include "ComponentSpec.h"
#include "Cargo.h"
#include "Engine.h"
#include "Shield.h"
#include "Weapon.h"
#include <memory>

class ComponentFactory {
public:
    static Cargo CreateCargoByID(const std::string& id);
    static Cargo CreateCargoByName(const std::string& name);
    static std::vector<Cargo> CreateAllCargo();
    static void PrintCargoCatalog();

    static Engine CreateEngineByID(const std::string& id);
    static Engine CreateEngineByName(const std::string& name);
    static std::vector<Engine> CreateAllEngines();
    static void PrintEngineCatalog();

    static Shield CreateShieldByID(const std::string& id);
    static Shield CreateShieldByName(const std::string& name);
    static std::vector<Shield> CreateAllShields();
    static void PrintShieldCatalog();

    static Weapon CreateWeaponByID(const std::string& id);
    static Weapon CreateWeaponByName(const std::string& name);
    static std::vector<Weapon> CreateAllWeapons();
    static void PrintWeaponCatalog();

private:
    static const CargoSpec* FindCargoByName(const std::string& name);
    static const EngineSpec* FindEngineByName(const std::string& name);
    static const ShieldSpec* FindShieldByName(const std::string& name);
    static const WeaponSpec* FindWeaponByName(const std::string& name);

    static std::string ToLower(const std::string& str);
};
