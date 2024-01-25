#pragma once
#include "Matrix4.h"
#include "WindowsAPI.h"
#include <wrl.h>
#include <d3d12.h>

namespace WristerEngine
{
	namespace _3D
	{
		// カメラ
		class ViewProjection
		{
		private:
			Matrix4 matView, matProjection;

			// 定数バッファ用データ構造体
			struct ConstBufferData
			{
				Matrix4 viewproj; // ビュープロジェクション行列
				Vector3 cameraPos; // カメラ座標(ワールド座標)
			};

		public:
			ConstBufferData* constMap = nullptr;
			Microsoft::WRL::ComPtr<ID3D12Resource> constBuffer;
			Vector3 eye = { 0, 0, -50.0f }, target, up = Vector3::MakeAxis(Axis::Y);
			Angle fovAngleY = 45; // 画角(度)
			// アスペクト比(基本はWIN_SIZEに準拠)
			float aspectRatio = WIN_SIZE.x / WIN_SIZE.y;
			float nearZ = 0.1f, farZ = 1000.0f; // 映る範囲

			// 初期化
			void Initialize();
			// 更新
			void Update();
			// カメラ移動
			void CameraMove(const Vector3& move);
			// ビュー行列とプロジェクション行列を掛け合わせた行列
			Matrix4 GetViewProjectionMatrix() const { return matView * matProjection; }
		};
	}
}