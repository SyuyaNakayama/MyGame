#include "Transform.h"
#include "D3D12Common.h"
#include "ModelManager.h"
using namespace WristerEngine;
using namespace _3D;

void Transform::Initialize()
{
	CreateBuffer(constBuffer.GetAddressOf(), &constMap, (sizeof(ConstBufferData) + 0xff) & ~0xff);
}

void Transform::Update()
{
	// �e�|�C���^�̍X�V
	if (parent) { parent->Update(); }
	// �X�V�ςȂ�֐��𔲂���
	if (isUpdated) { return; }
	Matrix4 matScale = Matrix4::Scale(scale); // �X�P�[���s��
	Matrix4 matRot = Matrix4::Rotate(rotation); // ��]�s��
	matWorld = matScale * matRot;
	matWorld.SetVector(translation, 3); // ���s�ړ���������
	if (parent) { matWorld *= parent->matWorld; } // �e�̃��[���h�s����|����
	isUpdated = true;
	constMap->world = matWorld;
}

void Transform::Draw()
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
	cmdList->SetGraphicsRootConstantBufferView(
		(UINT)RootParamNum::MatWorld, constBuffer->GetGPUVirtualAddress());
	isUpdated = false;
}

Vector3 Transform::GetScale() const
{
	Vector3 scale_;
	// �O���[�o���s�񂩂�X�P�[���l�𒊏o
	for (size_t i = 0; i < 3; i++) { scale_[i] = matWorld.GetVector(i).Length(); }
	return scale_;
}
