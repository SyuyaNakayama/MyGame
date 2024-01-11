#pragma once
#include "ModelManager.h"

namespace WristerEngine
{
	namespace _3D
	{
		// オブジェクトに追従するカメラ
		class BaseCamera
		{
		protected:
			float distance = 50.0f; // 注視点から視点までの距離
			ViewProjection viewProjection;
			Vector2 angle = { 0,0.3f }; // カメラ回転量
			WorldTransform worldTransform;

		public:
			// 仮想デストラクタ
			virtual ~BaseCamera() = default;
			/// <summary>
			/// 初期化
			/// </summary>
			/// <param name="parent">ワールドトランスフォームの親ポインタ</param>
			virtual void Initialize(WorldTransform* parent);
			// 更新
			virtual void Update();
			// getter
			ViewProjection* GetViewProjection() { return &viewProjection; }
			const Vector2& GetAngle() { return angle; }
		};
	}
}