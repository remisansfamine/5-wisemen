#include "speaker.hpp"

#include "time.h"

#include "utils.hpp"

Speaker::Speaker()
    : info({ "HAL 9000", 1 }), castThread(&Speaker::castMessages, this)
{
    // Display the speaker informations
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

    // Display the cast initialisation informations

    printWithDelay("\n\n * Cette representation holographique a besoin d'informations entrees manuellement pour pouvoir fonctionner.\n");
    printWithDelay("   Pour les prochaines informations demandees, veuillez entrer des valeurs numeriques non-nulles.\n");

    printWithDelay("\n\n * Pour une meilleure experience utilisateur: veuillez vous mettre en plein-ecran.\n\n");
    printWithDelay("----------------------------------------------------------------------------------------------------\n");
    printWithDelay("\nOuverture de l'archive...\n", 64, 100);
    printWithDelay("\nAcces donnees HAL 9000...\n", 64, 100);
    printWithDelay("\nHAL 9000 - Initialisation...\n", 64, 100);
    printWithDelay("\nDemande d'acces aux inputs en cours...\n", 64, 100);
    printWithDelay("\nDemarrage des systemes neronaux...\n\n", 64, 100);
    printWithDelay("----------------------------------------------------------------------------------------------------\n\n");

    printWithDelay("+===================================================================================================\n|\n");

    // Display all informations while the meal is not finished
    while (!isCastFinished())
    {
        std::lock_guard<std::mutex> lock(castMutex);

        // While the queue is not empty, use it and pop it
        while (!messages.empty())
        {
            Message& message = messages.front();

            message.display();

            // Pop the current message
            messages.pop();
        }
    }
    printWithDelay("|\n+===================================================================================================\n");
}

void Speaker::stopMeal()
{
    if (mealIsOver)
        return;

    // Display the meal ending informations

    narrate("Ce dernier coup de baguette marqua la fin du repas, tout le monde se leva et vaqua.\n");

    auto now = std::chrono::system_clock::now();
    std::string timeAsString = std::to_string(std::chrono::duration_cast<std::chrono::minutes>(now - castStart).count());

    narrate("Cet representation holographique de " + timeAsString + " minutes fut inspire par la tetralogie d'Arthur C. Clarke: l'Odyssee de l'espace.\n");
    narrate("A l'occasion de son 227ieme anniversaire.\n");

    mealIsOver = true;
}

bool Speaker::isCastFinished()
{
    return messages.empty() && mealIsOver;
}

void Speaker::narrate(const std::string& action)
{
    sendMessage(info, action);
}

void Speaker::sendMessage(const SenderInfo& sender, const std::string& action, int foregroundColor, int backgroundColor, const std::time_t& time)
{
    std::lock_guard<std::mutex> lock(castMutex);

    messages.push(Message(sender, action, foregroundColor, backgroundColor, time));
}