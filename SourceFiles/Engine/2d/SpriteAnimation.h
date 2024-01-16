#pragma once
#include <string>
#include "Sprite.h"
#include "Timer.h"

namespace WristerEngine
{
	namespace _2D
	{
		// �A�j���[�V�����t���X�v���C�g
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
			/// ������
			/// </summary>
			/// <param name="textureName">�e�N�X�`����</param>
			/// <param name="spriteWidth">�A�j���[�V�����ꖇ�̐؂��艡��</param>
			/// <param name="animationIntervel">�A�j���[�V�������x</param>
			void Initialize(const std::string& textureName, size_t spriteWidth, int animationIntervel);
			// �X�V
			void Update();
			// �`��
			void Draw() { sprite->Draw(); }
			// �X�v���C�g�̎擾
			Sprite* GetSprite() { return sprite.get(); }
		};
	}
}