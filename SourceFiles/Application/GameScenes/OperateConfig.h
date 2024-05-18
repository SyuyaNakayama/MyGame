#pragma once
#include "Input.h"
#include "Constant.h"
#include <Sprite.h>

// �Q�[���̑�����Ǘ�����N���X
class OperateConfig final
{
private:
	WristerEngine::Input* input = WristerEngine::Input::GetInstance();
	WristerEngine::Constant* constant = WristerEngine::Constant::GetInstance();

	OperateConfig() = default;
	~OperateConfig() = default;

	std::unique_ptr<WristerEngine::_2D::Sprite> LoadSprite(const std::string& str);

public:
	OperateConfig(const OperateConfig& obj) = delete;
	OperateConfig operator=(const OperateConfig& obj) = delete;

	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static OperateConfig* GetInstance();

	/// <summary>
	/// ����L�[�������ꂽ�����擾
	/// </summary>
	/// <param name="str">����L�[</param>
	/// <returns>����L�[�������ꂽ��</returns>
	bool GetPush(const std::string& str);

	/// <summary>
	/// ����L�[�������ꂽ�u�Ԃ����擾
	/// </summary>
	/// <param name="str">����L�[</param>
	/// <returns>����L�[�������ꂽ�u�Ԃ�</returns>
	bool GetTrigger(const std::string& str);

	/// <summary>
	/// ����L�[��UI�𐶐�
	/// </summary>
	/// <param name="str">����L�[</param>
	/// <returns>����L�[��Sprite�C���X�^���X(unique_ptr)</returns>
	std::unique_ptr<WristerEngine::_2D::Sprite> CreateOperateSprite(const std::string& str);
	
	std::unique_ptr<WristerEngine::_2D::Sprite> CreateOperateSpriteAnimation(const std::string& str);
};