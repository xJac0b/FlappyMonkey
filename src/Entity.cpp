#include "pch.h"
#include "Entity.h"

Entity::Entity(sf::FloatRect& bounds, sf::Texture& texture, sf::FloatRect hitboxBounds) : texture(texture)
{
	this->sprite.resize(4, sf::Vertex());
	gui::setVertexShape(this->sprite, bounds);
	this->state.texture = &texture;
	this->hitboxComponent = std::make_unique<HitboxComponent>(sf::FloatRect(bounds.left,bounds.top,hitboxBounds.width,hitboxBounds.height),
		sf::Vector2f(hitboxBounds.left, hitboxBounds.top));
}

Entity::~Entity()
{
}

const sf::FloatRect Entity::getBounds(short type)
{
	if (type)
		return this->hitboxComponent->getGlobalBounds();
	return gui::getVertexShape(this->sprite);
}

const sf::Vector2f& Entity::getPosition() const
{
	return this->sprite[0].position;
}

void Entity::setPosition(sf::Vector2f&& pos)
{
	gui::setVertexShape(this->sprite, sf::FloatRect(pos, sf::Vector2f(gui::getVertexShape(this->sprite).width,
		gui::getVertexShape(this->sprite).height)));
}

