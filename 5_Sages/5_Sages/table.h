#pragma once

#include <thread>

#include "wiseman.h"
#include "speaker.h"
#include "chopstick.h"

class Table
{
	std::vector<std::unique_ptr<Wiseman>> wisemen;

	Speaker speaker;

public:
	void init();

	std::vector<std::unique_ptr<Chopstick>> chopticks;

	void addAGuess(Wiseman* guess);

	void startDinner();
};