#include "Philosopher.h"

Philosopher::Philosopher(const TextureHolder<std::string> &th)
	:mSprite(th.get("Philosopher"))
{
	this->setOrigin(mSprite.getLocalBounds().height / 2, mSprite.getLocalBounds().width / 2);
}

void Philosopher::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}