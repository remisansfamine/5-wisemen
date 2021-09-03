#include "time.h"

#include "table.h"

int main()
{
    srand(time(NULL));

    Table table;

    table.addAGuess(new Wiseman(&table, "Descartes", 1, 5, 2, 10));
    table.addAGuess(new Wiseman(&table, "Platon", 1, 5, 2, 10));
    table.addAGuess(new Wiseman(&table, "Voltaire", 1, 5, 2, 10));
    table.addAGuess(new Wiseman(&table, "Socrate", 1, 5, 2, 10));
    table.addAGuess(new Wiseman(&table, "Heraclite", 1, 5, 2, 10));

    table.dinner();

    return 0;
}