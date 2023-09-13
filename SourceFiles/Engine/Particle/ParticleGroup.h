#pragma once
#include "DiffuseParticle.h"
#include "DirectionalParticle.h"
#include "TrackParticle.h"
#include "Sprite.h"
#include <string>
#include <wrl.h>
#include <d3dx12.h>

// ���̃C���X�^���X1�ɂ�1���̃e�N�X�`�����g����
class ParticleGroup
{
private:
	// ���_�f�[�^�\����
	struct VertexPos
	{
		Vector3 pos; // xyz���W
		float scale; // �X�P�[��
	};

	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	static const int PARTICLE_MAX = 384; // �p�[�e�B�N���ő吔
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	VertexPos* vertMap;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// �e�N�X�`���C���f�b�N�X
	TextureData* texture = nullptr;
	// �g�U����p�[�e�B�N��
	DiffuseParticle diffuseParticle;
	// �n�_����I�_�֌������p�[�e�B�N��
	DirectionalParticle directionalParticle;
	TrackParticle trackParticle;

	void CreateVertexBuffer(); // ���_�o�b�t�@����
	size_t AllParticleNum() { return diffuseParticle.GetParticles().size() + directionalParticle.GetParticles().size() + trackParticle.GetParticles().size(); }
	bool IsParticleMax() { return AllParticleNum() >= PARTICLE_MAX; }

public:
	void Initialize(const std::string& textureName);
	void Update(); // ���t���[������
	void Draw(); // �`��
	// �p�[�e�B�N���̒ǉ�
	void Add(const DiffuseParticle::AddProp& particleProp);
	void Add(const DirectionalParticle::AddProp& particleProp);
	void Add(const TrackParticle::AddProp& particleProp);
	void Clear(); // �p�[�e�B�N���̍폜
};