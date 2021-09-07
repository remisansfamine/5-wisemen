#include "utils.h"

#include <thread>
#include <random>
<<<<<<< HEAD
#include <thread>
=======
#include <time.h>
#include <iostream>
>>>>>>> 45270cf2da9cbc94239532d6ebd43be4581e5467

int randomFromRange(int min, int max)
{
    static std::mt19937 generator;
    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(generator);
}

int getColorCode(int foreground, int background)
{
	return foreground + background * 16;
}

<<<<<<< HEAD
void printWithDelay(const std::string& toPrint, int lastCharToPrint, int delay)
{
    int characterCount = lastCharToPrint <= 0 ? (unsigned int)toPrint.size() : (std::min)(lastCharToPrint, (int)toPrint.size());

    for (int i = 0; i < characterCount; i++)
    {
        std::cout << toPrint[i];
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

    std::cout << '\0';
=======
void printWithDelay(const std::string& toPrint, int delay)
{
    for (const char& c : toPrint)
    {
        std::cout << c;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
>>>>>>> 45270cf2da9cbc94239532d6ebd43be4581e5467
}