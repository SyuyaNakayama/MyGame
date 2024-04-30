#pragma once
#include "Constant.h"

namespace WristerEngine::_2D
{
	// UI�`��̒��ۃN���X
	// �e�V�[�����Ƃ�UIDrawer�N���X���`����
	class AbstractUIDrawer
	{
	protected:
		Constant* constant = Constant::GetInstance();

	public:
		// ���z�f�X�g���N�^
		virtual ~AbstractUIDrawer() = default;
		// ������(�������z�֐�)
		virtual void Initialize() = 0;
		// �X�V(�������z�֐�)
		virtual void Update() = 0;
		// �`��(�������z�֐�)
		virtual void Draw() = 0;
	};
}