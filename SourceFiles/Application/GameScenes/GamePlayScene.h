#pragma once
#include "BaseScene.h"
#include "Stage.h"
#include "Object3d.h"
#include "AudioManager.h"
#include "BitMapNumber.h"
#include "MathUtility.h"

class GamePlayScene : public BaseScene
{
private:
	Stage stage;
	ViewProjection viewProjection;
	Audio* audio = nullptr;
	std::unique_ptr<Sprite> uiScore;
	std::unique_ptr<Sprite> uiClock;
	BitMapNumber scoreSprite;
	BitMapNumber timeIntSprite; // �c�莞�Ԑ�����
	BitMapNumber timeDecSprite; // �c�莞�ԏ�����
	Angle easingColor = 0; // ����UI�F�̃C�[�W���O�Ɏg��

	void Initialize();
	void Update();
	void Draw();

	void UIInitialize();
	void UIUpdate();
};