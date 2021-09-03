#include "chopstick.hpp"

bool Chopstick::isTaken()
{
	return owner;
}

std::string Chopstick::getOwner()
{
	return owner ? owner->name : "Nobody";
}
