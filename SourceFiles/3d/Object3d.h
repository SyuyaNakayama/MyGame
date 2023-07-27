#pragma once
#include "Mesh.h"
#include "WorldTransform.h"

struct Object3d
{
	Material material;
	WorldTransform worldTransform;

	void Initialize(const std::string& modelName);
	void Update();
	void Draw();

private:
	Mesh* mesh;
};