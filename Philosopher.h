#pragma once
#include "Entity.h"
#include "TextureHolder.h"
#include <iostream>
#include <mutex>
#include <thread>	// TODO: LINUX support for Sleep()
#include <chrono>
#include <cstdlib>
#include <condition_variable>
class Chopstick;
class Food;	

#define LEFT		(mId+philAmount-1)%philAmount		/* ID of mId's left neighbor */
#define RIGHT		(mId+1)%philAmount					/* ID of mId's right neighbor */
#define THINKING	0									/* philosopher is thinking */
#define	HUNGRY		1									/* philosopher is hungry */
#define EATING		2									/* philosopher is eating */

class Philosopher : public Entity
{
public:
	explicit					Philosopher(const TextureHolder<std::string> &th, int id, Food* food, int philAm);
	
	void						philosopher(int maxRuns);

private:
	void						takeForks();
	void						putForks();
	bool						test();


private:
	void						updateCurrent(sf::Time dt);
	void						drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	static std::vector<Chopstick*> chopsticks;	/* Bad practice, but fuck it. */
	static std::vector<int> state;

private:
	sf::Sprite mSprite;		// TODO!! Mutex on this variable
	mutable std::mutex spriteMtx;	// Mutex for accesing the mSprite variable
	
	int mId;
	int philAmount;

	int lastState;			/* The last recorded state of our philosopher */

	static int totalRuns;

	Food* mFood;

	static std::mutex diningMtx;
	static std::condition_variable cv;
};
