#pragma once

#include <thread>
#include <mutex>

#include <queue>
#include <string>

#include "message.hpp"

#include "utils.hpp"

class Speaker
{
private:
	bool mealIsOver = false;
	
	std::queue<Message> messages = std::queue<Message>();

	std::thread castThread;
	std::mutex castMutex;

	SenderInfo info;

	std::chrono::system_clock::time_point castStart;

	void castMessages();

public:
	Speaker();
	~Speaker();

	void stopMeal();

	bool isCastFinished();

	void narrate(const std::string& action);

	void sendMessage(const SenderInfo& sender, const std::string& action, int foregroundColor = 15, int backgroundColor = 0, const std::time_t& time = std::time(0));
};