#include "GamePlayScene.h"
#include "SceneManager.h"
#include <imgui.h>

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 0,0 });
	viewProjection.Initialize();
	viewProjection.eye.y = 350;
	viewProjection.eye.z = -75;
	viewProjection.target.z = 10;
	stage.Initialize();
	UIInitialize();
	countDown = StartCountDown::Create();
	//ModelManager::SetViewProjection(&debugCamera);
	// �J�E���g�_�E���O�Ɉ��X�V����
	stage.Update();
	UIUpdate();
}

void GamePlayScene::Update()
{
	//if (input->IsTrigger(Key::_1)) { ModelManager::SetViewProjection(&viewProjection); }
	//if (input->IsTrigger(Key::_2)) { ModelManager::SetViewProjection(&debugCamera); }
	// �J�E���g�_�E�����o
	if (countDown)
	{
		countDown->Update();
		if (countDown->IsFinish()) { countDown.release(); stage.ResetTime(); }
		else { return; }
	}

	debugCamera.Update();
	stage.Update();
	UIUpdate();

	// �Q�[���I�����Ƀ��U���g��ʂ֔��
	if (stage.IsFinished() /*|| input->IsTrigger(Key::Space)*/)
	{
		sceneManager->ChangeScene(Scene::Result);
		ModelManager::ClearObjects();
	}
}

void GamePlayScene::Draw()
{
	scoreSprite.Draw();
	timeIntSprite.Draw();
	timeDecSprite.Draw();
	uiClock->Draw();
	uiScore->Draw();
	if (countDown) { countDown->Draw(); }
}

void GamePlayScene::UIInitialize()
{
	// �r�b�g�}�b�v�̐ݒ�
	BitMapProp bitMapProp =
	{
		"ui/num.png",{30,30},{30,30},{1100,100},4
	};

	// �X�R�A
	scoreSprite.Initialize(bitMapProp);
	uiScore = Sprite::Create("ui/score.png");
	uiScore->anchorPoint = { 0.5f,0.5f };
	uiScore->position = { 1160,70 };
	uiScore->Update();

	// �c�莞��
	bitMapProp.pos.x = 60;
	bitMapProp.digit = 2;
	timeIntSprite.Initialize(bitMapProp); // ������

	bitMapProp.pos = { 120,115 };
	bitMapProp.digit = 3;
	bitMapProp.size /= 2;
	timeDecSprite.Initialize(bitMapProp); // ������

	uiClock = Sprite::Create("ui/clock.png");
	uiClock->anchorPoint = { 0.5f,0.5f };
	uiClock->position = { 112.5f,54 };
	uiClock->Update();
}

void GamePlayScene::UIUpdate()
{
	scoreSprite.Update(stage.GetScore());

	// �J�E���g�_�E������60.000�b�Œ�
	if (countDown)
	{
		timeIntSprite.Update(60);
		timeDecSprite.Update(000);
		return;
	}

	float remainTime = stage.GetRemainTime();

	// �c�莞�Ԃ�10�b�ȉ��ɂȂ�Ǝ��Ԃ̕������ԓ_�ł���
	if (remainTime <= 10.0f)
	{
		easingColor += (int)(15.0f - remainTime);
		float colorGB = (cos(easingColor) + 1) * 0.5f;
		timeIntSprite.ChangeColor({ 1,colorGB,colorGB,1 });
		timeDecSprite.ChangeColor({ 1,colorGB,colorGB,1 });
	}

	timeIntSprite.Update((int)remainTime);

	float temp = stage.GetRemainTime();
	float decimal = modf(remainTime, &temp) * 1000;
	timeDecSprite.Update((int)decimal);
}

std::unique_ptr<StartCountDown> StartCountDown::Create()
{
	std::unique_ptr<StartCountDown> countDown = std::make_unique<StartCountDown>();

	// �r�b�g�}�b�v�̐ݒ�
	BitMapProp bitMapProp =
	{
		"ui/num.png",{30,30},{180,180},{},1
	};

	bitMapProp.pos = (WindowsAPI::WIN_SIZE - bitMapProp.size) / 2.0f;
	countDown->countUI.Initialize(bitMapProp);
	countDown->count.Start();

	return countDown;
}

void StartCountDown::Update()
{
	countUI.Update((int)ceilf(count.GetRemainTime()));
}

void StartCountDown::Draw()
{
	countUI.Draw();
}
