#pragma once
#include "Light.h"
#include "CircleShadow.h"
#include <wrl.h>
#include <d3d12.h>
#include <memory>
#include <array>

namespace WristerEngine
{
	// ���C�g
	class LightGroup
	{
	public:
		static const int DIR_LIGHT_NUM = 3;
		static const int POINT_LIGHT_NUM = 3;
		static const int SPOT_LIGHT_NUM = 3;
		static const int CIRCLE_SHADOW_NUM = 3;

	private:
		template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

		struct ConstBufferData
		{
			ColorRGB ambientColor;
			float pad1;
			DirectionalLight::ConstBufferData dirLights[DIR_LIGHT_NUM];
			PointLight::ConstBufferData pointLights[POINT_LIGHT_NUM];
			SpotLight::ConstBufferData spotLights[SPOT_LIGHT_NUM];
			CircleShadow::ConstBufferData circleShadows[CIRCLE_SHADOW_NUM];
		};

		ComPtr<ID3D12Resource> constBuff;
		ColorRGB ambientColor;
		std::array<DirectionalLight, DIR_LIGHT_NUM> dirLights;
		std::array<PointLight, POINT_LIGHT_NUM> pointLights;
		std::array<SpotLight, SPOT_LIGHT_NUM> spotLights;
		std::array<CircleShadow, CIRCLE_SHADOW_NUM> circleShadows;
		ConstBufferData* constMap = nullptr;

		// �萔�o�b�t�@�]��
		void TransferConstBuffer();
		// ������
		void Initialize();
		// �W���̃��C�g�ݒ�
		void DefaultLightSetting();

	public:
		/// <summary>
		/// �C���X�^���X����
		/// </summary>
		/// <returns>�C���X�^���X</returns>
		static std::unique_ptr<LightGroup> Create();
		// �X�V
		void Update(){ TransferConstBuffer(); }
		// �`��
		void Draw(UINT rootParameterIndex);
		// ������ύX
		void SetAmbientColor(const ColorRGB& color) { ambientColor = color; }
		// ���s�������擾
		DirectionalLight* GetDirectionalLight(uint32_t index);
		// �_�������擾
		PointLight* GetPointLight(uint32_t index);
		// �X�|�b�g���C�g���擾
		SpotLight* GetSpotLight(uint32_t index);
		// �ۉe���擾
		CircleShadow* GetCircleShadow(uint32_t index);
	};
}