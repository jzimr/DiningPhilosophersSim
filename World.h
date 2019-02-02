#pragma once
#include "GameObject.h"


class World : private sf::NonCopyable
{
public:
	explicit					World(sf::RenderWindow& window);
	void						update(sf::Time dt);
	void						draw();

private:
	void						loadTextures();
	void						buildScene();

private:
	GameObject					topNode;	/* Pater familias of all gameobjects */
	sf::RenderWindow&			mWindow;
};