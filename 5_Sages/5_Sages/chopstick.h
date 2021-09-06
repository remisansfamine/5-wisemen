#pragma once

#include <mutex>

#include "wiseman.h"

class Chopstick
{
	std::unique_ptr<std::mutex> m_mutex = std::unique_ptr<std::mutex>(new std::mutex);
	Wiseman* owner = nullptr;

public:
	void setOwner(Wiseman* newOwner);

	bool isTaken();
	std::string getOwnerName();
};