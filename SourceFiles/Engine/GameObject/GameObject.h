#pragma once

class GameObject
{
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};