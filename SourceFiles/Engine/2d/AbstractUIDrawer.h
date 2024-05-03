#pragma once
#include "Constant.h"
#include "Sprite.h"
#include <map>

namespace WristerEngine::_2D
{
	// UI�`��̒��ۃN���X
	// �e�V�[�����Ƃ�UIDrawer�N���X���`����
	class AbstractUIDrawer
	{
	protected:
		Constant* constant = Constant::GetInstance();
		std::map<std::string, std::unique_ptr<Sprite>> sprites;

	public:
		// ���z�f�X�g���N�^
		virtual ~AbstractUIDrawer() = default;
		// ������(�������z�֐�)
		virtual void Initialize() = 0;
		// �X�V(���z�֐�)
		virtual void Update() { for (auto& s : sprites) { s.second->Update(); } }
		// �`��(���z�֐�)
		virtual void Draw() { for (auto& s : sprites) { s.second->Draw(); } }
	};
}