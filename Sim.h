#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "TextureHolder.h"
#include "SpriteNode.h"

const int WINDOW_X = 1280;
const int WINDOW_Y = 720;
const int RESOLUTION_X = 480;
const int RESOLUTION_Y = 270;
const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

class Sim : private sf::NonCopyable
{
public:
								Sim();
	void						run();

private:
	void						processEvents();
	void						update(sf::Time elapsedTime);
	void						render();

	void						loadTextures();
	void						buildScene();

private:
	GameObject					topNode;	/* Pater familias of all gameobjects */

	sf::RenderWindow			mWindow;
	sf::View					mView;

	TextureHolder<std::string>	mTextures;
	sf::Time					mFrameRateUpdateTime;
	std::size_t					mFrameRateNumFrames;
};
