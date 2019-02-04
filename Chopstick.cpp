#include "Chopstick.h"

Chopstick::Chopstick()
{
	this->setOrigin(mSprite.getLocalBounds().height / 2, mSprite.getLocalBounds().width / 2);
}

void Chopstick::moveTowards(sf::Vector2f goal, float speed)
{
	mGoal = goal;

	// Error if direction = (0, 0) (FIX!)
	sf::Vector2f direction = goal - getPosition();

	int v = sqrtf(powf(goal.x, 2) + powf(goal.y, 2));
	int vx = direction.x / v;
	int vy = direction.y / v;

	setVelocity(vx * speed, vy * speed);
}

void Chopstick::updateCurrent(sf::Time dt)
{
	move(getVelocity() * dt.asSeconds());

	/* Check if we have overshot our intended destination */
	if ((getVelocity().x > 0 && getPosition().x > mGoal.x) ||
		(getVelocity().x < 0 && getPosition().x < mGoal.x))
	{
		setVelocity(0, 0);
		setPosition(mGoal);
	}
}

void Chopstick::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
