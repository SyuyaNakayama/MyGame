#pragma once
#include "Transform.h"
#include "Physics.h"
#include <vector>
#include <array>
#include <memory>

// �R���C�_�[�̑���
enum class CollisionAttribute
{
	Player = 0b1,
	Block = 0b1 << 1,
	Ground = 0b1 << 2,
	Object = 0b1 << 3,
	Goal = 0b1 << 4,
	All = -1
};

// �R���C�_�[�̃}�X�N
enum class CollisionMask
{
	None = 0,
	All = -1,
	Player = CollisionMask::All,
	Block = (int)CollisionAttribute::Player | (int)CollisionAttribute::Object,
	Object = (int)CollisionMask::All,
	Goal = (int)CollisionAttribute::Player | (int)CollisionAttribute::Object,
};

namespace WristerEngine
{
	class BoxCollider;
	class SphereCollider;
	class PlaneCollider;
	class PolygonCollider;
	class RayCollider;
	class IncludeCollider;
	class MeshCollider;

	// �R���C�_�[���N���X
	class BaseCollider
	{
	protected:
		CollisionAttribute collisionAttribute = CollisionAttribute::All;
		CollisionMask collisionMask = CollisionMask::All;
		_3D::Transform* worldTransform = nullptr;
		std::unique_ptr<Physics> physics;

	public:
		virtual ~BaseCollider() = default;

		// �Փ˃R�[���o�b�N�֐�
		virtual void OnCollision([[maybe_unused]] BoxCollider* boxCollider) {}
		virtual void OnCollision([[maybe_unused]] SphereCollider* sphereCollider) {}
		virtual void OnCollision([[maybe_unused]] PlaneCollider* boxCollider) {}
		virtual void OnCollision([[maybe_unused]] PolygonCollider* sphereCollider) {}
		virtual void OnCollision([[maybe_unused]] RayCollider* sphereCollider) {}
		virtual void OnCollision([[maybe_unused]] IncludeCollider* sphereCollider) {}

		// setter
		void SetCollisionAttribute(CollisionAttribute collisionAttribute_) { collisionAttribute = collisionAttribute_; }
		void SetCollisionMask(CollisionMask collisionMask_) { collisionMask = collisionMask_; }
		void SetWorldTransform(_3D::Transform* worldTransform_) { worldTransform = worldTransform_; }
		// getter
		CollisionAttribute GetCollisionAttribute() { return collisionAttribute; }
		CollisionMask GetCollisionMask() { return collisionMask; }
		virtual Vector3 GetWorldPosition() { return worldTransform->GetWorldPosition(); }
		Physics* GetPhysics() { return physics.get(); }
	};

	// �{�b�N�X�R���C�_�[(AABB����)
	class BoxCollider : public virtual BaseCollider
	{
	public:
		// �R���X�g���N�^
		BoxCollider();
		// ���z�f�X�g���N�^
		virtual ~BoxCollider();
		// 3�������̔��a���擾
		virtual Vector3 GetRadius3D() { return worldTransform->scale; }
	};

	// ���S��܂̃{�b�N�X�R���C�_�[(AABB����)
	class IncludeCollider : public virtual BaseCollider
	{
	public:
		enum class Axis { X, Y, Z };

	private:
		// ���S��ܔ��a
		static float includeRadius;
		// �����蔻������y�A��true�����Ȃ��ق����v�Z�ɔ��f�����
		std::array<bool, 3> isUseAxis = { true,true,true };

	public:
		// �R���X�g���N�^
		IncludeCollider();
		// ���z�f�X�g���N�^
		virtual ~IncludeCollider();
		// ���S��ܔ��a�̎擾
		static float GetIncludeRadius() { return includeRadius; }
		// �g�����̐ݒ�
		void SetUseAxis(Axis axis, bool isUse) { isUseAxis[(size_t)axis] = isUse; }
		// �g�����̎擾
		std::array<bool, 3> GetUseAxis() { return isUseAxis; }
	};

	// ���R���C�_�[
	class SphereCollider : public virtual BaseCollider
	{
	public:
		// �R���X�g���N�^
		SphereCollider();
		// ���z�f�X�g���N�^
		virtual ~SphereCollider();
		// ���a�擾
		virtual float GetRadius() { return worldTransform->scale.x; }
	};

	// ���ʃR���C�_�[
	class PlaneCollider : public virtual BaseCollider
	{
	protected:
		// ��@��
		Vector3 baseNormal = Vector3::MakeAxis(Axis::Z);
		float distance = 0;
		Vector3 inter;

	public:
		// �R���X�g���N�^
		PlaneCollider();
		// ���z�f�X�g���N�^
		virtual ~PlaneCollider();
		// setter
		void SetInter(const Vector3& inter_) { inter = inter_; }
		void SetDistance(float distance_) { distance = distance_; }
		void SetRotation(const Vector3& rotation) { worldTransform->rotation = rotation; }
		void SetBaseNormal(const Vector3& baseNormal_) { baseNormal = baseNormal_; }
		// getter
		virtual Vector3 GetNormal() { return baseNormal * Matrix4::Rotate(worldTransform->rotation); }
		virtual Vector3* GetInter() { return &inter; }
		virtual float GetDistance() { return distance; }
	};

	// ���p�`���ʃR���C�_�[
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
		// �R���X�g���N�^
		PolygonCollider();
		// ���z�f�X�g���N�^
		virtual ~PolygonCollider();
		// ���_�X�V
		void UpdateVertices();
		// �������v�Z
		void ComputeDistance() { distance = Dot(GetNormal(), vertices[0]); }
		// �@�����v�Z
		void ComputeNormal();
		// ���ʂɕϊ�����
		void ToPlaneCollider(PlaneCollider* planeCollider);
		// ���_��ǉ�
		void AddVertices(Vector3 pos) { vertices.push_back(pos); }
		// setter
		void SetBaseNormal(Vector3 baseNormal_) { baseNormal = baseNormal_; }
		virtual void SetVertices();
		// getter
		virtual Vector3 GetNormal() { return baseNormal * Matrix4::Rotate(worldTransform->rotation); }
		virtual std::vector<Vector3> GetVertices() { return vertices; }
	};

	// ���C�R���C�_�[
	class RayCollider : public virtual BaseCollider
	{
	public:
		// ����C
		Vector3 baseRayDirection = Vector3::MakeAxis(Axis::Z);
		// �R���X�g���N�^
		RayCollider();
		// ���z�f�X�g���N�^
		virtual ~RayCollider();
		// ���C�������擾
		virtual const Vector3 GetRayDirection() { return baseRayDirection * Matrix4::Rotate(worldTransform->rotation); }
	};
}

// ���b�V���R���C�_�[
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