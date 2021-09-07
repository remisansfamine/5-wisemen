#include "philosopher.hpp"

#include "utils.hpp"
#include "chopstick.hpp"
#include "table.hpp"

int Philosopher::wisemanCount = 0;

int Philosopher::timeToEat;
int Philosopher::minTimeToEat;
int Philosopher::maxTimeToEat;
int Philosopher::minTimeToThink;
int Philosopher::maxTimeToThink;

int Philosopher::askValidInformation(Speaker& speaker, const std::string& question)
{
	speaker.narrate(question);

	int result;

	bool isValid = false;
	while (!isValid)
	{
		std::cin >> result;

		isValid = result > 0;

		if (!isValid)
			speaker.narrate("ERR##OR - V3UIL*LEZ REESS$AYER\n");
	}

	return result;
}

void Philosopher::askGlobalInformations(Speaker& speaker)
{
	speaker.narrate("Ce repas fut organise apres quelques jours de preparation, le temps de synchroniser les emplois du temps.\n");

	timeToEat = askValidInformation(speaker, "Ils s'etaient d'abord mis a mettre en place le temps de repas qu'un membre pouvait avoir (secondes): ");

	minTimeToThink = askValidInformation(speaker, "Ensuite sur le temps minimum qu'un membre pouvait prendre pour songer (secondes): ");
	maxTimeToThink = askValidInformation(speaker, "Ainsi qu'un temps maximum (secondes): ");

	speaker.narrate("Ils deciderent d'adopter la meme strategie pour le temps qu'un membre pouvait prendre pour manger.\n");
	minTimeToEat = askValidInformation(speaker, "D'abord sur le temps minimum (secondes): ");
	maxTimeToEat = askValidInformation(speaker, "Finalement sur le temps maximum (secondes): ");
}

Philosopher::Philosopher(Speaker& speaker, std::vector<std::unique_ptr<Chopstick>>& chopticks, const std::string& name)
	: speaker(speaker), chopticks(chopticks), name(name)
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

std::string Philosopher::getName()
{
	return name;
}

bool Philosopher::hasFinished()
{
	return finished;
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
		printAction("tente de manger mais n'a pas de baguette! Iel aimerait avoir les baguettes " + std::to_string(leftBaguetteIndex) + " et " + std::to_string(rightBaguetteIndex) + " qu'utilisent " + leftChopstick.getOwnerName() +  " et " + rightChopstick.getOwnerName() + ".", 4);
		think();
	}
	else if (baguetteCount == 1)
	{
		int neededChopstickIndex = leftChopstick.isTaken() ? leftBaguetteIndex : rightBaguetteIndex;

		printAction("tente de manger mais n'a qu'une seule pauvre baguette, iel lui manque la baguette " + std::to_string(neededChopstickIndex) + " qu'occupe " + chopticks[neededChopstickIndex]->getOwnerName() + ".", 4);
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

	int currentTimeToEat = randomFromRange(minTimeToEat, maxTimeToEat);

	std::string eatingSentence = getRandomInRange(eatingSentences, 0, (int)eatingSentences.size());
	printAction(eatingSentence + " pendant " + std::to_string(currentTimeToEat) + " secondes en prenant les baguettes " + std::to_string(leftBaguetteIndex) + " et " + std::to_string(rightBaguetteIndex) + ".", 2);

	std::this_thread::sleep_for(std::chrono::seconds(currentTimeToEat));

	timeToEat -= currentTimeToEat;

	printAction("repose les baguettes " + std::to_string(leftBaguetteIndex) + " et " + std::to_string(rightBaguetteIndex) + ".");

	chopticks[leftBaguetteIndex]->setOwner(nullptr);
	chopticks[rightBaguetteIndex]->setOwner(nullptr);

	if (timeToEat <= 0)
	{
		finished = true;
		printAction("a termine de manger.");
	}
	else
	{
		printAction("compte manger encore " + std::to_string(timeToEat) + " secondes.");
		think();
	}
}