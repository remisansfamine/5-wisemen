#include "time.h"

#include "table.hpp"

int main()
{
    srand(time(NULL));

    Table table;

    table.addAGuess(new Philosopher(&table, "Descartes", 1, 5, 2, 10));
    table.addAGuess(new Philosopher(&table, "Platon", 1, 5, 2, 10));
    table.addAGuess(new Philosopher(&table, "Voltaire", 1, 5, 2, 10));
    table.addAGuess(new Philosopher(&table, "Socrate", 1, 5, 2, 10));
    table.addAGuess(new Philosopher(&table, "Heraclite", 1, 5, 2, 10));

    table.dinner();

    return 0;
}