#pragma once
#include "WorldTransform.h"
#include "Physics.h"
#include <vector>
#include <array>
#include <memory>

enum class CollisionAttribute
{
	Player = 0b1,
	Block = 0b1 << 1,
	Ground = 0b1 << 2,
	Object = 0b1 << 3,
	Goal = 0b1 << 4,
	All = -1
};

enum class CollisionMask
{
	None = 0,
	All = -1,
	Player = CollisionMask::All,
	Block = (int)CollisionAttribute::Player | (int)CollisionAttribute::Object,
	Object = (int)CollisionMask::All,
	Goal = (int)CollisionAttribute::Player | (int)CollisionAttribute::Object,
};

class BoxCollider;
class SphereCollider;
class PlaneCollider;
class PolygonCollider;
class RayCollider;
class IncludeCollider;
class MeshCollider;

class BaseCollider
{
protected:
	CollisionAttribute collisionAttribute = CollisionAttribute::All;
	CollisionMask collisionMask = CollisionMask::All;
	WorldTransform* worldTransform = nullptr;
	std::unique_ptr<Physics> physics;

public:
	virtual ~BaseCollider() = default;

	virtual void OnCollision(BoxCollider* boxCollider) {}
	virtual void OnCollision(SphereCollider* sphereCollider) {}
	virtual void OnCollision(PlaneCollider* boxCollider) {}
	virtual void OnCollision(PolygonCollider* sphereCollider) {}
	virtual void OnCollision(RayCollider* sphereCollider) {}
	virtual void OnCollision(IncludeCollider* sphereCollider) {}

	CollisionAttribute GetCollisionAttribute() { return collisionAttribute; }
	CollisionMask GetCollisionMask() { return collisionMask; }
	virtual Vector3 GetWorldPosition() { return worldTransform->GetWorldPosition(); }
	Physics* GetPhysics() { return physics.get(); }
	void SetWorldTransform(WorldTransform* worldTransform_) { worldTransform = worldTransform_; }
};

class BoxCollider : public virtual BaseCollider
{
public:
	BoxCollider();
	virtual ~BoxCollider();

	virtual Vector3 GetRadius3D() { return worldTransform->scale; }
};

class IncludeCollider : public virtual BaseCollider
{
public:
	enum class Axis { X, Y, Z };

private:
	static float includeRadius;
	// �����蔻������y�A��true�����Ȃ��ق����v�Z�ɔ��f�����
	std::array<bool, 3> isUseAxis = { true,true,true };

public:
	IncludeCollider();
	virtual ~IncludeCollider();

	static float GetIncludeRadius() { return includeRadius; }
	void SetUseAxis(Axis axis, bool isUse) { isUseAxis[(size_t)axis] = isUse; }
	std::array<bool, 3> GetUseAxis() { return isUseAxis; }
};

class SphereCollider : public virtual BaseCollider
{
public:
	SphereCollider();
	virtual ~SphereCollider();

	virtual float GetRadius() { return worldTransform->scale.x; }
};

class PlaneCollider : public virtual BaseCollider
{
protected:
	// ��@��
	Vector3 baseNormal = Vector3::MakeAxis(Axis::Z);
	float distance = 0;
	Vector3 inter;

public:
	PlaneCollider();
	virtual ~PlaneCollider();

	void SetInter(const Vector3& inter_) { inter = inter_; }
	void SetDistance(float distance_) { distance = distance_; }
	void SetRotation(const Vector3& rotation) { worldTransform->rotation = rotation; }
	void SetBaseNormal(const Vector3& baseNormal_) { baseNormal = baseNormal_; }
	virtual Vector3 GetNormal() { return baseNormal * Matrix4::Rotate(worldTransform->rotation); }
	virtual Vector3* GetInter() { return &inter; }
	virtual float GetDistance() { return distance; }
};

class PolygonCollider : public virtual BaseCollider
{
protected:
	// ��@��
	Vector3 baseNormal = Vector3::MakeAxis(Axis::Y);
	// ���_�͎��v���
	std::vector<Vector3> vertices;
	float distance = 0;
	// ���b�V���R���C�_�[�Ŏg��
	Vector3 normal;

public:
	PolygonCollider();
	virtual ~PolygonCollider();

	void UpdateVertices();
	void ComputeDistance() { distance = Dot(GetNormal(), vertices[0]); }
	void ComputeNormal();
	void ToPlaneCollider(PlaneCollider* planeCollider);
	void AddVertices(Vector3 pos) { vertices.push_back(pos); }
	void SetBaseNormal(Vector3 baseNormal_) { baseNormal = baseNormal_; }
	virtual Vector3 GetNormal() { return baseNormal * Matrix4::Rotate(worldTransform->rotation); }
	virtual void SetVertices();
	virtual std::vector<Vector3> GetVertices() { return vertices; }
};

class RayCollider : public virtual BaseCollider
{
public:
	// ����C
	Vector3 baseRayDirection = Vector3::MakeAxis(Axis::Z);
	RayCollider();
	virtual ~RayCollider();

	virtual const Vector3 GetRayDirection() { return baseRayDirection * Matrix4::Rotate(worldTransform->rotation); }
};

//class MeshCollider : public BaseCollider
//{
//private:
//	// ���[���h�s��̋t�s��
//	Matrix4 invMatWorld;
//
//public:
//	std::vector<PolygonCollider> triangles;
//	void ConstructTriangles(ModelManager* model);
//};