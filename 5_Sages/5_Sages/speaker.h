#pragma once

#include <thread>
#include <mutex>

#include <queue>
#include <string>

#include <windows.h>

#include "message.h"

#include "utils.h"

class Speaker
{
private:
	std::queue<Message> messages = std::queue<Message>();

	std::thread castThread;
	std::mutex castMutex;
		
	void castMessages();

	bool isUsed = false;

	HANDLE consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);

	SenderInfo info;

public:
	bool mealIsOver = false;

	Speaker();
	~Speaker();

	void sendMessage(const Message& message);
};