#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "TextureHolder.h"
#include "SpriteNode.h"
#include <vector>
#include "Philosopher.h"
#include "Food.h"
#include "Chopstick.h"
#include <thread>

const float PI = 3.14159265f;
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

	void						startSim();			

private:
	std::vector<Philosopher*>	philosophers;
	std::vector<Chopstick*>		chopsticks;
	std::vector<Food*>			foods;
	std::vector<std::thread>	threads;

	/* Settings of the simulation */
	int PHIL_AMOUNT = 5;		/* number of philosophers */
	int MAX_RUNS = 100;			/* in total how often is eaten */
	
	sf::Vector2f				tablePos;		/* temp */
	float						tableRadius;	/* temp */

	GameObject					topNode;	/* Top ancestor of all gameobjects */
	GameObject					topUINode;	/* Top ancestor of all UI elements */

	sf::RenderWindow			mWindow;
	sf::View					mView;

	//UIManager					mUIManager;

	TextureHolder<std::string>	mTextures;
	sf::Time					mFrameRateUpdateTime;
	std::size_t					mFrameRateNumFrames;
};
