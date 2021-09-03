#include "table.hpp"

#include <chrono>

void Table::addAGuess(Philosopher* guess)
{
	wisemen.push_back(std::unique_ptr<Philosopher>(guess));
}

void Table::dinner()
{
    while (!wisemen.empty())
    {
        for (auto wisemanIt = wisemen.begin(); wisemanIt != wisemen.end(); )
        {
            if (wisemanIt->get()->hasFinished)
                wisemanIt = wisemen.erase(wisemanIt);
            else
                wisemanIt++;
        }
    }

    speaker.mealIsOver = true;
}