#include "chopstick.hpp"

void Chopstick::setOwner(Philosopher* newOwner)
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
	return owner ? owner->getName() : "Personne";
}
