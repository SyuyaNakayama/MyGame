#pragma once
#include "JsonLoader.h"

// ゲームに表示されているオブジェクトの基底クラス
class GameObject
{
public:
	// 仮想デストラクタ
	virtual ~GameObject() = default;
	/// <summary>
	/// 初期化(純粋仮想関数)
	/// </summary>
	/// <param name="objectData">Jsonファイルから読み込んだデータ</param>
	virtual void Initialize(const ObjectData& objectData) = 0;
	// 更新(純粋仮想関数)
	virtual void Update() = 0;
};