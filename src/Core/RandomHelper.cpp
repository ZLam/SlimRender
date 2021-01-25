#include "RandomHelper.h"

std::mt19937& RandomHelper::GetEngine()
{
	static std::random_device Seed_Gen;
	static std::mt19937 Engine(Seed_Gen());
	return Engine;
}
