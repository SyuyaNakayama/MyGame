#pragma once
#include <random>
#include <memory>

// �����_�����N���X
class RandomDevice
{
protected:
	static std::random_device rnd;
	static std::mt19937 rnddev;
};

// int�^�����_��
class Random_Int : private RandomDevice
{
private:
	std::unique_ptr<std::uniform_int_distribution<int>> random;

public:
	// �R���X�g���N�^
	Random_Int(int min, int max);
	int operator()() { return (*random)(rnddev); }
};

// float�^�����_��
class Random_Float : private RandomDevice
{
private:
	std::unique_ptr<std::uniform_real_distribution<float>> random;

public:
	// �R���X�g���N�^
	Random_Float(float min, float max);
	float operator()() { return (*random)(rnddev); }
};