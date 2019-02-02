#include "Sim.h"

Sim::Sim()
	: mWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), "Dining Philosophers Sim", sf::Style::Close)
	, topNode()
	, mTextures()
	, mView(mWindow.getDefaultView())
{
	mView.setSize(RESOLUTION_X, RESOLUTION_Y);
	mView.setCenter(200, 200);

	loadTextures();
	buildScene();
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
			processEvents();
			update(TimePerFrame);
		}

		render();
	}
}

void Sim::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			break;

		case sf::Event::KeyReleased:
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Sim::update(sf::Time elapsedTime)
{
	topNode.update(elapsedTime.asSeconds());
}

void Sim::render()
{
	mWindow.setView(mView);

	mWindow.clear();
	mWindow.draw(topNode);
	mWindow.display();
}

void Sim::loadTextures()
{
	mTextures.load("Chopstick", "Media/chopstick.png");
	mTextures.load("Face", "Media/face.png");
}

void Sim::buildScene()
{
	SpriteNode* chopstick = new SpriteNode(mTextures.get("Chopstick"));
	topNode.attachChild(chopstick);
	chopstick->setPosition(200, 200);

	SpriteNode* face = new SpriteNode(mTextures.get("Face"));
	topNode.attachChild(face);
	face->setPosition(250, 200);
}
