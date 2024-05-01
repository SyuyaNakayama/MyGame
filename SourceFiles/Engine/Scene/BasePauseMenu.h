#pragma once
#include "BaseScene.h"
#include "Sprite.h"
#include "Constant.h"
#include <map>

namespace WristerEngine
{
	class BasePauseMenu
	{
	protected:
		bool isPause = false;

		std::map<std::string, std::unique_ptr<_2D::Sprite>> sprites;
		Constant* constant = Constant::GetInstance();

	public:
		virtual ~BasePauseMenu() = default;
		virtual void Initialize() = 0;
		virtual void Update();
		void Draw();
		void Pause() { isPause = !isPause; }
		bool IsPause() const { return isPause; }
	};
}