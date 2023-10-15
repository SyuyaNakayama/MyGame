#pragma once
#include "JsonLoader.h"

// ゲームに表示されているオブジェクトの基底クラス
class GameObject
{
public:
	virtual ~GameObject() = default;
	virtual void Initialize(const ObjectData& objectData) = 0;
	virtual void Update() = 0;
};