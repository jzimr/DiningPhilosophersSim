#pragma once
#include "GameObject.h"

/*
	An Entity is simply a moving object
*/

class Entity : public GameObject
{
public:
	void						setVelocity(sf::Vector2f velocity);
	void						setVelocity(float vx, float vy);
	sf::Vector2f				getVelocity() const;

private:
	virtual void				updateCurrent(float dt);

private:
	sf::Vector2f				mVelocity;
};
