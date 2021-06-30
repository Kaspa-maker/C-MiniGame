#include "Laser.h"



Laser::Laser()
{

}

Laser::Laser(sf::Texture* texture, float y_, float shot_Speed, float pos_x, float pos_y)
{
	laser.setTexture(*texture);
	laser.setPosition(pos_x, pos_y);
	laser.scale(0.1f, 0.1f);
	direction.y = y_;
	shotSpeed = shot_Speed;
}

const sf::FloatRect Laser::getBounds() const
{
	return laser.getGlobalBounds();
}

void Laser::updateLaser()
{
	laser.move(shotSpeed * direction);
}

void Laser::renderLaser(sf::RenderTarget* target)
{
	target->draw(laser);
}
