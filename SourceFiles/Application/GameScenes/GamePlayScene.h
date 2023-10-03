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
	BitMapNumber timeIntSprite; // 残り時間整数部
	BitMapNumber timeDecSprite; // 残り時間小数部
	Angle easingColor = 0; // 時間UI色のイージングに使う

	void Initialize();
	void Update();
	void Draw();

	void UIInitialize();
	void UIUpdate();
};