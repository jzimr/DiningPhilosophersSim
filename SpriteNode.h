#pragma once
#include "GameObject.h"

class SpriteNode : public GameObject
{
public:
	explicit					SpriteNode(const sf::Texture& texture);
								SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);

private:
	virtual void				drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite					mSprite;
};