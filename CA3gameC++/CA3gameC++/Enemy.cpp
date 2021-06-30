#include "Enemy.h"

void Enemy::initializeSpriteEnemy()
{
	textureEnemy.loadFromFile("textures/enemy1.png");
}

void Enemy::initializeTextureEnemy()
{
	spriteEnemy.setTexture(textureEnemy);

	spriteEnemy.scale(0.1f, 0.1f);
	spriteEnemy.rotate(180);
	spriteEnemy.setPosition(450, 125);
}

void Enemy::initializeVariables()
{
	health = 100;
	damage = 100;
	score = 100;
}


Enemy::Enemy(float pos_x, float pos_y)
{
	initializeSpriteEnemy();
	initializeTextureEnemy();
	initializeVariables();
	
}

const sf::FloatRect Enemy::getBounds() const
{
	return spriteEnemy.getGlobalBounds();
}

const int& Enemy::getScore() const
{
	return score;
}

void Enemy::updateEnemy()
{
	this->spriteEnemy.move(0.f, 5.f);
}

void Enemy::renderEnemy(sf::RenderTarget& target)
{
	target.draw(spriteEnemy);
}
