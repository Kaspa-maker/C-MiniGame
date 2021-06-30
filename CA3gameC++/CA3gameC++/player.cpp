#include "player.h"
#include <iostream>


void player::initializeTexturePlayer()
{
	!texturePlayer.loadFromFile("textures/player1.png");
}

void player::initializeSpritePlayer()
{
	spritePlayer.setTexture(texturePlayer);

	spritePlayer.scale(0.1f, 0.1f);
	spritePlayer.setPosition(375, 500);
}

player::player()
{
	health = 100;
	moveSpeed = 5.0f;
	initializeTexturePlayer();
	initializeSpritePlayer();
}

const sf::Vector2f& player::getPosition() const
{
	return spritePlayer.getPosition();
}

const sf::FloatRect player::getBounds() const
{
	return spritePlayer.getGlobalBounds();
}

void player::moveShip(const float x, const float y)
{
	spritePlayer.move(moveSpeed * x, moveSpeed * y);
}

const bool player::canAttack()
{
	return false;
}


void player::renderPlayer(sf::RenderTarget& target)
{
	target.draw(spritePlayer);
}

