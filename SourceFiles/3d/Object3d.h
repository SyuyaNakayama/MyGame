#pragma once
#include "Mesh.h"
#include "WorldTransform.h"

struct Object3d
{
	Material material;
	WorldTransform worldTransform;

private:
	Mesh* mesh;
};