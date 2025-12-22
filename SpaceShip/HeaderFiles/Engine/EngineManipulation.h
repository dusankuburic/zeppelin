#pragma once
#include "Engine.h"

class EngineManipulation {
public:
	virtual ~EngineManipulation() = default;
	virtual void AddEngine(const Engine&) = 0;
	virtual void RemoveEngine() = 0;
	virtual void AboutEngine(const Engine&) = 0;
};