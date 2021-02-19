#pragma once

#include <string>

class Vector3;

static class Logger
{
public:
	static void Log(const std::string& str);
	static void Log(Vector3 vec);
};