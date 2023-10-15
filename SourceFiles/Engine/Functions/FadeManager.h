#pragma once
#include "Sprite.h"

// ��ʂ̃t�F�[�h���o
class FadeManager
{
private:
	const int FADE_TIME = 30;
	float fadePerFlame = 1.0f / FADE_TIME;
	std::unique_ptr<Sprite> sprite;
	bool isFade = 0;
	float alpha = 0;
	bool isChange = false;

public:
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw() { sprite->Draw(); }
	// �t�F�[�h���I���ɂ���
	void FadeScene() { isFade = true; }
	// getter
	bool IsChange() { return isChange; }
	bool IsFade() { return isFade; }
};