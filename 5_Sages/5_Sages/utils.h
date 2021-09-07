#pragma once

#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iomanip>
#include <iostream>

int randomFromRange(int min, int max);

int getColorCode(int foreground, int background);

void printWithDelay(const std::string& toPrint, int lastCharToPrint = 0, int delay = 3);

template <typename T>
T getRandomInRange(const std::vector<T> vec, int minimum, int maximum)
{
	minimum = (std::max)(minimum, 0);
	maximum = (std::min)(maximum, (int)vec.size() - 1);

	return vec[randomFromRange(minimum, maximum)];
}

template <int I = 26>
std::string getTimeAsString(const std::string& format, std::time_t currentTime = std::time(0))
{
	char timeString[I];
	struct tm tstruct;
	localtime_s(&tstruct, &currentTime);
	strftime(timeString, sizeof(timeString), format.c_str(), &tstruct);

    return std::string(timeString);
}