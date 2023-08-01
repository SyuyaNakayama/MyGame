#pragma once
#include "Mesh.h"
#include "WorldTransform.h"

struct Object3d
{
	Material material;
	std::unique_ptr<WorldTransform> worldTransform;
	bool isDestroy = false;
	bool isInvisible = false;

private:
	friend class ModelManager;	
	Mesh* mesh;
	void Initialize(Mesh* mesh);
	void Update();
	void Draw();
};