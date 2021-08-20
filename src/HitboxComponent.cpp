#include "pch.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::FloatRect bounds, sf::Vector2f offset) : offset(offset)
{
	this->hitbox.setSize(sf::Vector2f(bounds.width, bounds.height));
	this->hitbox.setPosition(bounds.left + offset.x, bounds.top + offset.y);
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

void HitboxComponent::update(sf::Vector2f pos)
{
	this->hitbox.setPosition(pos.x + offset.x, pos.y + offset.y);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
