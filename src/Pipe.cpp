#include "pch.h"
#include "Pipe.h"

Pipe::Pipe(sf::FloatRect&& bounds, sf::FloatRect&& hitbox_bounds, sf::Texture& texture) 
	: Entity(bounds,texture, hitbox_bounds)
{
	gui::setVertexShape(this->sprite, sf::FloatRect{0.f, 0.f, 215.f, 300.f},0);
}


Pipe::~Pipe()
{
}

void Pipe::update(const float& dt)
{
	this->hitboxComponent->update(this->getPosition());
}

void Pipe::render(sf::RenderTarget& target)
{
	target.draw(&this->sprite[0], 4, sf::Quads, this->state);
	//this->hitboxComponent->render(target);
}
