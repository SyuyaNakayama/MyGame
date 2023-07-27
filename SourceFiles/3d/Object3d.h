#pragma once
#include "Mesh.h"
#include "WorldTransform.h"

struct Object3d
{
	friend class ModelManager;
	
	Material material;
	WorldTransform worldTransform;

	void Update();
	void Draw();

private:
	Mesh* mesh;
};