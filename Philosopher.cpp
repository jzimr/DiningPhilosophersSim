#include "Philosopher.h"
#include "Chopstick.h"
#include "Food.h"

Philosopher::Philosopher(const TextureHolder<std::string> &th, int id, Food* food, int philAm)
	:mSprite(th.get("PhilThinking"))
	, mId(id)
	, mFood(food)
	, philAmount(philAm)
	, lastState(THINKING)
	, mth{ th }
{
	this->setOrigin(mSprite.getLocalBounds().height / 2, mSprite.getLocalBounds().width / 2);
}

void Philosopher::philosopher(int maxRuns)
{
	while (totalRuns < maxRuns)
	{
		// TODO: Add randomness to sleep function
		std::this_thread::sleep_for(std::chrono::seconds(3));	/* philosopher is thinking */
		takeChopsticks();											/* aquire two chopsticks or block */
		std::this_thread::sleep_for(std::chrono::seconds(4));	/* yum-yum, spaghetti */
		putChopsticks();												/* put chopsticks back on table */
	}
	return;
}

void Philosopher::takeChopsticks()
{
	std::unique_lock<std::mutex> lock(diningMtx);					/* enter critical region */
	state[mId] = HUNGRY;
	std::cout << "Philosopher " << mId << " is now hungry\n";

	while (!test())				/* loop until chopsticks are available for grab */
		cv.wait(lock);			/* sleep until someone has finished eating */

	lock.unlock();				/* exit critical region */
}

void Philosopher::putChopsticks()
{
	std::unique_lock<std::mutex> lock(diningMtx);				/* enter critical region */
	state[mId] = THINKING;									/* philosopher has finished eating */
	std::cout << "Philosopher " << mId << " is now thinking\n";
	totalRuns++;
	cv.notify_all();		/* notify philosophers waiting, and exit critical region */
}

bool Philosopher::test()
{
	if (state[mId] == HUNGRY && state[P_LEFT] != EATING && state[P_RIGHT] != EATING)
	{
		state[mId] = EATING;
		std::cout << "Philosopher " << mId << " is now eating\n";
		return true;
	}
	return false;
}

void Philosopher::updateCurrent(float dt)
{
	if (lastState != state[mId])	/* If state of philosopher has changed since last check */
	{
		/* Check first if neighboring chopsticks are available (Fixes a god damn bug that has kept me in agony for days) */
		if (lastState == HUNGRY &&
			(!chopsticks[P_LEFT]->isAvailable() || !chopsticks[mId]->isAvailable()))
			return;

		/* Update philosopher's state */
		lastState = state[mId];

		switch (lastState)
		{
		case EATING:
			mSprite.setTexture(mth.get("PhilEating"));
			chopsticks[P_LEFT]->moveTowards(mFood, 100);
			chopsticks[mId]->moveTowards(mFood, 100);
			break;
		case THINKING:
			mSprite.setTexture(mth.get("PhilThinking"));
			chopsticks[P_LEFT]->resetPos(100);
			chopsticks[mId]->resetPos(100);
			break;
		case HUNGRY:
			mSprite.setTexture(mth.get("PhilHungry"));
			break;
		}
	}
}

void Philosopher::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

/* Initialize static members of class */
std::vector<Chopstick*> Philosopher::chopsticks;
int Philosopher::totalRuns = 0;
std::vector<int> Philosopher::state;
std::mutex Philosopher::diningMtx;
std::condition_variable Philosopher::cv;