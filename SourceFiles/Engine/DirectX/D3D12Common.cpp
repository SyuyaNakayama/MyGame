#include "D3D12Common.h"
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
using namespace std;
using namespace WristerEngine;

map<PipelineType, PipelineManager> PipelineManager::pipelines;

D3D12_INPUT_ELEMENT_DESC WristerEngine::SetInputLayout(LPCSTR semanticName, DXGI_FORMAT format)
{
	D3D12_INPUT_ELEMENT_DESC inputLayout =
	{
		semanticName, 0, format, 0,
		D3D12_APPEND_ALIGNED_ELEMENT,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	};
	return inputLayout;
}

void WristerEngine::LoadShader(ID3DBlob** shaderBlob, wstring shaderName, LPCSTR target)
{
	ID3DBlob* errorBlob = nullptr;

	wstring fileName = L"Resources/shaders/" + shaderName + L".hlsl";
	//�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	HRESULT result = D3DCompileFromFile(
		fileName.c_str(), // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
		"main", target, // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0,
		shaderBlob, &errorBlob);
	// �G���[�Ȃ�
	if (FAILED(result)) {
		// errorBlob����G���[���e��string�^�ɃR�s�[
		string error;
		error.resize(errorBlob->GetBufferSize());
		copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(error.c_str());
		assert(0);
	}
}

std::wstring WristerEngine::ConvertMultiByteStringToWideString(const std::string& mString)
{
	// ���C�h������ɕϊ������ۂ̕�����o�b�t�@�T�C�Y���v�Z
	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);
	// ���C�h������ɕϊ�
	vector<wchar_t> wfilePath(filePathBufferSize);
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, wfilePath.data(), filePathBufferSize);

	return wfilePath.data();
}

void PipelineManager::Initialize()
{
	PipelineProp pipelineProp;
	pipelineProp.shaderNames = { L"SpriteVS", L"SpritePS" };
	pipelineProp.inputLayoutProps.push_back({ "POSITION", DXGI_FORMAT_R32G32_FLOAT });
	pipelineProp.inputLayoutProps.push_back({ "TEXCOORD", DXGI_FORMAT_R32G32_FLOAT });
	pipelineProp.rootParamProp = { 1,1 };
	pipelineProp.cullMode = D3D12_CULL_MODE_NONE;
	pipelines[PipelineType::Sprite].CreatePipeline(pipelineProp);

	pipelineProp.shaderNames = { L"PostEffectVS", L"PostEffectPS" };
	pipelineProp.textureAddressMode = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	pipelineProp.cullMode = D3D12_CULL_MODE_BACK;
	pipelines[PipelineType::PostEffect].CreatePipeline(pipelineProp);
	
	pipelineProp.shaderNames = { L"PostEffectVS", L"MultiTexturePS" };
	pipelineProp.rootParamProp = { 2,1 };
	pipelines[PipelineType::MultiTexture].CreatePipeline(pipelineProp);

	pipelineProp.shaderNames = { L"ObjVS", L"ObjPS" };
	pipelineProp.inputLayoutProps.clear();
	pipelineProp.inputLayoutProps.push_back({ "POSITION", DXGI_FORMAT_R32G32B32_FLOAT });
	pipelineProp.inputLayoutProps.push_back({ "NORMAL", DXGI_FORMAT_R32G32B32_FLOAT });
	pipelineProp.inputLayoutProps.push_back({ "TEXCOORD", DXGI_FORMAT_R32G32_FLOAT });
	pipelineProp.textureAddressMode = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	pipelineProp.isDepthTest = true;
	pipelineProp.rootParamProp = { 5,4 };
	pipelines[PipelineType::Object].CreatePipeline(pipelineProp);
	
	pipelineProp.cullMode = D3D12_CULL_MODE_NONE;
	pipelines[PipelineType::Dissolve].CreatePipeline(pipelineProp);
	
	pipelineProp.shaderNames = { L"ParticleVS", L"ParticlePS", L"ParticleGS" };
	pipelineProp.inputLayoutProps.clear();
	pipelineProp.inputLayoutProps.push_back({ "POSITION", DXGI_FORMAT_R32G32B32_FLOAT });
	pipelineProp.inputLayoutProps.push_back({ "TEXCOORD", DXGI_FORMAT_R32_FLOAT });
	pipelineProp.blendProp = { D3D12_BLEND_OP_ADD, D3D12_BLEND_ONE, D3D12_BLEND_ONE };
	pipelineProp.rootParamProp = { 1,1 };
	pipelineProp.depthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	pipelineProp.primitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
	pipelineProp.cullMode = D3D12_CULL_MODE_BACK;
	pipelines[PipelineType::Particle].CreatePipeline(pipelineProp);
}

void PipelineManager::CreatePipeline(const PipelineProp& pipelineProp)
{
	ComPtr<ID3DBlob> vsBlob, gsBlob, psBlob;
	LoadShader(&vsBlob, pipelineProp.shaderNames[0], "vs_5_0");
	LoadShader(&psBlob, pipelineProp.shaderNames[1], "ps_5_0");
	if (!pipelineProp.shaderNames[2].empty()) { LoadShader(&gsBlob, pipelineProp.shaderNames[2], "gs_5_0"); }

	std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout;
	for (auto& inputLayoutProp : pipelineProp.inputLayoutProps)
	{
		inputLayout.push_back(SetInputLayout(inputLayoutProp.semanticName, inputLayoutProp.format));
	}

	std::vector<CD3DX12_ROOT_PARAMETER> rootParams;
	// �f�X�N���v�^�����W
	for (UINT i = 0; i < pipelineProp.rootParamProp.descriptorNum; i++)
	{
		CD3DX12_DESCRIPTOR_RANGE* descriptorRange = new CD3DX12_DESCRIPTOR_RANGE();
		descriptorRange->Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, i);
		CD3DX12_ROOT_PARAMETER rootParam{};
		rootParam.InitAsDescriptorTable(1, descriptorRange);
		rootParams.push_back(rootParam);
	}

	for (UINT i = 0; i < pipelineProp.rootParamProp.constBuffNum; i++)
	{
		CD3DX12_ROOT_PARAMETER rootParam{};
		rootParam.InitAsConstantBufferView(i);
		rootParams.push_back(rootParam);
	}

	// �����_�[�^�[�Q�b�g�̃u�����h�ݒ�
	D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;	// RBGA�S�Ẵ`�����l����`��
	blenddesc.BlendEnable = true;
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;
	blenddesc.BlendOp = pipelineProp.blendProp.blendOp;
	blenddesc.SrcBlend = pipelineProp.blendProp.srcBlend;
	blenddesc.DestBlend = pipelineProp.blendProp.destBlend;

	// �X�^�e�B�b�N�T���v���[
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0, D3D12_FILTER_MIN_MAG_MIP_POINT,
		pipelineProp.textureAddressMode, pipelineProp.textureAddressMode);

	// ���[�g�V�O�l�`���̐ݒ�
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Init_1_0((UINT)rootParams.size(), rootParams.data(), 1, &samplerDesc,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> rootSigBlob, errorBlob;
	// �o�[�W������������̃V���A���C�Y
	Result result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	// ���[�g�V�O�l�`���̐���
	ID3D12Device* device = DirectXCommon::GetInstance()->GetDevice();
	result = device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));

	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipeline{};
	// �O���t�B�b�N�X�p�C�v���C���̗����ݒ�
	pipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	pipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());
	if (gsBlob) { pipeline.GS = CD3DX12_SHADER_BYTECODE(gsBlob.Get()); }
	// �T���v���}�X�N
	pipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�
	// ���X�^���C�U�X�e�[�g
	pipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	pipeline.RasterizerState.CullMode = pipelineProp.cullMode;
	// �}�`�̌`��ݒ�
	pipeline.PrimitiveTopologyType = pipelineProp.primitiveTopologyType;
	// �u�����h�X�e�[�g�̐ݒ�
	pipeline.BlendState.RenderTarget[0] = blenddesc;

	// ���_���C�A�E�g�̐ݒ�
	pipeline.InputLayout.pInputElementDescs = inputLayout.data();
	pipeline.InputLayout.NumElements = (UINT)inputLayout.size();

	pipeline.NumRenderTargets = 1;	// �`��Ώۂ�1��
	pipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0�`255�w���RGBA
	pipeline.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

	// 3D�p�p�C�v���C��
	if (pipelineProp.isDepthTest)
	{
		// �f�v�X�X�e���V���X�e�[�g
		pipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
		// �[�x�o�b�t�@�̃t�H�[�}�b�g
		pipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		pipeline.DepthStencilState.DepthWriteMask = pipelineProp.depthWriteMask;
	}

	pipeline.pRootSignature = rootSignature.Get();

	// �O���t�B�b�N�X�p�C�v���C���̐���
	result = device->CreateGraphicsPipelineState(&pipeline, IID_PPV_ARGS(&pipelineState));
}

void PipelineManager::SetPipeline(PipelineType type)
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	cmdList->SetPipelineState(pipelines[type].pipelineState.Get());
	cmdList->SetGraphicsRootSignature(pipelines[type].rootSignature.Get());
}