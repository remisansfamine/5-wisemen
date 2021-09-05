#include "utils.hpp"

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

int getClampedInput(bool& isValid, const std::function<void>& lambda, int min, int max)
{
    int wisemanCount = 0;
    isValid = false;
    while (!isValid)
    {
        std::cin >> wisemanCount;

        lambda;

        isValid = wisemanCount > min && wisemanCount < max;
    }

    return wisemanCount;
}

void printWithDelay(const std::string& toPrint, int delay)
{
    for (const char& c : toPrint)
    {
        std::cout << c;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}