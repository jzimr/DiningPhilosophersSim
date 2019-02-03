#include "Sim.h"

Sim::Sim()
	: mWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), "Dining Philosophers Sim", sf::Style::Close)
	, topNode()
	, mTextures()
	, mView(mWindow.getDefaultView())
	, tablePos(RESOLUTION_X / 2.f, RESOLUTION_Y / 2.f)
{
	mView.setSize(RESOLUTION_X, RESOLUTION_Y);
	mView.setCenter(RESOLUTION_X / 2.f, RESOLUTION_Y / 2.f);
	mWindow.setFramerateLimit(120);		/* 120 FPS to limit GPU usage */

	tableRadius = 100;
	philAmount = 5;

	loadTextures();
	buildScene();
	startSim();
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
	mTextures.load("Philosopher", "Media/face.png");
	mTextures.load("Food", "Media/food.png");
}

void Sim::buildScene()
{
	/*
	Set up scene
	*/
	sf::Vector2f mid = sf::Vector2f(RESOLUTION_X / 2.f, RESOLUTION_Y / 2.f);

	for (int i = 0; i < philAmount; i++)
	{
		Philosopher* phil = new Philosopher(mTextures);
		philosophers.push_back(phil);
		topNode.attachChild(phil);

		float degree = i * (360.f / philAmount);
		phil->setPosition(tablePos.x + (cos(degree * PI / 180.0) * tableRadius), tablePos.y + (sin(degree * PI / 180.0) * tableRadius));


		Food* food = new Food(mTextures);
		topNode.attachChild(food);

		food->setPosition(tablePos.x + (cos(degree * PI / 180.0) * (tableRadius / 2)), tablePos.y + (sin(degree * PI / 180.0) * (tableRadius / 2)));


		SpriteNode* chops = new SpriteNode(mTextures.get("Chopstick"));
		topNode.attachChild(chops);
		chops->setRotation(degree - 15);		/* -15 to fine adjust the sprite */

		degree = degree + (360.f / philAmount / 2);
		chops->setPosition(tablePos.x + (cos(degree * PI / 180.0) * (tableRadius / 1.7)), tablePos.y + (sin(degree * PI / 180.0) * (tableRadius / 1.7)));
	}
}

void Sim::startSim()
{
	// Spawn a thread for each philosopher
	for (int i = 0; i < philAmount; i++)
	{
		threads.push_back(std::thread(&Philosopher::philosopher, philosophers[i]));
	}
}