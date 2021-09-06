#include "time.h"

#include "table.h"

int main()
{
    srand((unsigned int)time(nullptr));

    Table table;

    table.init();

    table.startDinner();

    return 0;
}