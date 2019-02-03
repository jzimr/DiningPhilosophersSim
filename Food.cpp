#include "Food.h"

Food::Food(const TextureHolder<std::string> &th)
	: mSprite(th.get("Food"))
{
	this->setOrigin(mSprite.getLocalBounds().height / 2, mSprite.getLocalBounds().width / 2);
}

void Food::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}