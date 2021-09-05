#include "speaker.h"

#include "utils.h"

Speaker::Speaker()
{
    castThread = std::thread(&Speaker::castMessages, this);

    info = { "HAL 9000", 1 };

    sendMessage({ info, "Bonjour, je suis HAL 9000. Vous vous trouvez a bord d'une reproduction de Leonov.\n" });
    sendMessage({ info, "En 2010 se deroula dans ce vaiseau un repas rassemblant les plus grands scientifiques du XXIe siecle.\n" });
    sendMessage({ info, "Ce repas ce deroula autour de plats de ramen.\n" });
    sendMessage({ info, "Malheureusement pour eux, David Bowman n'avait pas amene avec lui assez de baguettes lors de son voyage vers Jupiter en 2001.\n" });
}

Speaker::~Speaker()
{
    sendMessage({ info, "Ce dernier coup de baguette marqua la fin du repas, tout le monde se leva et vaqua." });
    sendMessage({ info, "Cet representation d'hologramme fut inspire par la tetralogie d'Arthur C. Clarke: l'Odyssee de l'espace." });

    castThread.join();
    mealIsOver = true;
}

void Speaker::castMessages()
{
    while (!mealIsOver)
    {
        while (!messages.empty())
        {
            std::lock_guard<std::mutex> lock(castMutex);

            Message& message = messages.front();

            SetConsoleTextAttribute(consoleHandler, getColorCode(message.sender.textColor, 15));
            printWithDelay(message.sender.name);

            SetConsoleTextAttribute(consoleHandler, getColorCode(message.foregroundColor, message.backgroundColor));
            printWithDelay(" " + message.action);

            SetConsoleTextAttribute(consoleHandler, getColorCode(15, 0));

            messages.pop();
        }
    }
}

void Speaker::sendMessage(const Message& message)
{
    std::lock_guard<std::mutex> lock(castMutex);

    messages.push(message);
}