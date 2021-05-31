#pragma once

#include <bitset>
#include <filesystem>
#include "Types.h"

static std::string Float2BinStr(float Value)
{
	uint32 t;
	std::memcpy(&t, &Value, sizeof(Value));
	return std::bitset<sizeof(float) * 8>(t).to_string();
}

static std::string Double2BinStr(double Value)
{
	uint64 t;
	std::memcpy(&t, &Value, sizeof(Value));
	return std::bitset<sizeof(double) * 8>(t).to_string();
}

static std::string GetProjectDir()
{
	std::string Ret = "";
	auto CurPath = std::filesystem::current_path();
#ifdef __WIN32__
	Ret = CurPath.parent_path().parent_path().parent_path().generic_string();
#elif __APPLE__
    Ret = CurPath.generic_string();
#endif
	return Ret;
}

static std::string GetResDir()
{
	auto ProjectDir = GetProjectDir();
	return ProjectDir.append("/res");
}

static std::string ResFullPath(const std::string& InFilePath)
{
	auto ResDir = GetResDir();
	return ResDir.append(InFilePath);
}
