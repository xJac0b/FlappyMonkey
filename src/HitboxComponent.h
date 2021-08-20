#pragma once
#include "State.h"
class HitboxComponent
{
public:
	HitboxComponent(sf::FloatRect bounds, sf::Vector2f offset);
	~HitboxComponent();

	const sf::FloatRect getGlobalBounds() const;

	void update(sf::Vector2f pos);
	void render(sf::RenderTarget& target);
private:
	sf::RectangleShape hitbox;
	sf::Vector2f offset;
};

