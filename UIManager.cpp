#include "UIManager.h"

UIManager::UIManager()
	: uiElements{}
{
}

void UIManager::checkMouseClickUI(sf::Vector2f mousePos)
{
	for (int i = 0; i < uiElements.size(); i++)
		if (uiElements[i]->containsPos(mousePos))
			uiElements[i]->executeAction();
}

void UIManager::addUIElement(UIElement* element)
{
	uiElements.push_back(element);
}

