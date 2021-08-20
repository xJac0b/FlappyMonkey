#pragma once
#include "PauseMenu.h"
class Animation
{
public:
	Animation(std::vector<sf::Vertex>& sprite, unsigned image_count, sf::Vector2f image_size, float switch_time);
	~Animation();

	void update(const float& dt);
private:
	std::vector<sf::Vertex>& sprite;
	unsigned imageCount;
	unsigned currentImage;
	sf::Vector2f imageSize;
	float switchTime;
	float totalTime;
};

