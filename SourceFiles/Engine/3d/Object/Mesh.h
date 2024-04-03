#pragma once
#include "Material.h"
#include <unordered_map>

namespace WristerEngine::_3D
{
	// �`��f�[�^
	class Mesh
	{
	private:
		// ���_�f�[�^�\����
		struct VertexData
		{
			Vector3 pos; // xyz���W
			Vector3 normal; // �@���x�N�g��
			Vector2 uv;  // uv���W
		};

		friend Material;
		// Microsoft::WRL::���ȗ�
		template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

		std::vector<VertexData> vertices;	// ���_�f�[�^�z��
		std::vector<UINT16> indices;		// ���_�C���f�b�N�X�z��
		std::unordered_map<UINT16, std::vector<UINT16>> smoothData;	// ���_���W�X���[�W���O�p�f�[�^
		ComPtr<ID3D12Resource> vertBuff;	// ���_�o�b�t�@
		D3D12_VERTEX_BUFFER_VIEW vbView{};	// ���_�o�b�t�@�r���[
		ComPtr<ID3D12Resource> indexBuff;	// �C���f�b�N�X�o�b�t�@
		D3D12_INDEX_BUFFER_VIEW ibView{};	// �C���f�b�N�X�o�b�t�@�r���[
		bool isSmooth = false;	// �X���[�W���O
		std::string modelName;	// ���f����
		std::string materialFileName;	// �}�e���A���t�@�C����
		std::string directoryPath;	// �f�B���N�g���p�X��

		// ���_�@���̕��ω�
		void CalculateSmoothedVertexNormals();
		// �o�b�t�@����
		void CreateBuffers();

	public:
		// obj�t�@�C���ǂݍ���
		void LoadOBJ(const std::string& modelName, bool isSmooth);
		// �`��
		void Draw();
	};
}