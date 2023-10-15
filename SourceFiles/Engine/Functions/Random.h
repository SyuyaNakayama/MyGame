#pragma once
#include <random>
#include <memory>

// ランダム基底クラス
class RandomDevice
{
protected:
	static std::random_device rnd;
	static std::mt19937 rnddev;
};

// int型ランダム
class Random_Int : private RandomDevice
{
private:
	std::unique_ptr<std::uniform_int_distribution<int>> random;

public:
	// コンストラクタ
	Random_Int(int min, int max);
	int operator()() { return (*random)(rnddev); }
};

// float型ランダム
class Random_Float : private RandomDevice
{
private:
	std::unique_ptr<std::uniform_real_distribution<float>> random;

public:
	// コンストラクタ
	Random_Float(float min, float max);
	float operator()() { return (*random)(rnddev); }
};