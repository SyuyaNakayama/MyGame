#include "Skydome.h"
#include "ModelManager.h"

void Skydome::Initialize(float scale)
{
	object = ModelManager::Create("skydome", true);
	object->worldTransform.scale *= scale;
}