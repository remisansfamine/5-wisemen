#include "table.h"

#include <chrono>
#include <iostream>

void Table::init()
{
<<<<<<< HEAD
    Wiseman::askGlobalInformations(speaker);
=======
    speaker.sendMessage({ {"HAL 9000", 1}, "Ce repas fut organise apres quelques jours de preparation, le temps de synchroniser les emplois du temps.\n" });
>>>>>>> 45270cf2da9cbc94239532d6ebd43be4581e5467

    bool isValid = false;

    int wisemanCount = 0;
    while (!isValid)
    {
<<<<<<< HEAD
        speaker.narrate("A ce repas etait invite (nombre de participants): ");
=======
        speaker.sendMessage({ {"HAL 9000", 1}, "A ce repas etait invite (nombre de participants): " });
>>>>>>> 45270cf2da9cbc94239532d6ebd43be4581e5467

        std::cin >> wisemanCount;

        isValid = wisemanCount > 1;
        if (!isValid)
<<<<<<< HEAD
            speaker.narrate("Ce repas avait etait organise pour avoir au minimum deux invites.\n");
    }


    speaker.narrate("Le premier invite etait: ");
    bool canLeave = false;
=======
            speaker.sendMessage({ {"HAL 9000", 1}, "Ce repas avait etait organise pour avoir au minimum deux invites.\n" });
    }

    speaker.sendMessage({ {"HAL 9000", 1}, "Le premier invite etait: " });

    bool canLeave = false;

>>>>>>> 45270cf2da9cbc94239532d6ebd43be4581e5467
    do
    {
        std::string wisemanName;
        std::getline(std::cin >> std::ws, wisemanName);

<<<<<<< HEAD
        addAGuess(new Wiseman(speaker, chopticks, wisemanName));
=======
        addAGuess(new Wiseman(this, wisemanName));
>>>>>>> 45270cf2da9cbc94239532d6ebd43be4581e5467

        canLeave = wisemen.size() >= wisemanCount;

        if (!canLeave)
<<<<<<< HEAD
            speaker.narrate("Arriva ensuite: ");
=======
            speaker.sendMessage({ {"HAL 9000", 1 }, "Arriva ensuite: " });
>>>>>>> 45270cf2da9cbc94239532d6ebd43be4581e5467
    }
    while (!canLeave);
}

void Table::addAGuess(Wiseman* guess)
{
	wisemen.push_back(std::unique_ptr<Wiseman>(guess));
}

void Table::startDinner()
{
<<<<<<< HEAD
    speaker.narrate("Ce repas debuta par un temps de reflexion.\n");
=======
    speaker.sendMessage({ {"HAL 9000"}, "Ce repas debuta par un temps de reflexion.\n" });
>>>>>>> 45270cf2da9cbc94239532d6ebd43be4581e5467

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