#pragma once
#include "LevelLoader.h"
#include "Input.h"
#include "SceneManager.h"
#include "Constant.h"

namespace WristerEngine::_3D
{
	// ゲームに表示されている3Dオブジェクトの基底クラス
	class GameObject
	{
	protected:
		Input* input = Input::GetInstance();
		Constant* constant = Constant::GetInstance();

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
		// 現在のシーンを取得
		Scene GetNowScene() const { return SceneManager::GetInstance()->GetNowScene(); }
	};
}