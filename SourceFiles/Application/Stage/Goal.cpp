#include "Goal.h"
#include "Stage.h"
#include "ParticleManager.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

GoalManager* GoalManager::GetInstance()
{
	static GoalManager instance;
	return &instance;
}

void GoalManager::Initialize()
{
	scoreChangeTimer = 600;
	tutorialEventPhase = tutorialEvent->GetTutorialEventPhase();
	roulette.Initialize(WristerEngine::Constant::GetInstance()->GetConstant<std::vector<UINT>>("ScoreRate"));
}

void GoalManager::Update()
{
	isScoreChange = scoreChangeTimer.Update();
	phase = tutorialEvent->GetPhase();
}

void Goal::Initialize(const ObjectData& objectData)
{
	object = ModelManager::Create("cube");
	object->worldTransform.reset(objectData.worldTransform);
	worldTransform = object->worldTransform.get();
	ChangeScore();
	if (objectData.collider.type == "PLANE") { normal = objectData.collider.normal; }
	collisionAttribute = CollisionAttribute::Goal;
	collisionMask = CollisionMask::Goal;
}

Score GoalManager::GetScore() const
{
	switch (roulette())
	{
	default: return Score::_10;
	case 1: return Score::_20;
	case 2: return Score::_30;
	case 3: return Score::_50;
	case 4: return Score::_M10;
	}
}

void Goal::ChangeScore()
{
	Scene nowScene = GetNowScene();
	if (nowScene == Scene::Play || manager->IsTutorialEnd()) { score = manager->GetScore(); }
	else if (nowScene == Scene::Tutorial)
	{
		UINT32 phase = manager->GetPhase();
		auto* tutorialEventPhase = manager->GetTutorialEventPhase();

		if (phase != (*tutorialEventPhase)[4])
		{
			if (score == Score::_M10) { return; }
			if (phase == (*tutorialEventPhase)[3]) { score = Score::_M10; }
			else { score = Score::_10; }
		}
	}
	std::unique_ptr<Sprite> newSprite = Sprite::Create(manager->SCORE_TEX_NAME[score]);

	switch (score)
	{
	case Score::_M10:
		newSprite->color = WristerEngine::ColorRGBA::Blue();
		break;
	case Score::_10:
		newSprite->color = WristerEngine::ColorRGBA::White();
		break;
	case Score::_20:
		newSprite->color = { 1,1,0.5f,1 };
		break;
	case Score::_30:
		newSprite->color = WristerEngine::ColorRGBA::Yellow();
		break;
	case Score::_50:
		newSprite->color = WristerEngine::ColorRGBA::Red();
		break;
	}

	initColor = newSprite->color;
	Material& material = object->material;
	if (score == Score::_M10) { material.ambient = { 1,1,1 }; }
	else { material.ambient = { 0.2f,0.2f,0.2f }; }

	newSprite->isFlipX = true;
	newSprite->Update();
	material.SetSprite(std::move(newSprite), TexType::Main);
}

void Goal::Update()
{
	if (GetNowScene() == Scene::Tutorial)
	{
		UINT32 phase = manager->GetPhase();
		auto* tutorialEventPhase = manager->GetTutorialEventPhase();
		if (phase == (*tutorialEventPhase)[3]) { ChangeScore(); }
		if (phase != (*tutorialEventPhase)[4]) { return; }
	}
	// スコアの変更
	if (manager->IsScoreChange()) { ChangeScore(); }

	// ゴールの点滅開始時間
	const int START_BLINK_TIME = 120;
	// 点滅回数
	const int BLINK_NUM = 4;

	int remainTime = manager->GetChangeRemainTime();
	if (remainTime <= START_BLINK_TIME)
	{
		const int BLINK_INTERVAL = START_BLINK_TIME / BLINK_NUM;
		int easingColor = NumberLoop(START_BLINK_TIME - remainTime, BLINK_INTERVAL);
		float colorRate = (cos(2.0f * PI * (float)easingColor / (float)BLINK_INTERVAL) + 1) * 0.5f;
		object->material.GetSprite(TexType::Main)->color = initColor * colorRate;
	}
}

void Goal::OnCollision(BoxCollider* collider)
{
	WristerEngine::Physics* physics_ = collider->GetPhysics();
	if (!physics_) { return; }
	if (normal.Length() <= 0.001f) { return; }
	if (collider->GetCollisionAttribute() == CollisionAttribute::Player)
	{
		physics_->Backlash(normal, 1.0f);
	}
	else if (collider->GetCollisionAttribute() == CollisionAttribute::Object)
	{
		Object* object_ = dynamic_cast<Object*>(collider);
		assert(object_);
		collider->SetCollisionMask(CollisionMask::None);
		object_->Goal();
		Stage::AddScore(object_->GetGoalScore((int)score));

		WristerEngine::ParticleGroup* pGroup = WristerEngine::ParticleManager::GetParticleGroup(0);
		WristerEngine::DiffuseParticle::AddProp addProp;
		addProp.addNum = 30;
		addProp.start_scale = 10;
		addProp.posOffset = collider->GetWorldPosition();
		addProp.accOffset.y = 0.01f;
		pGroup->Add(addProp);

		if (GetNowScene() == Scene::Tutorial)
		{
			manager->NextPhase();
		}
	}
}