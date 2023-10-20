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
	// UI�`��N���X�̃C���X�^���X����
	uiDrawer = std::make_unique<UIDrawer>();
	InitializeUI();
	countDown = StartCountDown::Create();
	//ModelManager::SetViewProjection(&debugCamera);
	// �J�E���g�_�E���O�Ɉ��X�V����
	stage.Update();
	UpdateUI();
}

void GamePlayScene::Update()
{
#ifdef _DEBUG
	if (input->IsTrigger(Key::_1)) { ModelManager::SetViewProjection(&viewProjection); }
	if (input->IsTrigger(Key::_2)) { ModelManager::SetViewProjection(&debugCamera); }
#endif // _DEBUG

	if (countDown)
	{
		countDown->Update();
		if (countDown->IsFinish()) { countDown.release(); stage.ResetTime(); }
		else { return; }
	}

	debugCamera.Update();
	stage.Update();
	UpdateUI();

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

void GamePlayScene::InitializeUI()
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

	uiClock = Sprite::Create("ui/clock.png");
	uiClock->anchorPoint = { 0.5f,0.5f };
	uiClock->position = { 112.5f,54 };
	uiClock->Update();
}

void GamePlayScene::UpdateUI()
{
	scoreSprite.Update(stage.GetScore());

	// �J�E���g�_�E������60.000�b�Œ�
	if (countDown)
	{
		timeIntSprite.Update(60);
		timeDecSprite.Update(000);
		return;
	}

	// �c�莞�Ԃ��擾
	std::array<int, 2> remainTime = stage.GetRemainTime();

	// �c�莞�Ԃ�10�b�ȉ��ɂȂ�Ǝ��Ԃ̕������ԓ_�ł���
	if (remainTime[0] < 10)
	{
		easingColor += (int)15 - remainTime[0];
		float colorGB = (cos(easingColor) + 1) * 0.5f;
		timeIntSprite.GetBitMapProp()->color = { 1,colorGB,colorGB,1 };
		timeDecSprite.GetBitMapProp()->color = { 1,colorGB,colorGB,1 };
	}

	timeIntSprite.Update(remainTime[0]);
	timeDecSprite.Update(remainTime[1]);
}

std::unique_ptr<StartCountDown> StartCountDown::Create()
{
	std::unique_ptr<StartCountDown> countDown = std::make_unique<StartCountDown>();

	// �r�b�g�}�b�v�̐ݒ�
	BitMapProp bitMapProp =
	{
		"ui/num.png",{30,30},{360,360},{},1
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
	// �J�E���g�_�E���`��̍X�V
	int time = count.GetRemainTime() / fps;
	time = min(3, time + 1);
	countUI.Update(time);
	// �����̃X���C�h���o
	auto timeSecond = count.GetRemainTime(fps);
	const int SLIDE_START = 250; // �X���C�h���o���n�܂�^�C�~���O
	if (timeSecond[1] <= SLIDE_START)
	{
		float offsetRate = 1.0f - (float)timeSecond[1] / SLIDE_START;
		countUI.GetBitMapProp()->texLTOffset.x = countUI.GetAllSpriteSize().x * offsetRate;
	}
	else
	{
		countUI.GetBitMapProp()->texLTOffset.x = 0;
	}
}

void StartCountDown::Draw()
{
	countUI.Draw();
}

void UIDrawer::Initialize()
{
}

void UIDrawer::Update()
{
}

void UIDrawer::Draw()
{
}
