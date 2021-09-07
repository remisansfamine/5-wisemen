#pragma once

#include <string>
#include <windows.h>

#include <ctime>

struct SenderInfo
{
	std::string name;
	int textColor = 15;
};

class Message
{
private:
	static HANDLE consoleHandler;
	SenderInfo sender;
	std::string action;
	int foregroundColor = 15;
	int backgroundColor = 0;
	std::time_t sendingTime;

public:
	Message(const SenderInfo& sender, const std::string& action, int foregroundColor = 15, int backgroundColor = 0, const std::time_t& time = std::time(0));

	void display();
};