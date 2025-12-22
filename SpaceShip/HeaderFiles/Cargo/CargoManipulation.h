#pragma once
#include "Cargo.h"

class CargoManipulation {
public:
	virtual ~CargoManipulation() = default;
	virtual void AddCargo(const Cargo&) = 0;
	virtual void RemoveCargo() = 0;
	virtual void AboutCargo(const Cargo&) = 0;
};