#pragma once

#include <mutex>

#include "wiseman.h"

class Chopstick
{

public:
	std::unique_ptr<std::mutex> m_mutex = std::unique_ptr<std::mutex>(new std::mutex);

	Wiseman* owner = nullptr;

	bool isTaken();
	std::string getOwnerName();
};