#include "UIElement.h"

UIElement::UIElement()
	: mSprite{}
{
}

bool UIElement::containsPos(sf::Vector2f mousePos)
{
	if (mSprite.getGlobalBounds().contains(mousePos))
		return true;
	return false;
}

void UIElement::executeAction()
{
	/* Nothing by default */
}


void UIElement::setTexture(const sf::Texture& texture)
{
	mSprite.setTexture(texture);
}

void UIElement::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}