#include "pch.h"
#include "Monkey.h"

Monkey::Monkey(sf::FloatRect&& bounds, sf::FloatRect&& hitbox_bounds, sf::Texture& texture, sf::Vector2f&& velocity) 
	: Entity(bounds, texture, hitbox_bounds),
velocity(velocity), acceleration(1.f)
{
	gui::setVertexShape(this->sprite, sf::FloatRect(0.f, 0.f,
		256.f, 256.f), 0);
	this->animation = std::make_unique<Animation>(this->sprite, 2U, sf::Vector2f(256.f,256.f), 0.5f);
}

Monkey::~Monkey()
{
}

void Monkey::move(const float&& dir_x, const float&& dir_y, const float& dt)
{
	for (auto& i : this->sprite)
	{
		i.position.x += this->velocity.x * dir_x * dt ;
		i.position.y += this->acceleration * this->velocity.y * dir_y * dt;
	}
}

void Monkey::jump()
{
	this->acceleration = 1.8f;
}

void Monkey::fall(const float& dt)
{
	this->move(0.f, 2.f, dt);
}
 
void Monkey::update(const float& dt)
{
	if (this->acceleration > 1.f)
	{
		this->velocity.y = 350.f;
		this->move(1.f, -1.f, dt);
		this->acceleration -= 6.f * dt;
		if (this->acceleration < 1.f)
		{
			this->acceleration = 1.f;
			this->velocity.y = 600.f;
		}
			
	}
	else
	{
		this->move(1.f, 1.f, dt);
	}
	this->hitboxComponent->update(this->getPosition());
	this->animation->update(dt);
}

void Monkey::render(sf::RenderTarget& target)
{
	target.draw(&this->sprite[0], 4, sf::Quads, this->state);
	//this->hitboxComponent->render(target);
}
