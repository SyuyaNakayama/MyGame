#pragma once
#include <memory>
#include <cassert>
#include <array>
#include <map>
#include "DirectXCommon.h"

namespace WristerEngine
{
	// result�l���G���[�Ȃ������Ɍx�����o��
	struct Result
	{
	private:
		HRESULT result = S_OK;

	public:
		// �R���X�g���N�^
		Result() {}
		Result(const HRESULT& result) { operator=(result); }

		void operator=(HRESULT result_)
		{
			result = result_;
			assert(SUCCEEDED(result));
		}
	};

	// �o�b�t�@����
	template<class T> void CreateBuffer(ID3D12Resource** buff, T** map, UINT64 width)
	{
		D3D12_HEAP_PROPERTIES heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		D3D12_RESOURCE_DESC resDesc = CD3DX12_RESOURCE_DESC::Buffer(width);
		// �o�b�t�@�̐���
		Result result = DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
			&heapProp, D3D12_HEAP_FLAG_NONE,
			&resDesc, D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr, IID_PPV_ARGS(buff));

		// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
		result = (*buff)->Map(0, nullptr, (void**)map);
		// �q���������
		(*buff)->Unmap(0, nullptr);
	}

	// �C���v�b�g���C�A�E�g�̒ǉ�
	D3D12_INPUT_ELEMENT_DESC SetInputLayout(LPCSTR semanticName, DXGI_FORMAT format);
	// �V�F�[�_�[�ǂݍ���
	void LoadShader(ID3DBlob** shaderBlob, std::wstring shaderName, LPCSTR target);

	/// <summary>
	/// �}���`�o�C�g����������C�h������ɕϊ�
	/// </summary>
	/// <param name="mString">�}���`�o�C�g������</param>
	/// <returns>���C�h������</returns>
	std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

	enum class RootParamType { CBV, DescriptorTable };

	// �p�C�v���C�������̐ݒ�
	struct PipelineProp
	{
	private:
		struct InputLayoutProp
		{
			LPCSTR semanticName;
			DXGI_FORMAT format;
		};

		struct BlendProp
		{
			D3D12_BLEND_OP blendOp = D3D12_BLEND_OP_ADD;
			D3D12_BLEND srcBlend = D3D12_BLEND_SRC_ALPHA;
			D3D12_BLEND destBlend = D3D12_BLEND_INV_SRC_ALPHA;
		};

		struct RootParameterProp
		{
			UINT descriptorNum;
			UINT constBuffNum;
		};

	public:
		// VS,PS,GS
		std::array<std::wstring, 3> shaderNames;
		std::vector<InputLayoutProp> inputLayoutProps;
		BlendProp blendProp;
		D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		bool isDepthTest = false; // �[�x�e�X�g���s�� = 3D�p ��
		D3D12_DEPTH_WRITE_MASK depthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		RootParameterProp rootParamProp;
		D3D12_TEXTURE_ADDRESS_MODE textureAddressMode = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		D3D12_CULL_MODE cullMode = D3D12_CULL_MODE_BACK;
	};

	enum class PipelineType { Sprite, PostEffect, MultiTexture,Object, Dissolve, Particle };

	// �p�C�v���C���Ǘ��N���X
	class PipelineManager
	{
		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
		static std::map<PipelineType, PipelineManager> pipelines;
		ComPtr<ID3D12RootSignature> rootSignature;
		ComPtr<ID3D12PipelineState> pipelineState;

	public:
		/// <summary>
		/// �p�C�v���C������
		/// </summary>
		/// <param name="pipelineProp">�p�C�v���C�������v���p�e�B</param>
		void CreatePipeline(const PipelineProp& pipelineProp);
		// ������
		static void Initialize();
		// �p�C�v���C���̃Z�b�g
		static void SetPipeline(PipelineType pipelineType);
	};
}