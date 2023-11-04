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

void UIDrawerResultScene::Initialize()
{
	// �X�R�A���擾
	//score = Stage::GetScore();
	score = 4649;

	// �����N�Q�[�W
	rankGauge = Sprite::Create("ui/RankGauge.png");
	rankGauge->position = WindowsAPI::WIN_SIZE / 2.0f;
	rankGauge->anchorPoint = { 0.5f,0.5f };
	rankGauge->Update();

	// �����N�Q�[�W�w�i
	rankGaugeBG = Sprite::Create("white1x1.png");
	rankGaugeBG->position = WindowsAPI::WIN_SIZE / 2.0f;
	rankGaugeBG->position.x -= 320;
	rankGaugeBG->anchorPoint = { 0.0f,0.5f };
	rankGaugeBG->size = GAUGE_SIZE;

	// �����N�Q�[�W�̕����X�v���C�g
	rankGaugeSplit[Rank::S] = Sprite::Create("white1x1.png");
	rankGaugeSplit[Rank::A] = Sprite::Create("white1x1.png");
	rankGaugeSplit[Rank::B] = Sprite::Create("white1x1.png");
	rankGaugeSplit[Rank::C] = Sprite::Create("white1x1.png");

	// �����N�\����UI
	rankUI[Rank::C] = Sprite::Create("ui/Rank/RankC.png");
	for (auto& s : rankUI)
	{
		s.second->anchorPoint = { 0.5f,0.5f };
		s.second->position = { 1030,WindowsAPI::WIN_SIZE.y / 2 };
	}

	for (auto& s : rankGaugeSplit)
	{
		s.second->anchorPoint = { 0.5f,0.5f };
		s.second->color = { 0,1,0,1 };
		s.second->size = { 5,GAUGE_SIZE.y };
		s.second->position = { ScoreToMoniter((int)s.first) + rankGaugeBG->position.x,rankGaugeBG->position.y };
	}
	
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

void UIDrawerResultScene::Update()
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

	rankGauge->Update();
	rankGaugeBG->Update();
	for (auto& s : rankGaugeSplit) { s.second->Update(); }
	for (auto& s : rankUI) { s.second->Update(); }
	printScoreUI.Update(printScore);
	scoreUI->Update();
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
