#pragma once
#include "JsonLoader.h"

class GameObject
{
public:
	virtual ~GameObject() = default;
	virtual void Initialize(const ObjectData& objectData) = 0;
	virtual void Update() = 0;
};