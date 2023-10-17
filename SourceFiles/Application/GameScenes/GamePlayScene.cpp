#include "GamePlayScene.h"
#include "SceneManager.h"
#include <imgui.h>

int StartCountDown::fps = 0;

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
#ifdef _DEBUG
	if (input->IsTrigger(Key::_1)) { ModelManager::SetViewProjection(&viewProjection); }
	if (input->IsTrigger(Key::_2)) { ModelManager::SetViewProjection(&debugCamera); }
	// �J�E���g�_�E�����o
	ImGui::Text("FPS = %d", fps->GetFPS());
#endif // _DEBUG

	if (countDown)
	{
		countDown->Update();
		if (countDown->IsFinish()) { countDown.release(); stage.ResetTime(); }
		else { return; }
	}

	timer.Update();
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
	timeIntSprite2.Draw();
	timeDecSprite2.Draw();
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
	*scoreSprite.GetBitMapProp() = bitMapProp;
	scoreSprite.Initialize();
	uiScore = Sprite::Create("ui/score.png");
	uiScore->anchorPoint = { 0.5f,0.5f };
	uiScore->position = { 1160,70 };
	uiScore->Update();

	// �c�莞��
	bitMapProp.pos.x = 60;
	bitMapProp.digit = 2;
	*timeIntSprite.GetBitMapProp() = bitMapProp;
	timeIntSprite.Initialize(); // ������

	bitMapProp.pos = { 120,115 };
	bitMapProp.digit = 3;
	bitMapProp.size /= 2;
	*timeDecSprite.GetBitMapProp() = bitMapProp;
	timeDecSprite.Initialize(); // ������

	// �c�莞��
	bitMapProp.size *= 2;
	bitMapProp.pos.y += 50;
	bitMapProp.pos.x = 60;
	bitMapProp.digit = 2;
	*timeIntSprite2.GetBitMapProp() = bitMapProp;
	timeIntSprite2.Initialize(); // ������

	bitMapProp.pos = { 120,180 };
	bitMapProp.digit = 3;
	bitMapProp.size /= 2;
	*timeDecSprite2.GetBitMapProp() = bitMapProp;
	timeDecSprite2.Initialize(); // ������

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
		timeIntSprite.GetBitMapProp()->color = { 1,colorGB,colorGB,1 };
		timeDecSprite.GetBitMapProp()->color = { 1,colorGB,colorGB,1 };
	}

	timeIntSprite.Update((int)remainTime);

	float temp = stage.GetRemainTime();
	float decimal = modf(remainTime, &temp) * 1000;
	timeDecSprite.Update((int)decimal);

	float nowtime = (float)timer.GetTime() / 20.0f;
	float nowtime2 = modf(nowtime, &temp) * 1000;
	timeIntSprite2.Update((int)nowtime);
	timeDecSprite2.Update((int)nowtime2);
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
	*countDown->countUI.GetBitMapProp() = bitMapProp;
	countDown->countUI.Initialize();
	if (fps == 0) { fps = FPS::GetInstance()->GetFPS(); }
	countDown->count = COUNT_DOWN_TIME * fps;

	return countDown;
}

void StartCountDown::Update()
{
	int time = count.GetTime() / fps;
	time = min(3, time + 1);
	countUI.Update(time);
	ImGui::Text("count.GetTime() %d", count.GetTime());
}

void StartCountDown::Draw()
{
	countUI.Draw();
}
