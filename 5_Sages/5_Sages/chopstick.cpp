#include "chopstick.h"

bool Chopstick::isTaken()
{
	return owner;
}

std::string Chopstick::getOwnerName()
{
	return owner ? owner->name : "Personne";
}
