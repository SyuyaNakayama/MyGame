#include "ResultScene.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "Stage.h"

#pragma region ResultScene
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
		sceneManager->ChangeScene(Scene::Title);
		Stage::ResetScore();
	}

	uiDrawer->Update();
}

void ResultScene::Draw()
{
	uiDrawer->Draw();
}
#pragma endregion

void UIDrawerResultScene::ScoreInitialize()
{
	// �X�R�A���擾
	//score = Stage::GetScore();
	score = 3000;

	// �X�R�A�\���̃X�v���C�g
	BitMapProp* bmProp = printScoreUI.GetBitMapProp();
	bmProp->SetVal("ui/num.png", { 30,30 }, { 30,30 }, {}, 4);
	bmProp->pos.y = rankGaugeBG->position.y - GAUGE_SIZE.y * 2.0f;
	bmProp->anchorPoint = { 0.0f,0.5f };
	printScoreUI.Initialize();

	scoreUI = Sprite::Create("ui/score.png");
	scoreUI->SetCenterAnchor();
	scoreUI->position.y = 240;
}

void UIDrawerResultScene::RankInitialize()
{
	// �����N���\���ɔw�i���Â����邽�߂̃X�v���C�g
	blind = Sprite::Create("white1x1.png");
	blind->size = WindowsAPI::WIN_SIZE;
	blind->color = { 0,0,0,0.5f };
	blind->isInvisible = true;

	// �����N�Q�[�W
	rankGauge = Sprite::Create("ui/RankGauge.png");
	rankGauge->position = Half(WindowsAPI::WIN_SIZE);
	rankGauge->SetCenterAnchor();
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
		s.second->SetCenterAnchor();
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
		s.second->SetCenterAnchor();
		s.second->position = { 1030,Half(WindowsAPI::WIN_SIZE.y) };
		s.second->color.a = 0.0f;
	}
	rankUI[Rank::C]->color.a = Color::MAX;

	rankSpriteFade.Initialize(RANK_ANIMATION_TIME, Easing::Type::Sqrt);
	rankSpriteScale.Initialize(RANK_ANIMATION_TIME, Easing::Type::OutBounce);
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
	// �A�j���[�V�������郉���NUI�̃y�A
	std::map<Rank, Rank> animationPair;
	animationPair[Rank::B] = Rank::C;
	animationPair[Rank::A] = Rank::B;
	animationPair[Rank::S] = Rank::A;

	Rank printRank = GetRank(printScore); // �\�������N
	Rank prePrintRank = animationPair[printRank]; // �O�̕\�������N

	float easingRate = rankSpriteFade.Update();
	rankUI[prePrintRank]->color.a = Color::MAX - easingRate; // ������
	// �A�j���[�V�����I��
	if (easingRate == Easing::MAX)
	{
		RankAnimation = &UIDrawerResultScene::Appear;
		rankUI[prePrintRank]->isInvisible = true;
		rankSpriteSizeMem = rankUI[printRank]->size;
		rankSpriteFade.Restart();
	}
}

void UIDrawerResultScene::Judge()
{
	// �����N���ς�����烉���N�\��UI�̃A�j���[�V����������
	if (preRank != GetRank(printScore)) { RankAnimation = &UIDrawerResultScene::Disappear; }
	if (score == printScore) { RankAnimation = &UIDrawerResultScene::Result; }
}

void UIDrawerResultScene::Appear()
{
	float easingRate = rankSpriteFade.Update();
	rankUI[GetRank(printScore)]->color.a = easingRate; // �Z��
	const float SIZE_RATE = 3.0f;
	rankUI[GetRank(printScore)]->size = rankSpriteSizeMem * (SIZE_RATE - (SIZE_RATE - 1.0f) * rankSpriteScale.Update());
	// �A�j���[�V�����I��
	if (easingRate == Easing::MAX)
	{
		RankAnimation = &UIDrawerResultScene::Judge;
		rankSpriteFade.Restart();
		rankSpriteScale.Restart();
	}
}

void UIDrawerResultScene::Result()
{
	blind->isInvisible = false;
	resultRankSprite = Sprite::Create(rankUI[GetRank(score)]->tex->fileName);
	resultRankSprite->SetCenterAnchor();
	resultRankSprite->SetCenterPos();
	resultRankSprite->size *= 4.0f;
	if (Input::GetInstance()->IsTrigger(Key::Return))
	{
		blind->isInvisible = true;
		RankAnimation = nullptr;
	}
}

void UIDrawerResultScene::RankUpdate()
{
	// �����N�\��UI�̃A�j���[�V����
	if (RankAnimation) { (this->*RankAnimation)(); }

	// �e�ϐ��̍X�V
	preRank = GetRank(printScore);
	for (auto& s : rankGaugeSplit) { s.second->Update(); }
	for (auto& s : rankUI) { s.second->Update(); }
	if (blind->isInvisible) { return; }
	blind->Update();
	resultRankSprite->Update();
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
	rankGauge->Draw();
	rankGaugeBG->Draw();
	for (auto& s : rankGaugeSplit) { s.second->Draw(); }
	for (auto& s : rankUI) { s.second->Draw(); }
	printScoreUI.Draw();
	scoreUI->Draw();
	if (blind->isInvisible) { return; }
	blind->Draw();
	resultRankSprite->Draw();
}

UIDrawerResultScene::Rank UIDrawerResultScene::GetRank(int score_)
{
	if (score_ >= (int)Rank::S) { return Rank::S; }
	if (score_ >= (int)Rank::A) { return Rank::A; }
	if (score_ >= (int)Rank::B) { return Rank::B; }
	return Rank::C;
}