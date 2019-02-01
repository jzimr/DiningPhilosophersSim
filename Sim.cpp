#include "Sim.h"

Sim::Sim()
	: mWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), "Dining Philosophers Sim", sf::Style::Close)
{
}

void Sim::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			update(TimePerFrame);
		}

		render();
	}
}

void Sim::update(sf::Time elapsedTime)
{
	//m_systemManager->update(elapsedTime.asSeconds());
}

void Sim::render()
{
	mWindow.clear();

	mWindow.display();
}