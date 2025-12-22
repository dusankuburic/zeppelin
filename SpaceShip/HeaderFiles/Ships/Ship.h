#pragma once

#include "SpaceShip.h"
#include "ShipSpec.h"
#include <string>
#include <iostream>

class Ship : public SpaceShip {
private:
    std::string ship_id_;
    std::string ship_name_;
    std::string category_;
    double hull_strength_;
    int max_shield_class_;
    int cargo_space_;
    int max_impulse_speed_;
    std::string description_;

public:
    Ship(const ShipSpec& spec, const std::string& faction = "");

    Ship(const std::string& ship_id, const std::string& faction);

    Ship(const Ship& other);

    Ship& operator=(const Ship& other);

    virtual ~Ship() = default;

    const std::string& GetShipID() const;

    const std::string& GetShipName() const;

    const std::string& GetCategory() const;

    double GetHullStrength() const;

    int GetMaxShieldClass() const;

    int GetCargoSpace() const;

    int GetMaxImpulseSpeed() const;

    const std::string& GetDescription() const;

    void SetHullStrength(double hull);

    void SetMaxShieldClass(int shield_class);

    void SetCargoSpace(int cargo);

    void SetMaxImpulseSpeed(int speed);

    void SetDescription(const std::string& description);

    std::string GetInfo() const;

    friend std::ostream& operator<<(std::ostream& out, const Ship& ship);

    Ship CloneWithFaction(const std::string& faction) const;
};
