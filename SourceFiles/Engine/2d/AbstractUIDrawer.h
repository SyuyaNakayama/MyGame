#pragma once

namespace WristerEngine
{
	namespace _2D
	{
		// UI描画の抽象クラス
		// 各シーンごとにUIDrawerクラスを定義する
		class AbstractUIDrawer
		{
		public:
			// 仮想デストラクタ
			virtual ~AbstractUIDrawer() = default;
			// 初期化(純粋仮想関数)
			virtual void Initialize() = 0;
			// 更新(純粋仮想関数)
			virtual void Update() = 0;
			// 描画(純粋仮想関数)
			virtual void Draw() = 0;
		};
	}
}