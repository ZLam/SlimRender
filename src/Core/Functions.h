#pragma once

#include <bitset>
#include "Types.h"

std::string Float2BinStr(float Value)
{
	uint32 t;
	std::memcpy(&t, &Value, sizeof(Value));
	return std::bitset<sizeof(float) * 8>(t).to_string();
}

std::string Double2BinStr(double Value)
{
	uint64 t;
	std::memcpy(&t, &Value, sizeof(Value));
	return std::bitset<sizeof(double) * 8>(t).to_string();
}