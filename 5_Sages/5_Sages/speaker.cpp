#include "speaker.h"

#include "utils.h"
#include "time.h"

Speaker::Speaker()
    : info({ "HAL 9000", 1 }), castThread(&Speaker::castMessages, this)
{
    narrate("Bonjour, je suis HAL 9000. Vous vous trouvez a bord d'une reproduction de Leonov.\n");
    narrate("En 2010 se deroula dans ce vaiseau un repas rassemblant les plus grands scientifiques du XXIe siecle.\n");
    narrate("Ce repas se deroula autour de plats de ramen.\n");
    narrate("Malheureusement pour eux, David Bowman n'avait pas amene avec lui assez de baguettes lors de son voyage vers Jupiter en 2001.\n");
}

Speaker::~Speaker()
{
    castThread.join();
}

void Speaker::castMessages()
{
    castStart = std::chrono::system_clock::now();

    printWithDelay("+===================================================================================================\n");

    while (!mealIsOver)
    {
        std::lock_guard<std::mutex> lock(castMutex);

        while (!messages.empty())
        {
            Message& message = messages.front();

            message.display();

            messages.pop();
        }
    }

    printWithDelay("+===================================================================================================\n");
}

void Speaker::stopMeal()
{
    narrate("Ce dernier coup de baguette marqua la fin du repas, tout le monde se leva et vaqua.\n");

    auto now = std::chrono::system_clock::now();
    std::string timeAsString = std::to_string(std::chrono::duration_cast<std::chrono::minutes>(now - castStart).count());

    narrate("Cet representation holographique de " + timeAsString + " minutes fut inspire par la tetralogie d'Arthur C. Clarke: l'Odyssee de l'espace.\n");

    mealIsOver = true;
}

bool Speaker::isCastFinished()
{
    return messages.empty();
}

void Speaker::narrate(const std::string& action)
{
    sendMessage(info, { action });
}

void Speaker::sendMessage(const SenderInfo& sender, const std::string& action, int foregroundColor, int backgroundColor, const std::time_t& time)
{
    std::lock_guard<std::mutex> lock(castMutex);

    messages.push(Message(sender, action, foregroundColor, backgroundColor, time));
}