#include "chopstick.h"

bool Chopstick::isTaken()
{
	return owner;
}

std::string Chopstick::getOwner()
{
	return owner ? owner->name : "Personne";
}
