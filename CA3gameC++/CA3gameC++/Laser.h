#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Laser
{
private:
	sf::Sprite laser;
	sf::Vector2f direction;
	float shotSpeed;

public:
	Laser();
	Laser(sf::Texture* texture, float y_, float shot_Speed, float pos_x, float pos_y);

	const sf::FloatRect getBounds() const;

	void updateLaser();
	void renderLaser(sf::RenderTarget* target);

};

