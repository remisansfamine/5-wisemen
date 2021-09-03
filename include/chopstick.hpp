#pragma once

#include <mutex>

#include "philosopher.hpp"

class Chopstick
{
public:
	std::unique_ptr<std::mutex> m_mutex = std::unique_ptr<std::mutex>(new std::mutex);

	Philosopher* owner = nullptr;

	bool isTaken();
	std::string getOwner();
};