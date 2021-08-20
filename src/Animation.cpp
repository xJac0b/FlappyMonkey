#include "pch.h"
#include "Animation.h"

Animation::Animation(std::vector<sf::Vertex>& sprite, unsigned image_count, sf::Vector2f image_size, float switch_time)
	: sprite(sprite), imageCount(image_count), currentImage(0U), imageSize(image_size),
	switchTime(switch_time), totalTime(switch_time)
{
}

Animation::~Animation()
{
}

void Animation::update(const float& dt)
{
	this->totalTime += dt;
	if (this->totalTime >= this->switchTime)
	{
		this->totalTime -= this->switchTime;
		this->currentImage++;
		if (this->imageCount == this->currentImage)
			this->currentImage = 0U;

		gui::setVertexShape(this->sprite, sf::FloatRect(this->currentImage*this->imageSize.x, 0.f,
			this->imageSize.x, this->imageSize.y), 0);
	}
	
}
