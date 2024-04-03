#pragma once
#include <random>
#include <memory>

namespace WristerEngine
{
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
		Random_Float(float min = 0, float max = 0);
		float operator()() { return (*random)(rnddev); }
	};

	// �m���w�胉���_�����[���b�g
	class Roulette
	{
	private:
		std::unique_ptr<Random_Int> random;
		std::vector<uint32_t> rateTable;

	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="rateTable">�m�����X�g</param>
		void Initialize(const std::vector<uint32_t>& rateTable);

		// ���ۂ̏o��
		size_t operator()() const;
	};
}