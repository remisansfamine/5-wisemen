#include "message.h"

#include "utils.h"

HANDLE Message::consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);

Message::Message(const SenderInfo& sender, const std::string& action, int foregroundColor, int backgroundColor, const std::time_t& time)
	: sender(sender), action(action), sendingTime(time), foregroundColor(foregroundColor), backgroundColor(backgroundColor)
{

}

void Message::display()
{
    std::string timeAsString = getTimeAsString("%H:%M:%S", sendingTime);

    std::time_t delay = std::time(0) - sendingTime;
    std::string delayString = getTimeAsString("delay: %Ss", delay);

    printWithDelay("|    [" + timeAsString + " - " + delayString + "]  > ", 0);

    SetConsoleTextAttribute(consoleHandler, getColorCode(sender.textColor, 15));
    printWithDelay(sender.name);

    bool shouldRemoveLineReturn = *(action.end() - 1) == '\n';
    int indexOffset = shouldRemoveLineReturn ? -1 : 0;

    SetConsoleTextAttribute(consoleHandler, getColorCode(foregroundColor, backgroundColor));
    printWithDelay(" ");
    printWithDelay(action, (unsigned int)action.size() + indexOffset);

    SetConsoleTextAttribute(consoleHandler, getColorCode(15, 0));

    if (shouldRemoveLineReturn)
        printWithDelay("\n");
}
