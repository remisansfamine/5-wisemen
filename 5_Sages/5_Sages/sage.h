#pragma once

#include <thread>
#include <mutex>

#include <string>

class Sage
{
	std::string name;

	std::thread thread;

	static std::mutex mutex;

public:
	Sage(const std::string& name);

	void think();
	void eat();
};