#include "wiseman.h"

#include "utils.h"
#include "chopstick.h"
#include "table.h"

int Wiseman::wisemanCount = 0;

Wiseman::Wiseman(Table* table, const std::string& name, int thinkTimeMin, int thinkTimeMax, int eatTimeMin, int eatTimeMax)
	: table(table), name(name)
{
	currentTimeToEat = randomFromRange(eatTimeMin, eatTimeMax);
	currentTimeToThink = randomFromRange(thinkTimeMin, thinkTimeMax);

	index = wisemanCount;
	wisemanCount++;

	info = { name, index + 1 };

	table->chopticks.push_back(std::unique_ptr<Chopstick>(new Chopstick()));

	printAction("s'assoit a la table, il y a " + std::to_string(wisemanCount) + " baguette(s) a table.", 6, 3);

	thread = std::thread(&Wiseman::think, this);
}

Wiseman::~Wiseman()
{
	printAction("quitte la table.", 6, 3);

	thread.join();
}

void Wiseman::think()
{
	printAction("reflechi au sens de la vie pendant " + std::to_string(currentTimeToThink) + " secondes.", 3);

	std::this_thread::sleep_for(std::chrono::seconds(currentTimeToThink));

	tryToEat();
}

void Wiseman::tryToEat()
{
	int baguetteCount = 0;

	int leftBaguetteIndex = index;
	int rightBaguetteIndex = (index + 1) % wisemanCount;

	Chopstick& leftChopstick = *table->chopticks[leftBaguetteIndex];
	Chopstick& rightChopstick = *table->chopticks[rightBaguetteIndex];

	if (!leftChopstick.isTaken())
		baguetteCount++;

	if (!rightChopstick.isTaken())
		baguetteCount++;

	if (baguetteCount == 0)
	{
		printAction("tente de manger mais n'a pas de baguette! " + std::to_string(leftBaguetteIndex) + " (" + leftChopstick.getOwner() + ")" + " et " + std::to_string(rightBaguetteIndex) + " (" + rightChopstick.getOwner() + ").", 4);
		think();
	}
	else if (baguetteCount == 1)
	{
		printAction("tente de manger mais n'a qu'une seule pauvre baguette " + std::to_string(leftBaguetteIndex) + " (" + leftChopstick.getOwner() + ")" + " et " + std::to_string(rightBaguetteIndex) + " (" + rightChopstick.getOwner() + ").", 4);
		think();
	}
	else
	{
		leftChopstick.owner = rightChopstick.owner = this;

		eat();
	}
}

void Wiseman::printAction(const std::string& action, int foregroundColor, int backgroundColor)
{
	table->speaker.sendMessage({ info, action + '\n', foregroundColor, backgroundColor });
}

void Wiseman::eat()
{
	int leftBaguetteIndex = index;
	int rightBaguetteIndex = (index + 1) % wisemanCount;

	Chopstick& leftChopstick = *table->chopticks[leftBaguetteIndex];
	Chopstick& rightChopstick = *table->chopticks[rightBaguetteIndex];

	leftChopstick.m_mutex->lock();
	rightChopstick.m_mutex->lock();

	printAction("est en train de manger un delicieux repas pendant " + std::to_string(currentTimeToEat) + " secondes en prenant les baguettes.", 2);

	std::this_thread::sleep_for(std::chrono::seconds(currentTimeToEat));

	timeToEat -= currentTimeToEat;

	printAction("repose les baguettes " + std::to_string(leftBaguetteIndex) + " et " + std::to_string(rightBaguetteIndex) + ".");

	leftChopstick.owner = rightChopstick.owner = nullptr;

	leftChopstick.m_mutex->unlock();
	rightChopstick.m_mutex->unlock();

	if (timeToEat <= 0)
	{
		hasFinished = true;
		printAction("a termine de manger.");
	}
	else
	{
		printAction("compte manger encore " + std::to_string(timeToEat) + "s.");
		think();
	}
}