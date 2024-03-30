#include "Block.h"
#include "Stage.h"
#include "ParticleManager.h"
#include "SceneManager.h"

using namespace WristerEngine::_3D;
using namespace WristerEngine::_2D;

std::map<Goal::Score, std::string> Goal::SCORE_TEX_NAME =
{
	{ Score::_M10,"Textures/score-10.png" },
	{ Score::_10, "Textures/score10.png" },
	{ Score::_20, "Textures/score20.png" },
	{ Score::_30, "Textures/score30.png" },
	{ Score::_50, "Textures/score50.png" }
};

const std::vector<Goal::Score> Goal::SCORE_TABLE =
{
	Score::_10, Score::_10, Score::_10, Score::_10,
	Score::_20, Score::_20, Score::_20, Score::_M10,
	Score::_30, Score::_30, Score::_30, Score::_50
};

WristerEngine::FrameTimer Goal::scoreChangeTimer = 600;
bool Goal::isScoreChange = false;
WristerEngine::Random_Int Goal::randScore(0, (int)SCORE_TABLE.size() - 1);
WristerEngine::Roulette Goal::roulette;

void Block::Initialize(const ObjectData& objectData)
{
	object = ModelManager::Create("cube");
	object->worldTransform.reset(objectData.worldTransform);
	worldTransform = object->worldTransform.get();
	Material& material = object->material;
	material.ambient = { 0,0,0 };
	material.diffuse = { 1,1,1 };
	material.specular = { 0,0,0 };
	Sprite* objectSprite = material.GetSprite(TexType::Main);

	const float WALL_SPLIT_NUM = 5.0f;
	objectSprite->textureSize.x *= worldTransform->scale.x / WALL_SPLIT_NUM;
	objectSprite->textureSize.y *= worldTransform->scale.z / WALL_SPLIT_NUM;

	if (objectData.collider.type == "PLANE") { normal = objectData.collider.normal; }
	if (objectData.fileName == "Ground") { collisionAttribute = CollisionAttribute::Ground; }
	else { collisionAttribute = CollisionAttribute::Block; }
	collisionMask = CollisionMask::Block;
}

void Block::OnCollision(BoxCollider* collider)
{
	WristerEngine::Physics* physics_ = collider->GetPhysics();
	if (!physics_) { return; }
	const float ZERO = 0.001f;
	if (normal.Length() <= ZERO) { return; }
	if (collisionAttribute == CollisionAttribute::Ground && physics_->IsFreeFall())
	{
		physics_->SetIsFreeFall(false);
		physics_->SetVelocity({});
		physics_->GetWorldTransform()->translation.y = worldTransform->GetWorldPosition().y + worldTransform->scale.y;
		return;
	}
	if (collisionAttribute == CollisionAttribute::Block)
	{
		physics_->Backlash(normal, 1.0f);
	}
}

void Goal::StaticUpdate()
{
	isScoreChange = scoreChangeTimer.Update();
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

void Goal::ChangeScore()
{
	Scene nowScene = GetNowScene();
	if (nowScene == Scene::Play) { score = SCORE_TABLE[randScore()]; }
	else if (nowScene == Scene::Tutorial) { score = Score::_10; }
	std::unique_ptr<WristerEngine::_2D::Sprite> newSprite = Sprite::Create(Goal::SCORE_TEX_NAME[score]);

	switch (score)
	{
	case Goal::Score::_M10:
		newSprite->color = WristerEngine::ColorRGBA::Blue();
		break;
	case Goal::Score::_10:
		newSprite->color = WristerEngine::ColorRGBA::White();
		break;
	case Goal::Score::_20:
		newSprite->color = { 1,1,0.5f,1 };
		break;
	case Goal::Score::_30:
		newSprite->color = WristerEngine::ColorRGBA::Yellow();
		break;
	case Goal::Score::_50:
		newSprite->color = WristerEngine::ColorRGBA::Red();
		break;
	}

	initColor = newSprite->color;
	Material& material = object->material;
	if (score == Score::_M10) { material.ambient = { 1,1,1 }; }
	else { material.ambient = { 0.2f,0.2f,0.2f }; }

	newSprite->size.x *= -1.0f;
	newSprite->Update();
	material.SetSprite(std::move(newSprite), TexType::Main);
}

void Goal::Update()
{
	if (GetNowScene() == Scene::Tutorial) { return; }
	// スコアの変更
	if (isScoreChange) { ChangeScore(); }

	// ゴールの点滅開始時間
	const int START_BLINK_TIME = 120;
	// 点滅回数
	const int BLINK_NUM = 4;

	int remainTime = scoreChangeTimer.GetRemainTime();
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
			TutorialEventManager::GetInstance()->NextPhase();
		}
	}
}