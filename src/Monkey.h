#pragma once
#include "Animation.h"
class Monkey :
    public Entity
{
public:
    Monkey(sf::FloatRect&& bounds, sf::FloatRect&& hitbox_bounds, sf::Texture& texture, sf::Vector2f&& velocity);
    ~Monkey();
    
    void move(const float&& dir_x, const float&& dir_y, const float& dt);
    void jump();
    void fall(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget& target);

private:
    sf::Vector2f velocity;
    float acceleration;
    std::unique_ptr<Animation>animation;
};

