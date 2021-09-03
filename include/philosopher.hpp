#pragma once

#include <thread>
#include <mutex>
#include <atomic>

#include <vector>
#include <memory>
#include <string>

#include "message.hpp"

class Table;

class Philosopher
{
	std::thread thread;

	int timeToEat = 60;

	int currentTimeToEat;
	int currentTimeToThink;

	static int wisemanCount;

	int index = 0;

	Table* table;

	SenderInfo info;

public:
	std::string name;

	bool hasFinished = false;

	Philosopher(Table* table, const std::string& name, int thinkTimeMin, int thinkTimeMax, int eatTimeMin, int eatTimeMax);
	~Philosopher();

	void think();
	void tryToEat();
	void eat();

	void printAction(const std::string& action, int foregroundColor = 15, int backgroundColor = 0);
};