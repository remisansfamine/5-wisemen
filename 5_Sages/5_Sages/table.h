#pragma once

#include <thread>

#include "wiseman.h"
#include "speaker.h"
#include "chopstick.h"

class Table
{
	std::vector<std::unique_ptr<Wiseman>> wisemen;

public:
	void init();

	std::vector<std::unique_ptr<Chopstick>> chopticks;
	Speaker speaker;

	void addAGuess(Wiseman* guess);

	void startDinner();
};