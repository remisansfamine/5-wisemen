#include "utils.h"

#include <thread>
#include <random>
#include <time.h>
#include <iostream>

int randomFromRange(int min, int max)
{
	return min + std::rand() % (max - min + 1);
}

int getColorCode(int foreground, int background)
{
	return foreground + background * 16;
}

void printWithDelay(const std::string& toPrint, int delay)
{
    for (const char& c : toPrint)
    {
        std::cout << c;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}