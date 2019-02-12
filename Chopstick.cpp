#include "Chopstick.h"

Chopstick::Chopstick(const TextureHolder<std::string> &th)
	: mSprite(th.get("Chopstick"))
	, mSpawn(getPosition())
{
	this->setOrigin(mSprite.getLocalBounds().height / 2, mSprite.getLocalBounds().width / 2);
}

void Chopstick::moveTowards(GameObject* gameObject, float speed)
{
	moveTowards(gameObject->getPosition(), speed);
}

void Chopstick::moveTowards(sf::Vector2f goal, float speed)
{
	mGoal = goal;

	// Error if direction = (0, 0) (FIX!)
	sf::Vector2f direction = goal - getPosition();

	float v = sqrtf(powf(direction.x, 2) + powf(direction.y, 2));
	float vx = direction.x / v;
	float vy = direction.y / v;

	setVelocity(vx * speed, vy * speed);

	/* std::cout << vx << ", " << vy << " | " << mGoal.x << ", " << mGoal.y << 
		" | " << getPosition().x << ", " << getPosition().y << " | " 
		<< direction.x << ", " << direction.y << '\n'; */
}

void Chopstick::setSpawn(sf::Vector2f spawn)
{
	mSpawn = spawn;
}

void Chopstick::resetPos(float speed)
{
	//setPosition(mSpawn);
	moveTowards(mSpawn, speed);
}

bool Chopstick::isAvailable()
{
	return getPosition() == mSpawn;
}

void Chopstick::updateCurrent(float dt)
{
	move(getVelocity() * dt);

	/*
	/* Check if we have overshot our intended destination */
	if (((getVelocity().x > 0 && getPosition().x > mGoal.x) ||
		(getVelocity().x < 0 && getPosition().x < mGoal.x)) ||
		((getVelocity().y > 0 && getPosition().y > mGoal.y) ||
		(getVelocity().y < 0 && getPosition().y < mGoal.y)))
	{
		setVelocity(0, 0);
		//std::cout << "-----======>>> " << mGoal.x << ", " << mGoal.y << '\n';

		setPosition(mGoal);
	}
	
}

void Chopstick::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
