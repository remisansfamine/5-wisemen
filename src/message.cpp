#include "message.hpp"

#include "utils.hpp"

HANDLE Message::consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);

Message::Message(const SenderInfo& sender, const std::string& action, int foregroundColor, int backgroundColor, const std::time_t& time)
	: sender(sender), action(action), sendingTime(time), foregroundColor(foregroundColor), backgroundColor(backgroundColor)
{

}

void Message::display()
{
    // Get the sending time (when the message was sent) as a string to print it
    std::string timeAsString = getTimeAsString("%H:%M:%S", sendingTime);

    // Get the delay between the sending and now
    std::time_t delay = std::time(0) - sendingTime;
    std::string delayString = getTimeAsString("delay: %Ss", delay);

    // Display the hour and the delay
    printWithDelay("|    [" + timeAsString + " - " + delayString + "]  > ", 0);

    // Display the author
    SetConsoleTextAttribute(consoleHandler, getColorCode(sender.textColor, 15));
    printWithDelay(sender.name);

    bool shouldRemoveLineReturn = *(action.end() - 1) == '\n';
    int indexOffset = shouldRemoveLineReturn ? -1 : 0;

    // Display the action minus the line return
    SetConsoleTextAttribute(consoleHandler, getColorCode(foregroundColor, backgroundColor));
    printWithDelay(" ");
    printWithDelay(action, (unsigned int)action.size() + indexOffset);

    // Remove all color info to make a good line return
    SetConsoleTextAttribute(consoleHandler, getColorCode(15, 0));

    // Add the line return if there was one
    if (shouldRemoveLineReturn)
        printWithDelay("\n");
}
