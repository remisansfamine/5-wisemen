#pragma once

#include <mutex>

#include "philosopher.hpp"

class Chopstick
{
	std::unique_ptr<std::mutex> m_mutex = std::unique_ptr<std::mutex>(new std::mutex);
	Philosopher* owner = nullptr;

public:
	void setOwner(Philosopher* newOwner);

	bool isTaken();
	std::string getOwnerName();
};