#pragma once

#include <bitset>
#include <filesystem>

#ifdef __WIN32__
#include <windows.h>
#elif __linux__
#include <sstream>
#include <unistd.h>
#elif __APPLE__
#include <mach-o/dyld.h>
#endif

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

static std::string GetExecDir()
{
	unsigned int bufferSize = 512;
	std::vector<char> buffer(bufferSize + 1);
	
#ifdef __WIN32__
	::GetModuleFileName(NULL, &buffer[0], bufferSize);
#elif __linux__
	// Get the process ID.
	int pid = getpid();

	// Construct a path to the symbolic link pointing to the process executable.
	// This is at /proc/<pid>/exe on Linux systems (we hope).
	std::ostringstream oss;
	oss << "/proc/" << pid << "/exe";
	std::string link = oss.str();

	// Read the contents of the link.
	int count = readlink(link.c_str(), &buffer[0], bufferSize);
	if (count == -1) throw std::runtime_error("Could not read symbolic link");
	buffer[count] = '\0';
#elif __APPLE__
	if (_NSGetExecutablePath(&buffer[0], &bufferSize))
	{
		buffer.resize(bufferSize);
		_NSGetExecutablePath(&buffer[0], &bufferSize);
	}
#endif
	
	std::filesystem::path p = &buffer[0];
	p.remove_filename();
	
	return p.generic_string();
}

static std::string GetResDir()
{
	auto ProjectDir = GetExecDir();
	return ProjectDir.append("res/");
}

static std::string ResFullPath(const std::string& InFilePath)
{
	auto ResDir = GetResDir();
	return ResDir.append(InFilePath);
}
