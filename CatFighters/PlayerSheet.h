#pragma once
#include "AssetManager.h"
#include "DEFINITIONS.h"

struct SpriteSheet
{
	sf::Sprite sprite;
	sf::IntRect spriteRect;
	sf::Vector2i frameSize;
	int columns;
	int rows;
	int animationSpeed; //the lower, the faster
};

class PlayerSheet
{
public:
	PlayerSheet(int spriteID);
	~PlayerSheet();

	void Draw(sf::RenderWindow &window);
	void Animate();
	void loadSprite(bool secondPlayer = false);
	void animationMachine();

	bool isJumping = false;
	bool isFalling = false;
	bool isAttacking = false;

	SpriteSheet activeSprite;

private:

	void setSheetAttributes(sf::Texture &textureSheet, SpriteSheet &sheet, int animationSpeed, int columns, int rows);

	int animationAccumulator = 0;
	int xAnim = 1;

	bool moveY = false;


	AssetManager asset;

	SpriteSheet idle;
	SpriteSheet jumpAir;
	SpriteSheet jumpFall;
	SpriteSheet attack;
};



