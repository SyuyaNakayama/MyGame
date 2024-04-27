#pragma once
#include <string>
#include "Input.h"

// �Q�[���̑�����Ǘ�����N���X
class OperateConfig final
{
private:
	WristerEngine::Input* input = WristerEngine::Input::GetInstance();

	OperateConfig() = default;
	~OperateConfig() = default;

public:
	OperateConfig(const OperateConfig& obj) = delete;
	OperateConfig operator=(const OperateConfig& obj) = delete;

	static OperateConfig* GetInstance();
	bool GetPush(const std::string& str);
	bool GetTrigger(const std::string& str);
};