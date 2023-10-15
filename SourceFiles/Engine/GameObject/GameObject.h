#pragma once
#include "JsonLoader.h"

// �Q�[���ɕ\������Ă���I�u�W�F�N�g�̊��N���X
class GameObject
{
public:
	virtual ~GameObject() = default;
	virtual void Initialize(const ObjectData& objectData) = 0;
	virtual void Update() = 0;
};