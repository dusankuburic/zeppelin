#pragma once
#include "Shield.h"

class ShieldManipulation {
public:
	virtual ~ShieldManipulation() = default;
	virtual void AddShield(const Shield&) = 0;
	virtual void RemoveShield() = 0;
	virtual void AboutShield(const Shield&) = 0;
};