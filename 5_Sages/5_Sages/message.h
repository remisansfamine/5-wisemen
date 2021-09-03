#pragma once

#include <string>

struct SenderInfo
{
	std::string name;
	int textColor = 15;
};

struct Message
{
	SenderInfo sender;
	std::string action;
	int foregroundColor = 15;
	int backgroundColor = 0;
};