#include "utils.h"

#include <random>
#include <thread>

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

void printWithDelay(const std::string& toPrint, int lastCharToPrint, int delay)
{
    int characterCount = lastCharToPrint <= 0 ? (unsigned int)toPrint.size() : (std::min)(lastCharToPrint, (int)toPrint.size());

    for (int i = 0; i < characterCount; i++)
    {
        std::cout << toPrint[i];
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

    std::cout << '\0';
}