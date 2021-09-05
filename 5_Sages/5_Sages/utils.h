#pragma once

#include <string>

int randomFromRange(int min, int max);

int getColorCode(int foreground, int background);

void printWithDelay(const std::string& toPrint, int delay = 10);