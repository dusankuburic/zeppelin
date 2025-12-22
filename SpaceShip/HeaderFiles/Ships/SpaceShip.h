#pragma once
#include "CargoManipulation.h"
#include "EngineManipulation.h"
#include "ShieldManipulation.h"
#include "WeaponManipulation.h"
#include<vector>
#include<map>
#include<iostream>

class SpaceShip :
	public CargoManipulation,
	public EngineManipulation,
	public ShieldManipulation,
	public WeaponManipulation {

public:
	SpaceShip();
	SpaceShip(const std::string& faction);
	SpaceShip(const std::string& faction, const int price);
	virtual ~SpaceShip(){}

	void ListCargo();
	void ListEngine();
	void ListShield();
	void ListWeapon();

	int64_t GetShipPrice() const;
	void SetShipPrice(const int64_t&);

	std::string GetFaction() const;
	void SetFaction(const std::string&);

	virtual void AddCargo(const Cargo&);
	virtual void RemoveCargo();
	virtual void AboutCargo(const Cargo&);

	virtual void AddEngine(const Engine&);
	virtual void RemoveEngine();
	virtual void AboutEngine(const Engine&);

	virtual void AddShield(const Shield&);
	virtual void RemoveShield();
	virtual void AboutShield(const Shield&);

	virtual void AddWeapon(const Weapon&);
	virtual void RemoveWeapon();
	virtual void AboutWeapon(const Weapon&);

protected:
	int64_t price_ = 0;

private:
	std::vector<Cargo> cargo_v;
	std::map<int, Engine> engine_m;
	std::map<int, Weapon> guns_m;
	std::vector<Shield> shield_v;
	std::string faction_;
};