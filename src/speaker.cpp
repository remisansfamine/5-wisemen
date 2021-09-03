#include "speaker.hpp"

#include <iostream>

Speaker::Speaker()
{
    castThread = std::thread(&Speaker::castMessages, this);

    info = { "Antiphon", 1 };

    sendMessage({ info, "Bonjour, je m'appelle Antiphon, je vais vous narrer le deroulement d'un repas presque parfait.\n" });
}

Speaker::~Speaker()
{
    sendMessage({ info, "Ce dernier coup de baguette marqua la fin du repas, tout le monde se leva et vaqua." });

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
            std::cout << message.sender.name;

            SetConsoleTextAttribute(consoleHandler, getColorCode(message.foregroundColor, message.backgroundColor));
            std::cout << " " << message.action;

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