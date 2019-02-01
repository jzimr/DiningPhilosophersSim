#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "GameObject.h"

const int WINDOW_X = 640;
const int WINDOW_Y = 360;
const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

class Sim : private sf::NonCopyable
{
public:
	Sim();
	void						run();

private:
	void						update(sf::Time elapsedTime);
	void						render();

private:
	sf::RenderWindow			mWindow;
	sf::Time					mFrameRateUpdateTime;
	std::size_t					mFrameRateNumFrames;
};
