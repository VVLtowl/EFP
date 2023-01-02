#pragma once
#include <string>

const int BDEBUG_INFO_MAX = 20;

class DebugInfo
{
public:
	static std::string m_Info[BDEBUG_INFO_MAX];
	static void Update();

	static void Print(std::string info);
};

