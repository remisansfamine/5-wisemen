#include "chopstick.h"

void Chopstick::setOwner(Wiseman* newOwner)
{
	m_mutex->lock();
	owner = newOwner;
	m_mutex->unlock();
}

bool Chopstick::isTaken()
{
	return owner;
}

std::string Chopstick::getOwnerName()
{
	return owner ? owner->name : "Personne";
}
