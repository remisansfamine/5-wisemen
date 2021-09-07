#pragma once

#include <thread>
#include <mutex>

#include <vector>
#include <memory>
#include <string>

#include "message.hpp"
#include "speaker.hpp"

class Chopstick;

class Philosopher
{
private:
	int index = 0;

	std::thread thread;

	Speaker& speaker;

	SenderInfo info;

	std::vector<std::unique_ptr<Chopstick>>& chopticks;

	void think();
	void tryToEat();
	void eat();

	void printAction(const std::string& action, int foregroundColor = 15, int backgroundColor = 0, const std::time_t& time = std::time(0));

	std::vector<std::string> eatingSentences = { "s'apprete a manger un delicieux ramen",
												 "est sur le point de savourer un plat oncuteux",
												 "est pret a deguster",
												 "va manger le meilleur repas de sa vie" };

	std::vector<std::string> thinkingSentences = { "se demande si le monolith est reellement de nature extraterrestre",
												   "se questionne sur ce que pouvait bien faire Bowman avant ses repas",
												   "se demande si iel ne devrait pas ramener ses propres baguettes",
												   "reflechi sur la trajectoire de Leonov" };

	std::string name;
	bool finished = false;

	static int timeToEat;
	static int minTimeToEat;
	static int maxTimeToEat;
	static int minTimeToThink;
	static int maxTimeToThink;
	static int wisemanCount;

	static int askValidInformation(Speaker& speaker, const std::string& question);

public:
	Philosopher(Speaker& speaker, std::vector<std::unique_ptr<Chopstick>>& chopticks, const std::string& name);
	~Philosopher();

	void startTheMeal();

	std::string getName();

	bool hasFinished();

	static void askGlobalInformations(Speaker& speaker);
};