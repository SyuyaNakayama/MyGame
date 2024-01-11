#include "Skydome.h"
#include "ModelManager.h"

void WristerEngine::Skydome::Initialize(float scale)
{
	object = ModelManager::Create("skydome", true);
	object->worldTransform->scale *= scale;
}