#include "time.h"

#include "table.hpp"

int main()
{
    srand((unsigned int)time(nullptr));

    Table table;

    table.init();

    table.startDinner();

    return 0;
}