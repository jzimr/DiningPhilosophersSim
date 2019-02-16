#pragma once
#include "UIElement.h"
#include <vector>

/*
This class to be initiated once and put into the part of the
engine where input is handled.
*/

class UIManager
{
public:
	UIManager();

	void						checkMouseClickUI(sf::Vector2f mousePos);
	void						addUIElement(UIElement* element);

private:
	std::vector<UIElement*>		uiElements;
};
