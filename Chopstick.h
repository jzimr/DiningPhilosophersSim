#pragma once
#include "Entity.h"
#include "TextureHolder.h"
#include <iostream>

class Chopstick : public Entity
{
public:
	Chopstick(const TextureHolder<std::string> &th);
	void						moveTowards(GameObject* gameObject, float speed);
	void						moveTowards(sf::Vector2f goal, float speed);
	void						setSpawn(sf::Vector2f spawn);
	void						resetPos(float speed);
	bool						isAvailable();			// Chopstick is currently not in use											

private:
	void						updateCurrent(float dt);
	void						drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite mSprite;
	sf::Vector2f mGoal;
	sf::Vector2f mSpawn;
};
