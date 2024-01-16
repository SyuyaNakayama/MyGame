#pragma once
#include <string>
#include "Sprite.h"
#include "Timer.h"

namespace WristerEngine
{
	namespace _2D
	{
		// アニメーション付きスプライト
		class SpriteAnimation
		{
		private:
			std::unique_ptr<WristerEngine::_2D::Sprite> sprite;
			size_t width;
			FrameTimer interval;
			size_t animeNum = 0;
			size_t animeNumMax = 0;

		public:
			/// <summary>
			/// 初期化
			/// </summary>
			/// <param name="textureName">テクスチャ名</param>
			/// <param name="spriteWidth">アニメーション一枚の切り取り横幅</param>
			/// <param name="animationIntervel">アニメーション速度</param>
			void Initialize(const std::string& textureName, size_t spriteWidth, int animationIntervel);
			// 更新
			void Update();
			// 描画
			void Draw() { sprite->Draw(); }
			// スプライトの取得
			Sprite* GetSprite() { return sprite.get(); }
		};
	}
}