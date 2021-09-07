#pragma once

#include <thread>

#include "philosopher.hpp"
#include "speaker.hpp"
#include "chopstick.hpp"

class Table
{
	std::vector<std::unique_ptr<Philosopher>> wisemen;

	Speaker speaker;

public:
	void init();

	std::vector<std::unique_ptr<Chopstick>> chopticks;

	void addAGuess(Philosopher* guess);

	void startDinner();
};