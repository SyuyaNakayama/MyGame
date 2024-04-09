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
	nowScene = WristerEngine::SceneManager::GetInstance()->GetNowScene();
	scoreChangeTimer = Const(int, "ScoreChangeTimer");
	tutorialEventPhase = tutorialEvent->GetTutorialEventPhase();
	roulette.Initialize(Const(std::vector<UINT>, "ScoreRate"));
	goalColor.Initialize(
		Const(int, "GoalBlinkTime") / Const(int, "GoalBlinkNum"),
		WristerEngine::LoopEasing::Type::Cos);
}

void GoalManager::Update()
{
	nowScene = WristerEngine::SceneManager::GetInstance()->GetNowScene();

	if (IsNotTutorial())
	{
		isScoreChange = scoreChangeTimer.Update();
		// ゴールの点滅処理
		if (scoreChangeTimer.GetRemainTime() <= Const(int, "GoalBlinkTime"))
		{
			float colorRate = goalColor.Update();
			for (auto* g : goals) { g->ChangeColor(colorRate); }
		}
	}
	else
	{
		phase = tutorialEvent->GetPhase();
		isScoreChange = (phase == (*tutorialEventPhase)[3]);
	}

	if (!preTutorialEnd && IsNotTutorial()) { isScoreChange = true; }

	// スコアの変更
	if (isScoreChange) { for (auto* g : goals) { g->ChangeScore(GetScore()); } }
	preTutorialEnd = IsNotTutorial();
}

Score GoalManager::GetScore() const
{
	if (IsNotTutorial())
	{
		// 通常プレイの点数変化
		switch (roulette())
		{
		default: return Score::_10;
		case 1: return Score::_20;
		case 2: return Score::_30;
		case 3: return Score::_50;
		case 4: return Score::_M10;
		}
	}
	else
	{
		// チュートリアルの点数変化
		if (phase == (*tutorialEventPhase)[3]) { return Score::_M10; }
		else { return Score::_10; }
	}
}

void Goal::Initialize(const ObjectData& objectData)
{
	object = ModelManager::Create("cube");
	object->worldTransform.reset(objectData.worldTransform);
	worldTransform = object->worldTransform.get();
	ChangeScore(manager->GetScore());
	if (objectData.collider.type == "PLANE") { normal = objectData.collider.normal; }
	collisionAttribute = CollisionAttribute::Goal;
	collisionMask = CollisionMask::Goal;
}

void Goal::ChangeScore(Score nextScore)
{
	score = nextScore;
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

		if (GetNowScene() == Scene::Tutorial) { manager->NextPhase(); }
	}
}

void Goal::ChangeColor(float colorRate)
{
	object->material.GetSprite(TexType::Main)->color = initColor * colorRate;
}