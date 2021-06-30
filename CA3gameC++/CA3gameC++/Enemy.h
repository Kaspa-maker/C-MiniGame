#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Enemy
{
private:
	sf::Sprite spriteEnemy;
	sf::Texture textureEnemy;
	int health;
	int damage;
	int score;

	void initializeSpriteEnemy();
	void initializeTextureEnemy();
	void initializeVariables();

public:
	Enemy(float pos_x, float pos_y);
	const sf::FloatRect getBounds() const;
	const int& getScore() const;

	void updateEnemy();
	void renderEnemy(sf::RenderTarget& target);
};

