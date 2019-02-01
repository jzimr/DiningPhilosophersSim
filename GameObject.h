#pragma once
#include <SFML/Graphics.hpp>

class GameObject : public sf::Transformable, public sf::Drawable, public sf::NonCopyable
{
public:
	GameObject();
	void						update(float dt);
	void						attachChild(GameObject* child);
	GameObject*					detachChild(const GameObject& node);		//	Returns the child after detaching it

private:
	virtual void				updateCurrent(float dt);
	virtual void				updateChildren(float dt);

	virtual void				draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void				drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void						drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<GameObject*>	mChildren;
	GameObject*					mParent;
};