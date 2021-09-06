#include "philosopher.hpp"

#include "utils.hpp"
#include "chopstick.hpp"
#include "table.hpp"

int Philosopher::wisemanCount = 0;

Philosopher::Philosopher(Speaker& speaker, std::vector<std::unique_ptr<Chopstick>>& chopticks, const std::string& name, int minTimeToThink, int maxTimeToThink, int minTimeToEat, int maxTimeToEat)
	: speaker(speaker), chopticks(chopticks), name(name), minTimeToThink(minTimeToThink), maxTimeToThink(maxTimeToThink), minTimeToEat(minTimeToEat), maxTimeToEat(maxTimeToEat)
{
	index = wisemanCount;
	wisemanCount++;

	info = { name, index + 1 };

	chopticks.push_back(std::unique_ptr<Chopstick>(new Chopstick()));

	printAction("s'assoit a la table, il y a " + std::to_string(wisemanCount) + " baguette(s) a table.", 6, 3);
}

Philosopher::~Philosopher()
{
	printAction("quitte la table.", 6, 3);

	thread.join();
}

void Philosopher::startTheMeal()
{
	thread = std::thread(&Philosopher::think, this);
}

void Philosopher::think()
{
	int currentTimeToThink = randomFromRange(minTimeToThink, maxTimeToThink);

	std::string thinkingSentence = getRandomInRange(thinkingSentences, 0, (int)thinkingSentences.size());
	printAction(thinkingSentence + " pendant " + std::to_string(currentTimeToThink) + " secondes.", 3);

	std::this_thread::sleep_for(std::chrono::seconds(currentTimeToThink));

	tryToEat();
}

void Philosopher::tryToEat()
{
	int baguetteCount = 0;

	int leftBaguetteIndex = index;
	int rightBaguetteIndex = (index + 1) % wisemanCount;

	Chopstick& leftChopstick = *chopticks[leftBaguetteIndex];
	Chopstick& rightChopstick = *chopticks[rightBaguetteIndex];

	if (!leftChopstick.isTaken())
		baguetteCount++;

	if (!rightChopstick.isTaken())
		baguetteCount++;

	if (baguetteCount == 0)
	{
		printAction("tente de manger mais n'a pas de baguette! " + std::to_string(leftBaguetteIndex) + " (" + leftChopstick.getOwnerName() + ")" + " et " + std::to_string(rightBaguetteIndex) + " (" + rightChopstick.getOwnerName() + ").", 4);
		think();
	}
	else if (baguetteCount == 1)
	{
		printAction("tente de manger mais n'a qu'une seule pauvre baguette " + std::to_string(leftBaguetteIndex) + " (" + leftChopstick.getOwnerName() + ")" + " et " + std::to_string(rightBaguetteIndex) + " (" + rightChopstick.getOwnerName() + ").", 4);
		think();
	}
	else
	{
		leftChopstick.setOwner(this);
		rightChopstick.setOwner(this);

		eat();
	}
}

void Philosopher::printAction(const std::string& action, int foregroundColor, int backgroundColor, const std::time_t& time)
{
	speaker.sendMessage(info, action + '\n', foregroundColor, backgroundColor, time);
}

void Philosopher::eat()
{
	int leftBaguetteIndex = index;
	int rightBaguetteIndex = (index + 1) % wisemanCount;

	Chopstick& leftChopstick = *chopticks[leftBaguetteIndex];
	Chopstick& rightChopstick = *chopticks[rightBaguetteIndex];

	int currentTimeToEat = randomFromRange(minTimeToEat, maxTimeToEat);

	std::string eatingSentence = getRandomInRange(eatingSentences, 0, (int)eatingSentences.size());
	printAction(eatingSentence + " pendant " + std::to_string(currentTimeToEat) + " secondes en prenant les baguettes " + std::to_string(leftBaguetteIndex) + " et " + std::to_string(rightBaguetteIndex) + ".", 2);

	std::this_thread::sleep_for(std::chrono::seconds(currentTimeToEat));

	timeToEat -= currentTimeToEat;

	printAction("repose les baguettes " + std::to_string(leftBaguetteIndex) + " et " + std::to_string(rightBaguetteIndex) + ".");

	leftChopstick.setOwner(nullptr);
	rightChopstick.setOwner(nullptr);

	if (timeToEat <= 0)
	{
		hasFinished = true;
		printAction("a termine de manger.");
	}
	else
	{
		printAction("compte manger encore " + std::to_string(timeToEat) + " secondes.");
		think();
	}
}