#pragma once
#include "SceneManager.h"
#include "DirectXCommon.h"
#include "Constant.h"

namespace WristerEngine
{
	// �Q�[�������̘g�g�݃N���X
	class Framework
	{
	protected:
		std::wstring windowName;
		WindowsAPI* wAPI = WindowsAPI::GetInstance();
		Input* input = Input::GetInstance();
		DirectXCommon* dxCommon = DirectXCommon::GetInstance();
		SceneManager* sceneManager = SceneManager::GetInstance();
		Constant* constant = Constant::GetInstance();

	public:
		virtual ~Framework() = default;
		// ������
		virtual void Initialize();
		// �I��
		virtual void Finalize();
		// �X�V
		virtual void Update();
		// �`��
		virtual void Draw() = 0;
		// �I���`�F�b�N
		virtual bool IsEndRequest();
		// ���s
		void Run();
	};
}