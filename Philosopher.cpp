#include "Philosopher.h"
#include "Chopstick.h"
#include "Food.h"

Philosopher::Philosopher(const TextureHolder<std::string> &th, int id, Food* food, int philAm)
	:mSprite(th.get("Philosopher"))
	, mId(id)
	, mFood(food)
	, philAmount(philAm)
	, lastState(THINKING)
{
	this->setOrigin(mSprite.getLocalBounds().height / 2, mSprite.getLocalBounds().width / 2);
}

void Philosopher::philosopher(int maxRuns)
{
	while (totalRuns < maxRuns)
	{
		// TODO: Add randomness to sleep function
		std::this_thread::sleep_for(std::chrono::seconds(2));	/* philosopher is thinking */
		takeForks();											/* aquire two chopsticks or block */
		std::this_thread::sleep_for(std::chrono::seconds(3));	/* yum-yum, spaghetti */
		putForks();												/* put chopsticks back on table */
	}
	return;
}

void Philosopher::takeForks()
{
	bool gotForks = false;
	std::unique_lock<std::mutex> lock(diningMtx);					/* enter critical region */
	state[mId] = HUNGRY;
	std::cout << "Philosopher " << mId << " is now hungry\n";
	gotForks = test();

	while (!gotForks)
	{
		cv.wait(lock);			/* sleep until someone has finished eating */
		gotForks = test();		/* see if chopsticks are available */
	}

	lock.unlock();				/* exit critical region */
}

void Philosopher::putForks()
{
	std::unique_lock<std::mutex> lock(diningMtx);				/* enter critical region */
	state[mId] = THINKING;									/* philosopher has finished eating */
	std::cout << "Philosopher " << mId << " is now thinking\n";
	totalRuns++;
	cv.notify_all();		/* notify philosophers waiting, and exit critical region */
}

bool Philosopher::test()
{
	if (state[mId] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
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
			(!chopsticks[LEFT]->isAvailable() || !chopsticks[mId]->isAvailable()))
			return;

		/* Update philosopher's state */
		lastState = state[mId];

		switch (lastState)
		{
		case EATING:
			chopsticks[LEFT]->moveTowards(mFood, 100);
			chopsticks[mId]->moveTowards(mFood, 100);
			break;
		case THINKING:
			chopsticks[LEFT]->resetPos(100);
			chopsticks[mId]->resetPos(100);
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