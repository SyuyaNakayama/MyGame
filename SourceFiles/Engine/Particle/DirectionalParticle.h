#pragma once
#include "Timer.h"
#include <list>
#include "Vector.h"

namespace WristerEngine
{
	// 始点から終点へ向かうパーティクル
	class DirectionalParticle
	{
	public:
		// パーティクル1粒
		struct Particle
		{
			Vector3 start; // 始点
			Vector3 end; // 終点
			Vector3 position;
			float scale = 1;
			unsigned short splitNum = 1;
			float angle = 0;
			float radius = 0;
			FrameTimer frame;
			std::vector<Vector3> controlPoints; // 制御点

			void ComputeControlPoints();
			void Update();
		};

		struct AddProp
		{
			Vector3 start;
			Vector3 end;
			float scale = 1;
			unsigned short splitNum = 1; // 制御点の数
			float angle = 0; // {0,1,0}が0ラジアン
			float radius = 0;
			int lifeTime = 60;
		};

	private:
		std::list<Particle> particles;

	public:
		// 更新
		void Update();
		// パーティクル削除
		void Clear() { particles.clear(); }
		// パーティクル追加
		void Add(const AddProp& particleProp);
		// パーティクルリスト取得
		const std::list<Particle>& GetParticles() const { return particles; }
	};
}