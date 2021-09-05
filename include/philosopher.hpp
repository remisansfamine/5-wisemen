#pragma once

#include <thread>
#include <mutex>
#include <atomic>

#include <vector>
#include <memory>
#include <string>

#include "message.hpp"
#include "speaker.hpp"

class Chopstick;

class Philosopher
{
private:
	std::thread thread;

	int timeToEat = 20;

	int minTimeToEat;
	int maxTimeToEat;
	int minTimeToThink;
	int maxTimeToThink;

	static int wisemanCount;

	int index = 0;

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
												   "se demande s'il ne devrait pas ramener ses propres baguettes",
												   "reflechi sur la trajectoire de Leonov" };

public:
	std::string name;

	bool hasFinished = false;

	Philosopher(Speaker& speaker, std::vector<std::unique_ptr<Chopstick>>& chopticks, const std::string& name, int minTimeToThink = 1, int maxTimeToThink = 5, int minTimeToEat = 2, int maxTimeToEat = 10);
	~Philosopher();

	void startTheMeal();

};