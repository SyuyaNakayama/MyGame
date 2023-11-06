#include "ResultScene.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "Stage.h"

void ResultScene::Initialize()
{
	debugCamera.Initialize();
	ModelManager::SetViewProjection(&debugCamera);

	uiDrawer = std::make_unique<UIDrawerResultScene>();
	uiDrawer->Initialize();
}

void ResultScene::Update()
{
	if (input->IsTrigger(Key::Space))
	{
		sceneManager->ChangeScene(Scene::Result);
		Stage::ResetScore();
	}

	uiDrawer->Update();
}

void ResultScene::Draw()
{
	uiDrawer->Draw();
}

void UIDrawerResultScene::ScoreInitialize()
{
	// �X�R�A���擾
	//score = Stage::GetScore();
	score = 1800;

	// �X�R�A�\���̃X�v���C�g
	BitMapProp* bmProp = printScoreUI.GetBitMapProp();
	bmProp->SetVal("ui/num.png", { 30,30 }, { 30,30 }, {}, 4);
	bmProp->pos.y = rankGaugeBG->position.y - GAUGE_SIZE.y * 2.0f;
	bmProp->anchorPoint = { 0.0f,0.5f };
	printScoreUI.Initialize();

	scoreUI = Sprite::Create("ui/score.png");
	scoreUI->anchorPoint = { 0.5f,0.5f };
	scoreUI->position.y = 240;
}

void UIDrawerResultScene::RankInitialize()
{
	// �����N�Q�[�W
	rankGauge = Sprite::Create("ui/RankGauge.png");
	rankGauge->position = Half(WindowsAPI::WIN_SIZE);
	rankGauge->anchorPoint = { 0.5f,0.5f };
	rankGauge->Update();

	// �����N�Q�[�W�w�i
	rankGaugeBG = Sprite::Create("white1x1.png");
	rankGaugeBG->position = Half(WindowsAPI::WIN_SIZE);
	rankGaugeBG->position.x -= 320;
	rankGaugeBG->anchorPoint = { 0.0f,0.5f };
	rankGaugeBG->size = GAUGE_SIZE;

	// �����N�Q�[�W�̕����X�v���C�g
	rankGaugeSplit[Rank::S] = Sprite::Create("white1x1.png");
	rankGaugeSplit[Rank::A] = Sprite::Create("white1x1.png");
	rankGaugeSplit[Rank::B] = Sprite::Create("white1x1.png");
	for (auto& s : rankGaugeSplit)
	{
		s.second->anchorPoint = { 0.5f,0.5f };
		s.second->color = { 0,1,0,1 };
		s.second->size = { 5,GAUGE_SIZE.y };
		s.second->position = { ScoreToMoniter((int)s.first) + rankGaugeBG->position.x,rankGaugeBG->position.y };
	}

	// �����N�\����UI
	rankUI[Rank::S] = Sprite::Create("ui/Rank/RankS.png");
	rankUI[Rank::A] = Sprite::Create("ui/Rank/RankA.png");
	rankUI[Rank::B] = Sprite::Create("ui/Rank/RankB.png");
	rankUI[Rank::C] = Sprite::Create("ui/Rank/RankC.png");
	for (auto& s : rankUI)
	{
		s.second->anchorPoint = { 0.5f,0.5f };
		s.second->position = { 1030,Half(WindowsAPI::WIN_SIZE.y) };
		s.second->color.a = 0.0f;
	}
	rankUI[Rank::C]->color.a = 1.0f;

	rankSpriteEasing.Initialize(RANK_ANIMATION_TIME, Easing::Type::Sqrt);
	preRank = GetRank(printScore);
}

void UIDrawerResultScene::Initialize()
{
	// �����N�\���֘A�̏�����
	RankInitialize();
	// �X�R�A�\���֘A�̏�����
	ScoreInitialize();
}

void UIDrawerResultScene::ScoreUpdate()
{
	// �Q�[�W���㏸������
	if (printScore <= score) { printScore = min(printScore + GAUGE_INC_SPD, score); }

	// �\���X�R�A�����j�^�[���W�ɕϊ����đ��
	rankGaugeBG->size.x = ScoreToMoniter(printScore);

	// �X�R�A�\���X�v���C�g�̈ړ�
	BitMapProp* bmProp = printScoreUI.GetBitMapProp();
	const float SCORE_UI_CENTER = bmProp->size.x * Half(bmProp->digit);
	bmProp->pos.x = -SCORE_UI_CENTER + rankGaugeBG->position.x + rankGaugeBG->size.x;
	scoreUI->position.x = bmProp->pos.x + SCORE_UI_CENTER;

	rankGaugeBG->Update();
	printScoreUI.Update(printScore);
	scoreUI->Update();
}

void UIDrawerResultScene::Disappear()
{
}

void UIDrawerResultScene::Appear()
{
}

void UIDrawerResultScene::RankUpdate()
{
	enum class AnimationPhase { None, Disappear, Appear };

	if (preRank != GetRank(printScore)) { isRankAnimation = (UINT16)AnimationPhase::Disappear; }

	if (isRankAnimation)
	{
		// �A�j���[�V�������郉���NUI�̃y�A
		std::map<Rank, Rank> animationPair;
		animationPair[Rank::B] = Rank::C;
		animationPair[Rank::A] = Rank::B;
		animationPair[Rank::S] = Rank::A;

		float easingNum = rankSpriteEasing.Update(); // �C�[�W���O�l
		Rank printRank = GetRank(printScore); // �\�������N
		Rank prePrintRank = animationPair[printRank]; // �O�̕\�������N
		// ���߃A�j���[�V����
		if (isRankAnimation == (UINT16)AnimationPhase::Disappear) { rankUI[prePrintRank]->color.a = 1.0f - easingNum; } // ������
		if (isRankAnimation == (UINT16)AnimationPhase::Appear) { rankUI[printRank]->color.a = easingNum; } // �Z��
		// �A�j���[�V�����I��
		if (easingNum == 1.0f)
		{
			if (isRankAnimation == (UINT16)AnimationPhase::Disappear)
			{
				isRankAnimation = (UINT16)AnimationPhase::Appear;
				rankUI[prePrintRank]->isInvisible = true;
				rankSpriteEasing.Restart();
			}
			else if (isRankAnimation == (UINT16)AnimationPhase::Appear)
			{
				isRankAnimation = (UINT16)AnimationPhase::None;
				rankSpriteEasing.Restart();
			}
		}
	}

	// �e�ϐ��̍X�V
	preRank = GetRank(printScore);
	for (auto& s : rankGaugeSplit) { s.second->Update(); }
	for (auto& s : rankUI) { s.second->Update(); }
}

void UIDrawerResultScene::Update()
{
	// �X�R�A�\���֘A�̍X�V
	ScoreUpdate();
	// �����N�\���֘A�̍X�V
	RankUpdate();
}

void UIDrawerResultScene::Draw()
{
	for (auto& s : rankGaugeSplit) { s.second->Draw(); }
	for (auto& s : rankUI) { s.second->Draw(); }
	rankGaugeBG->Draw();
	rankGauge->Draw();
	printScoreUI.Draw();
	scoreUI->Draw();
}

UIDrawerResultScene::Rank UIDrawerResultScene::GetRank(int score_)
{
	if (score_ >= (int)Rank::S) { return Rank::S; }
	if (score_ >= (int)Rank::A) { return Rank::A; }
	if (score_ >= (int)Rank::B) { return Rank::B; }
	return Rank::C;
}