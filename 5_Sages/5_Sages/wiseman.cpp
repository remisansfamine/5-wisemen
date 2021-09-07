#include "wiseman.h"

#include "utils.h"
#include "chopstick.h"
#include "table.h"

int Wiseman::wisemanCount = 0;

int Wiseman::timeToEat;
int Wiseman::minTimeToEat;
int Wiseman::maxTimeToEat;
int Wiseman::minTimeToThink;
int Wiseman::maxTimeToThink;

int Wiseman::askValidInformation(Speaker& speaker, const std::string& question)
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

void Wiseman::askGlobalInformations(Speaker& speaker)
{
	speaker.narrate("Ce repas fut organise apres quelques jours de preparation, le temps de synchroniser les emplois du temps.\n");

	timeToEat = askValidInformation(speaker, "Ils s'etaient d'abord mis a mettre en place le temps de repas qu'un membre pouvait avoir (secondes): ");

	minTimeToThink = askValidInformation(speaker, "Ensuite sur le temps minimum qu'un membre pouvait prendre pour songer (secondes): ");
	maxTimeToThink = askValidInformation(speaker, "Ainsi qu'un temps maximum (secondes): ");

	speaker.narrate("Ils deciderent d'adopter la meme strategie pour le temps qu'un membre pouvait prendre pour manger.\n");
	minTimeToEat = askValidInformation(speaker, "D'abord sur le temps minimum (secondes): ");
	maxTimeToEat = askValidInformation(speaker, "Finalement sur le temps maximum (secondes): ");
}

Wiseman::Wiseman(Speaker& speaker, std::vector<std::unique_ptr<Chopstick>>& chopticks, const std::string& name)
	: speaker(speaker), chopticks(chopticks), name(name)
{
	index = wisemanCount;
	wisemanCount++;

	info = { name, index + 1 };

	chopticks.push_back(std::unique_ptr<Chopstick>(new Chopstick()));

	printAction("s'assoit a la table, il y a " + std::to_string(wisemanCount) + " baguette(s) a table.", 6, 3);
<<<<<<< HEAD
=======

>>>>>>> 45270cf2da9cbc94239532d6ebd43be4581e5467
}

Wiseman::~Wiseman()
{
	printAction("quitte la table.", 6, 3);

	thread.join();
}

void Wiseman::startTheMeal()
{
	thread = std::thread(&Wiseman::think, this);
}

<<<<<<< HEAD
std::string Wiseman::getName()
{
	return name;
}

bool Wiseman::hasFinished()
{
	return finished;
}

void Wiseman::think()
{
	int currentTimeToThink = randomFromRange(minTimeToThink, maxTimeToThink);

	std::string thinkingSentence = getRandomInRange(thinkingSentences, 0, (int)thinkingSentences.size());
	printAction(thinkingSentence + " pendant " + std::to_string(currentTimeToThink) + " secondes.", 3);
=======
void Wiseman::think()
{
	printAction("reflechi a la trajectoire de Leonov pendant " + std::to_string(currentTimeToThink) + " secondes.", 3);
>>>>>>> 45270cf2da9cbc94239532d6ebd43be4581e5467

	std::this_thread::sleep_for(std::chrono::seconds(currentTimeToThink));

	tryToEat();
}

void Wiseman::tryToEat()
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
<<<<<<< HEAD
		printAction("tente de manger mais n'a pas de baguette! Iel aimerait avoir les baguettes " + std::to_string(leftBaguetteIndex) + " et " + std::to_string(rightBaguetteIndex) + " qu'utilisent " + leftChopstick.getOwnerName() +  " et " + rightChopstick.getOwnerName() + ".", 4);
=======
		printAction("tente de manger mais n'a pas de baguette! " + std::to_string(leftBaguetteIndex) + " (" + leftChopstick.getOwnerName() + ")" + " et " + std::to_string(rightBaguetteIndex) + " (" + rightChopstick.getOwnerName() + ").", 4);
>>>>>>> 45270cf2da9cbc94239532d6ebd43be4581e5467
		think();
	}
	else if (baguetteCount == 1)
	{
<<<<<<< HEAD
		int neededChopstickIndex = leftChopstick.isTaken() ? leftBaguetteIndex : rightBaguetteIndex;

		printAction("tente de manger mais n'a qu'une seule pauvre baguette, iel lui manque la baguette " + std::to_string(neededChopstickIndex) + " qu'occupe " + chopticks[neededChopstickIndex]->getOwnerName() + ".", 4);
=======
		printAction("tente de manger mais n'a qu'une seule pauvre baguette " + std::to_string(leftBaguetteIndex) + " (" + leftChopstick.getOwnerName() + ")" + " et " + std::to_string(rightBaguetteIndex) + " (" + rightChopstick.getOwnerName() + ").", 4);
>>>>>>> 45270cf2da9cbc94239532d6ebd43be4581e5467
		think();
	}
	else
	{
<<<<<<< HEAD
		leftChopstick.setOwner(this);
		rightChopstick.setOwner(this);
=======
		leftChopstick.m_mutex->lock();
		rightChopstick.m_mutex->lock();

		leftChopstick.owner = rightChopstick.owner = this;
>>>>>>> 45270cf2da9cbc94239532d6ebd43be4581e5467

		leftChopstick.m_mutex->unlock();
		rightChopstick.m_mutex->unlock();

		eat();
	}
}

void Wiseman::printAction(const std::string& action, int foregroundColor, int backgroundColor, const std::time_t& time)
{
	speaker.sendMessage(info, action + '\n', foregroundColor, backgroundColor, time);
}

void Wiseman::eat()
{
	int leftBaguetteIndex = index;
	int rightBaguetteIndex = (index + 1) % wisemanCount;

	int currentTimeToEat = randomFromRange(minTimeToEat, maxTimeToEat);

<<<<<<< HEAD
	std::string eatingSentence = getRandomInRange(eatingSentences, 0, (int)eatingSentences.size());
	printAction(eatingSentence + " pendant " + std::to_string(currentTimeToEat) + " secondes en prenant les baguettes " + std::to_string(leftBaguetteIndex) + " et " + std::to_string(rightBaguetteIndex) + ".", 2);
=======
	printAction("est en train de manger un delicieux repas pendant " + std::to_string(currentTimeToEat) + " secondes en prenant les baguettes " + std::to_string(leftBaguetteIndex) + " et " + std::to_string(rightBaguetteIndex) + ".", 2);
>>>>>>> 45270cf2da9cbc94239532d6ebd43be4581e5467

	std::this_thread::sleep_for(std::chrono::seconds(currentTimeToEat));

	timeToEat -= currentTimeToEat;

	leftChopstick.m_mutex->lock();
	rightChopstick.m_mutex->lock();

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