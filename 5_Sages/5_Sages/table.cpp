#include "table.h"

#include <chrono>
#include <iostream>

void Table::init()
{
    speaker.sendMessage({ {"HAL 9000", 1}, "Ce repas fut organise apres quelques jours de preparation, le temps de synchroniser les emplois du temps.\n" });

    bool isValid = false;

    int wisemanCount = 0;
    while (!isValid)
    {
        speaker.sendMessage({ {"HAL 9000", 1}, "A ce repas etait invite (nombre de participants): " });

        std::cin >> wisemanCount;

        isValid = wisemanCount > 1;
        if (!isValid)
            speaker.sendMessage({ {"HAL 9000", 1}, "Ce repas avait etait organise pour avoir au minimum deux invites.\n" });
    }

    speaker.sendMessage({ {"HAL 9000", 1}, "Le premier invite etait: " });

    bool canLeave = false;

    do
    {
        std::string wisemanName;
        std::getline(std::cin >> std::ws, wisemanName);

        addAGuess(new Wiseman(this, wisemanName));

        canLeave = wisemen.size() >= wisemanCount;

        if (!canLeave)
            speaker.sendMessage({ {"HAL 9000", 1 }, "Arriva ensuite: " });
    }
    while (!canLeave);
}

void Table::addAGuess(Wiseman* guess)
{
	wisemen.push_back(std::unique_ptr<Wiseman>(guess));
}

void Table::startDinner()
{
    speaker.sendMessage({ {"HAL 9000"}, "Ce repas debuta par un temps de reflexion.\n" });

    for (auto& wiseman : wisemen)
        wiseman->startTheMeal();

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