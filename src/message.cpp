#include "message.hpp"

#include "utils.hpp"

HANDLE Message::consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);

Message::Message(const SenderInfo& sender, const std::string& action, int foregroundColor, int backgroundColor, const std::time_t& time)
	: sender(sender), action(action), timeAsString(getTimeAsString("H:%H - M:%M - S:%S", time)), foregroundColor(foregroundColor), backgroundColor(backgroundColor)
{

}

void Message::display()
{
    consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);

    printWithDelay("|    [" + timeAsString + "]  > ", 0);

    SetConsoleTextAttribute(consoleHandler, getColorCode(sender.textColor, 15));
    printWithDelay(sender.name);

    SetConsoleTextAttribute(consoleHandler, getColorCode(foregroundColor, backgroundColor));
    printWithDelay(" " + action);

    SetConsoleTextAttribute(consoleHandler, getColorCode(15, 0));
}
