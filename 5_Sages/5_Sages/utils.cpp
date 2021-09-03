#include "utils.h"

#include <random>
#include <time.h>

int randomFromRange(int min, int max)
{
	return min + std::rand() % (max - min + 1);
}

int getColorCode(int foreground, int background)
{
	return foreground + background * 16;
}