#include "table.h"

#include <chrono>
#include <iostream>

void Table::init()
{
    Wiseman::askGlobalInformations(speaker);

    bool isValid = false;

    int wisemanCount = 0;
    while (!isValid)
    {
        speaker.narrate("A ce repas etait invite (nombre de participants): ");

        std::cin >> wisemanCount;

        isValid = wisemanCount > 1;
        if (!isValid)
            speaker.narrate("Ce repas avait etait organise pour avoir au minimum deux invites.\n");
    }


    speaker.narrate("Le premier invite etait: ");
    bool canLeave = false;
    do
    {
        std::string wisemanName;
        std::getline(std::cin >> std::ws, wisemanName);

        addAGuess(new Wiseman(speaker, chopticks, wisemanName));

        canLeave = wisemen.size() >= wisemanCount;

        if (!canLeave)
            speaker.narrate("Arriva ensuite: ");
    }
    while (!canLeave);
}

void Table::addAGuess(Wiseman* guess)
{
	wisemen.push_back(std::unique_ptr<Wiseman>(guess));
}

void Table::startDinner()
{
    speaker.narrate("Ce repas debuta par un temps de reflexion.\n");

    for (auto& wiseman : wisemen)
        wiseman->startTheMeal();

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