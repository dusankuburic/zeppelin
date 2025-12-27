#pragma once
#include "Weapon.h"

class WeaponManipulation {
public:
	virtual ~WeaponManipulation() = default;
	virtual void AddWeapon(const Weapon&) = 0;
	virtual void RemoveWeapon() = 0;
	virtual void AboutWeapon(const Weapon&) = 0;
};