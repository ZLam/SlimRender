#pragma once

#include <random>
#include "Types.h"

class RandomHelper
{
public:
	template<typename T>
	static T Random_Real(T min, T max)
	{
		std::uniform_real_distribution<T> dist(min, max);
		auto &mt = RandomHelper::GetEngine();
		return dist(mt);
	}

	template<typename T>
	static T Random_Int(T min, T max)
	{
		std::uniform_int_distribution<T> dist(min, max);
		auto &mt = RandomHelper::GetEngine();
		return dist(mt);
	}
private:
	static std::mt19937 &GetEngine();
};

inline uint32 Random(const uint32& Min, const uint32& Max)
{
	return RandomHelper::Random_Int(Min, Max);
}

inline float Random(const float& Min, const float& Max)
{
	return RandomHelper::Random_Real(Min, Max);
}
