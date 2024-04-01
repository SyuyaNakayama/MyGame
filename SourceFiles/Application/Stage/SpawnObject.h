#pragma once
#include "AbstractSpawnPoint.h"
#include "Object.h"
#include "Random.h"

// このゲームでのスポーンオブジェクト基底クラス
class BaseSpawnObject : public WristerEngine::AbstractSpawnPoint, public WristerEngine::_3D::GameObject
{
protected:
	static std::list<std::unique_ptr<WristerEngine::_3D::GameObject>>* objects;
	ObjectData objectData;
	Vector3 initialPos;
	std::unique_ptr<const int> SPAWN_MAX = nullptr;
	WristerEngine::Roulette roulette;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="objectData">Jsonファイルから読み込んだデータ</param>
	virtual void Initialize(const ObjectData& objectData);

	// 更新
	virtual void Update();

	// Typeを設定
	virtual ObjectType GetType() = 0;

	// ObjectListをセット
	static void SetObjectList(std::list<std::unique_ptr<WristerEngine::_3D::GameObject>>* list) { objects = list; }
};

// オブジェクト生成オブジェクト
class SpawnObject : public BaseSpawnObject
{

public:
	void Initialize(const ObjectData& objectData_) override;

	// 更新
	void Update();

	// BaseSpawnObject を介して継承されました
	ObjectType GetType() override;
};

// チュートリアルのスポーンオブジェクト
class TutorialSpawnObject : public BaseSpawnObject
{
private:
	UINT32 phase;
	const TutorialEvent* tutorialEvent = TutorialEvent::GetInstance();
	const std::vector<UINT32>* tutorialEventPhase = nullptr;

public:
	void Initialize(const ObjectData& objectData_) override;

	// 更新
	void Update();

	// BaseSpawnObject を介して継承されました
	ObjectType GetType() override;
};