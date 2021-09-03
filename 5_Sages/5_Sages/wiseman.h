#pragma once

#include <thread>
#include <mutex>
#include <atomic>

#include <vector>
#include <memory>
#include <string>

#include "message.h"

class Table;

class Wiseman
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

	Wiseman(Table* table, const std::string& name, int thinkTimeMin, int thinkTimeMax, int eatTimeMin, int eatTimeMax);
	~Wiseman();

	void think();
	void tryToEat();
	void eat();

	void printAction(const std::string& action, int foregroundColor = 15, int backgroundColor = 0);
};