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

	// �X�R�A�\���̃X�v���C�g
	BitMapProp* bmProp = printScoreUI.GetBitMapProp();
	bmProp->SetVal("ui/num.png", { 30,30 }, { 30,30 }, {}, 4);
	bmProp->pos.y = rankGaugeBG->position.y - GAUGE_SIZE.y * 2.0f;
	bmProp->anchorPoint = { 0.0f,0.5f };
	printScoreUI.Initialize();

	scoreUI = Sprite::Create("ui/score.png");
	scoreUI->anchorPoint = { 0.5f,0.5f };
}

void UIDrawerResultScene::Update()
{
	// �Q�[�W���㏸������
	if (printScore <= score) { printScore = min(printScore + GAUGE_INC_SPD, score); }

	// �\���X�R�A�����j�^�[���W�ɕϊ����đ��
	rankGaugeBG->size.x = min((float)printScore * GAUGE_SIZE.x / GAUGE_MAX_SCORE, GAUGE_SIZE.x);

	// �X�R�A�\���X�v���C�g�̈ړ�
	BitMapProp* bmProp = printScoreUI.GetBitMapProp();
	bmProp->pos.x = -bmProp->size.x * 2 + rankGaugeBG->position.x + rankGaugeBG->size.x;

	rankGaugeBG->Update();
	printScoreUI.Update(printScore);
}

void UIDrawerResultScene::Draw()
{
	rankGaugeBG->Draw();
	rankGauge->Draw();
	printScoreUI.Draw();
}
