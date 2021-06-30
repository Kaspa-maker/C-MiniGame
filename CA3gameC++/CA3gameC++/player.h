#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class player
{
private:
	sf::Sprite spritePlayer;
	sf::Texture texturePlayer;
	float moveSpeed;
	int health;

	void initializeSpritePlayer();
	void initializeTexturePlayer();
	
public:
	player();
	
	const sf::Vector2f& getPosition() const;

	const sf::FloatRect getBounds() const;

	void moveShip(const float x, const float y);
	const bool canAttack();
	void renderPlayer(sf::RenderTarget& target);
};

