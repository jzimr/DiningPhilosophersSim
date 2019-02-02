#include "World.h"

World::World(sf::RenderWindow & window)
	: mWindow(window)
	, topNode()
{
	loadTextures();
	buildScene();
}

void World::update(sf::Time dt)
{
	topNode.update(dt.asSeconds());
}

void World::draw()
{
	mWindow.draw(topNode);
}

void World::loadTextures()
{
}

void World::buildScene()
{
}
