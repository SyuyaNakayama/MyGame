#include "GamePlayScene.h"
#include "SceneManager.h"
#include <imgui.h>

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

int StartCountDown::fps = 0;

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 0,0 });
	viewProjection.Initialize();
	viewProjection.eye = { 0,350,0 };
	viewProjection.eye.y = 350;
	viewProjection.eye.z = -75;
	stage.Initialize();
	ModelManager::SetViewProjection(&viewProjection);

	// UI�`��N���X�̃C���X�^���X����
	uiDrawer = std::make_unique<UIDrawerGameScene>(&stage);
	uiDrawer->Initialize();
	//ModelManager::SetViewProjection(&debugCamera);
	// �J�E���g�_�E���O�Ɉ��X�V����
	stage.Update();
	uiDrawer->Update();
}

void GamePlayScene::Update()
{
#ifdef _DEBUG
	if (input->IsTrigger(WristerEngine::Key::_1)) { ModelManager::SetViewProjection(&viewProjection); }
	if (input->IsTrigger(WristerEngine::Key::_2)) { ModelManager::SetViewProjection(&debugCamera); }
#endif // _DEBUG
	uiDrawer->Update();
	UIDrawerGameScene* uiDrawer_ = dynamic_cast<UIDrawerGameScene*>(uiDrawer.get());
	if (uiDrawer_) { if (uiDrawer_->IsCountDown()) { return; } }

	debugCamera.Update();
	stage.Update();

	// �Q�[���I�����Ƀ��U���g��ʂ֔��
	if (stage.IsFinished())
	{
		sceneManager->ChangeScene(Scene::Result);
	}

	if (input->IsTrigger(WristerEngine::Key::Space))
	{
		sceneManager->ChangeScene(Scene::Title);
	}
}

std::unique_ptr<StartCountDown> StartCountDown::Create()
{
	std::unique_ptr<StartCountDown> countDown = std::make_unique<StartCountDown>();

	// �r�b�g�}�b�v�̐ݒ�
	BitMapProp bitMapProp =
	{
		"ui/num.png",{30,30},{360,360},{},1
	};

	bitMapProp.pos = Half(WristerEngine::WindowsAPI::WIN_SIZE - bitMapProp.size);
	*countDown->countUI.GetBitMapProp() = bitMapProp;
	countDown->countUI.Initialize();
	if (fps == 0) { fps = WristerEngine::FPS::GetInstance()->GetFPS(); }
	countDown->countTimer = COUNT_DOWN_TIME * fps;

	return countDown;
}

bool StartCountDown::Update()
{
	bool isFinish = countTimer.Update();
	// �J�E���g�_�E���`��̍X�V
	int time = countTimer.GetRemainTime() / fps;
	time = min(COUNT_DOWN_TIME, time + 1);
	countUI.Update(time);
	// �����̃X���C�h���o
	auto timeSecond = countTimer.GetRemainTime(fps);
	const int SLIDE_START = 250; // �X���C�h���o���n�܂�^�C�~���O
	if (timeSecond[1] <= SLIDE_START)
	{
		// �X�v���C�g��UV���W�����炷
		float offsetRate = 1.0f - (float)timeSecond[1] / SLIDE_START;
		countUI.GetBitMapProp()->texLTOffset.x = countUI.GetAllSpriteSize().x * offsetRate;
	}
	else { countUI.GetBitMapProp()->texLTOffset.x = 0; }

	return isFinish;
}

void StartCountDown::Draw()
{
	countUI.Draw();
}

void UIDrawerGameScene::Initialize()
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
	uiScore->SetCenterAnchor();
	uiScore->position = { 1160,70 };
	uiScore->Update();

	// �c�莞��
	// ������
	bitMapProp.pos.x = 60;
	bitMapProp.digit = 2;
	*timeIntSprite.GetBitMapProp() = bitMapProp;
	timeIntSprite.Initialize();
	// ������
	bitMapProp.pos = { 120,115 };
	bitMapProp.digit = 3;
	bitMapProp.size /= 2;
	*timeDecSprite.GetBitMapProp() = bitMapProp;
	timeDecSprite.Initialize();
	// ���v�A�C�R��
	uiClock = Sprite::Create("ui/clock.png");
	uiClock->SetCenterAnchor();
	uiClock->position = { 112.5f,54 };
	uiClock->Update();

	// �J�E���g�_�E��UI
	countDown = StartCountDown::Create();
	uiGo = Sprite::Create("ui/GO.png");
	uiGo->SetCenterAnchor();
	uiGo->position = Half(WristerEngine::WindowsAPI::WIN_SIZE);
	uiGo->isInvisible = true; // ����
	const int GO_EASING_DEC = 4;
	uiGoEasing.Initialize(StartCountDown::GetFPS() / GO_EASING_DEC, WristerEngine::Easing::Type::Sqrt);
	UIGoAnimation = &UIDrawerGameScene::UIGoSlide;

	frame = Sprite::Create("UI/uiFrame.png");
	frame->position = { 50,420 };
	frame->size = { 350,286 };
	frame->Update();
	
	using Key = WristerEngine::Key;
	
	keyUI[Key::A] = Sprite::Create("UI/Key/key_A.png");
	keyUI[Key::D] = Sprite::Create("UI/Key/key_D.png");
	keyUI[Key::W] = Sprite::Create("UI/Key/key_W.png");
	keyUI[Key::S] = Sprite::Create("UI/Key/key_S.png");

	keyUI[Key::Left] = Sprite::Create("UI/Key/key_Left.png");
	keyUI[Key::Right] = Sprite::Create("UI/Key/key_Right.png");
	keyUI[Key::Up] = Sprite::Create("UI/Key/key_Up.png");
	keyUI[Key::Down] = Sprite::Create("UI/Key/key_Down.png");

	for (auto& s : keyUI)
	{
		s.second->textureSize.x /= 2.0f;
		s.second->size.x /= 2.0f;
		s.second->position = frame->position;
	}

	const float UI_POS_COMPRESS = 10.0f; // ����UI�Ԃ̋��������k���邽�߂̕ϐ�
	const float DISTANCE_BETWEEN_KEY_ARROW = 148.0f; // �L�[����UI�ƃA���[UI�Ԃ̋���

	keyUI[Key::A]->position += { UI_POS_COMPRESS, keyUI[Key::A]->size.y };
	keyUI[Key::D]->position += { keyUI[Key::D]->size.x * 2.0f - UI_POS_COMPRESS, keyUI[Key::D]->size.y };
	keyUI[Key::W]->position += { keyUI[Key::W]->size.x, UI_POS_COMPRESS };
	keyUI[Key::S]->position += { keyUI[Key::S]->size.x, keyUI[Key::S]->size.y };

	std::map<Key, Key> keyPair =
	{
		{Key::Left,Key::A},
		{Key::Right,Key::D},
		{Key::Up,Key::W},
		{Key::Down,Key::S}
	};

	for (auto& pair : keyPair)
	{
		keyUI[pair.first]->position = keyUI[pair.second]->position;
		keyUI[pair.first]->position.y += DISTANCE_BETWEEN_KEY_ARROW;
	}

	operateUI["player"] = Sprite::Create("UI/Move.png");
	operateUI["player"]->anchorPoint.y = 0.25f;
	operateUI["player"]->position = { keyUI[Key::D]->position.x, keyUI[Key::W]->position.y };
	operateUI["player"]->position += { keyUI[Key::D]->size.x, Half(keyUI[Key::D]->size.y) };

	operateUI["camera"] = Sprite::Create("UI/Camera.png");
	operateUI["camera"]->anchorPoint.y = 0.25f;
	operateUI["camera"]->position = { keyUI[Key::Right]->position.x, keyUI[Key::Up]->position.y };
	operateUI["camera"]->position += { keyUI[Key::D]->size.x, Half(keyUI[Key::D]->size.y) };

	for (auto& s : operateUI) { s.second->Update(); }
}

void UIDrawerGameScene::Update()
{
	for (auto& s : keyUI)
	{
		// �L�[���������烌�N�g�ʒu��ς���
		s.second->textureLeftTop.x = WristerEngine::Input::GetInstance()->IsInput(s.first) * s.second->size.x;
		s.second->Update();
	}

	scoreSprite.Update(stage->GetScore());

	if (countDown)
	{
		// �J�E���g�_�E������60.000�b�Œ�
		timeIntSprite.Update(60);
		timeDecSprite.Update(0);

		if (countDown->Update())
		{
			countDown.release();
			stage->ResetTime();
			uiGo->isInvisible = false;
		}
		else { return; }
	}

	if (!uiGo->isInvisible)
	{
		(this->*UIGoAnimation)();
		uiGo->Update();
	}

	// �c�莞�Ԃ��擾
	std::array<int, 2> remainTime = stage->GetRemainTime();

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

void UIDrawerGameScene::UIGoSlide()
{
	float easingNum = uiGoEasing.Update();
	uiGo->position.x = WristerEngine::WindowsAPI::WIN_SIZE.x / 2.0f + SLIDE_DIS_UI_GO * (1.0f - easingNum);
	uiGo->color.a = easingNum;
	if (easingNum == 1.0f)
	{
		UIGoAnimation = &UIDrawerGameScene::UIGoIdle;
	}
}

void UIDrawerGameScene::UIGoIdle()
{
	const int IDLE_TIME = 20;
	static WristerEngine::FrameTimer idle = IDLE_TIME;
	if (idle.Update())
	{
		uiGoSize = uiGo->size;
		UIGoAnimation = &UIDrawerGameScene::UIGoZoom;
		uiGoEasing.Restart();
	}
}

void UIDrawerGameScene::UIGoZoom()
{
	float easingNum = uiGoEasing.Update();
	uiGo->size = uiGoSize * (1.0f + easingNum);
	uiGo->color.a = (1.0f - easingNum);
	if (easingNum == 1.0f)
	{
		uiGo->isInvisible = false;
	}
}

void UIDrawerGameScene::Draw()
{
	scoreSprite.Draw();
	timeIntSprite.Draw();
	timeDecSprite.Draw();
	uiClock->Draw();
	uiScore->Draw();
	frame->Draw();
	for (auto& s : keyUI) { s.second->Draw(); }
	for (auto& s : operateUI) { s.second->Draw(); }
	if (countDown) { countDown->Draw(); }
	uiGo->Draw();
}