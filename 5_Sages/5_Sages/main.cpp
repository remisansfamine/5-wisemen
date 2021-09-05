#include "time.h"

#include "table.h"

int main()
{
    srand(time(NULL));

    Table table;

    table.init();

    table.startDinner();

    return 0;
}