#pragma once
#include "Entity.h"
#include "TextureHolder.h"

class Food : public Entity
{
public:
	Food(const TextureHolder<std::string> &th);

private:
	void						drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite mSprite;
};