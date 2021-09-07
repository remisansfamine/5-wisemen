#pragma once

#include <thread>

#include "wiseman.h"
#include "speaker.h"
#include "chopstick.h"

class Table
{
	std::vector<std::unique_ptr<Wiseman>> wisemen;

<<<<<<< HEAD
	Speaker speaker;

=======
>>>>>>> 45270cf2da9cbc94239532d6ebd43be4581e5467
public:
	void init();

	std::vector<std::unique_ptr<Chopstick>> chopticks;

	void addAGuess(Wiseman* guess);

	void startDinner();
};