#include "SpriteNode.h"

SpriteNode::SpriteNode(const sf::Texture& texture)
	: mSprite(texture)
{
	this->setOrigin(mSprite.getLocalBounds().height / 2, mSprite.getLocalBounds().width / 2);
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect)
	: mSprite(texture, textureRect)
{
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}