#include "table.hpp"

#include <chrono>
#include <iostream>

void Table::init()
{
    Philosopher::askGlobalInformations(speaker);

    bool isValid = false;

    // Get the wiseman count

    int wisemanCount = 0;
    while (!isValid)
    {
        speaker.narrate("A ce repas etait invite (nombre de participants): ");

        std::cin >> wisemanCount;

        isValid = wisemanCount > 1;
        if (!isValid)
            speaker.narrate("Ce repas avait etait organise pour avoir au minimum deux invites.\n");
    }

    // Get all the wisemen name

    speaker.narrate("Le premier invite etait: ");
    bool canLeave = false;
    do
    {
        // Get the name
        std::string wisemanName;
        std::getline(std::cin >> std::ws, wisemanName);

        // Add a wiseman
        addAGuess(new Philosopher(speaker, chopticks, wisemanName));

        canLeave = wisemen.size() >= wisemanCount;

        if (!canLeave)
            speaker.narrate("Arriva ensuite: ");
    }
    while (!canLeave);
}

void Table::addAGuess(Philosopher* guess)
{
	wisemen.push_back(std::unique_ptr<Philosopher>(guess));
}

void Table::startDinner()
{
    speaker.narrate("Ce repas debuta par un temps de reflexion.\n");

    for (auto& wiseman : wisemen)
        wiseman->startTheMeal();

    // Update the wisemen, to avoid infinite loop

    while (!wisemen.empty())
    {
        for (auto wisemanIt = wisemen.begin(); wisemanIt != wisemen.end(); )
        {
            if (wisemanIt->get()->hasFinished())
                wisemanIt = wisemen.erase(wisemanIt);
            else
                wisemanIt++;
        }
    }

    bool canCloseTheDinner = false;
    while (!canCloseTheDinner)
    {
        speaker.stopMeal();

        canCloseTheDinner = speaker.isCastFinished();
    }
}