#pragma once
#include "AssetManager.h"
#include "DEFINITIONS.h"

class PlayerSheet
{
public:
	PlayerSheet();
	~PlayerSheet();

	void Draw(sf::RenderWindow &window);

	void Animate(float dt, int columns, int rows);

	void loadSprite(int columns, int rows);

	sf::IntRect playerIdleSource;
	sf::Vector2i frameSize;
	int animationAccumulator = 0;

	int xAnim = 1;
	bool moveY = false;
	
	AssetManager asset;

	sf::Sprite activeSprite;
	sf::Sprite idle;
};

