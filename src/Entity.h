#pragma once
#include "HitboxComponent.h"
class Entity
{
public:
	Entity(sf::FloatRect& bounds, sf::Texture& texture, sf::FloatRect hitboxBounds);
	~Entity();

	const sf::FloatRect getBounds(short type = 0);
	const sf::Vector2f& getPosition() const;
	
	void setPosition(sf::Vector2f&& pos);
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
protected:
	std::vector<sf::Vertex>sprite;
	sf::Texture& texture;
	sf::RenderStates state;
	std::unique_ptr<HitboxComponent> hitboxComponent;
};

