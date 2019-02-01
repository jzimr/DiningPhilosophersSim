#include "gameObject.h"

GameObject::GameObject()
	: mChildren{}
	, mParent{ nullptr }
{
}

void GameObject::attachChild(GameObject* child)
{
	//	Check if the child is already attached to this SceneNode
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](GameObject* p) { return p == child; });

	child->mParent = this;
	mChildren.push_back(std::move(child));
}

GameObject* GameObject::detachChild(const GameObject& node)
{
	//	Check if the child exists within this SceneNode
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](GameObject* p) { return p == &node; });

	GameObject* result = std::move(*found);		//	Move the node to this local variable
	result->mParent = nullptr;
	mChildren.erase(found);				//	Remove from list	
	return result;
}

void GameObject::update(float dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

void GameObject::updateCurrent(float dt)
{
	//	Do nothing by default
}

void GameObject::updateChildren(float dt)
{
	for (GameObject* child : mChildren)
		child->update(dt);
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply globalTransform of current node
	states.transform *= getTransform();

	// Draw node and children with changed globalTransform
	drawCurrent(target, states);
	drawChildren(target, states);
}

void GameObject::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
	// Do nothing by default
}

void GameObject::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const GameObject* child : mChildren)
		child->draw(target, states);
}
