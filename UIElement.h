#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
class UIManager;

class UIElement : public GameObject
{
public:
	UIElement();
	bool						containsPos(sf::Vector2f mousePos);
	virtual void				executeAction();

	void						setTexture(const sf::Texture& texture);

private:
	virtual void				drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	
private:
	sf::Sprite					mSprite;
};


