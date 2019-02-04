#pragma once
#include "Entity.h"

class Chopstick : public Entity
{
public:
	Chopstick();
	void						moveTowards(sf::Vector2f goal, float speed);

private:
	void						updateCurrent(sf::Time dt);
	void						drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite mSprite;
	sf::Vector2f mGoal;
};
