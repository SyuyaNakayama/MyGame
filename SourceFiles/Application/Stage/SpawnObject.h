#pragma once
#include "AbstractSpawnPoint.h"
#include "Object.h"
#include "Random.h"

// 前方定義
class BaseSpawnObject;

// チュートリアルシーンでSpawnObjectをチュートリアル用からプレイ用に切り替えるためのマネージャークラス
class SpawnObjectManager final
{
private:
	std::list<std::unique_ptr<WristerEngine::_3D::GameObject>>* objects = nullptr;
	BaseSpawnObject* spawnObject = nullptr;
	std::unique_ptr<WristerEngine::_3D::GameObject> nextSpawnObject;

	SpawnObjectManager() = default;
	~SpawnObjectManager() = default;

public:
	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>SpawnObjectmanagerインスタンス</returns>
	static SpawnObjectManager* GetInstance();

	SpawnObjectManager(const SpawnObjectManager& obj) = delete;
	SpawnObjectManager& operator=(const SpawnObjectManager& obj) = delete;

	// オブジェクトを追加
	void AddObject(const ObjectData& objectData);
	// ObjectListをセット
	void SetObjectList(std::list<std::unique_ptr<WristerEngine::_3D::GameObject>>* list) { objects = list; }
	// SpawnObjectをセット
	void SetSpawnObject(WristerEngine::_3D::GameObject* spawnObject_);
	// SpawnObjectを変更
	void ChangeSpawnObject();
	// SpawnObjectを変更する予約をする
	void ReserveChange(std::unique_ptr<WristerEngine::_3D::GameObject> spawnObject);
};

// このゲームでのスポーンオブジェクト基底クラス
class BaseSpawnObject : public WristerEngine::AbstractSpawnPoint, public WristerEngine::_3D::GameObject
{
protected:
	SpawnObjectManager* manager = SpawnObjectManager::GetInstance();
	ObjectData objectData;
	Vector3 initialPos;
	std::unique_ptr<const int> SPAWN_MAX = nullptr;

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
};

// オブジェクト生成オブジェクト
class SpawnObject : public BaseSpawnObject
{
	WristerEngine::Roulette roulette;

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