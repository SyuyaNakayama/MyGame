#pragma once
#include "AbstractSpawnPoint.h"
#include "Object.h"

// このゲームでのスポーンオブジェクト基底クラス
class BaseSpawnObject : public WristerEngine::AbstractSpawnPoint, public WristerEngine::_3D::GameObject
{
protected:
	static std::list<std::unique_ptr<WristerEngine::_3D::GameObject>>* objects;
	WristerEngine::ObjectData objectData;
	Vector3 initialPos;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="objectData_">Jsonファイルから読み込んだデータ</param>
	void Initialize(const WristerEngine::ObjectData& objectData_);

	// 更新
	virtual void Update();

	// ObjectListをセット
	static void SetObjectList(std::list<std::unique_ptr<WristerEngine::_3D::GameObject>>* list) { objects = list; }
};

// オブジェクト生成オブジェクト
class SpawnObject : public BaseSpawnObject
{
	static const int SPAWN_MAX = 25;

private:


public:
	// 更新
	void Update();
};

// チュートリアルのスポーンオブジェクト
class TutorialSpawnObject : public BaseSpawnObject
{
	static const int SPAWN_MAX = 2;

public:
	// 更新
	void Update();
};