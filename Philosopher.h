#pragma once
#include "Entity.h"
#include "TextureHolder.h"
#include <iostream>
#include <mutex>

class Philosopher : public Entity
{
public:
	explicit					Philosopher(const TextureHolder<std::string> &th);
	
	void						philosopher();
	/*
	void						eat();
	void						think();
	*/


private:
	void						drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite mSprite;
	static std::mutex mutex;
};
