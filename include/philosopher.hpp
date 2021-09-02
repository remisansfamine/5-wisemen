#pragma once

#include <thread>
#include <mutex>

#include <string>

class Philosopher
{
	std::string name;

	std::thread thread;

	static std::mutex mutex;

public:
	Philosopher(const std::string& name);

	void think();
	void eat();
};