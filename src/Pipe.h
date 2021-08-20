#pragma once
#include "Monkey.h"
class Pipe :
    public Entity
{
public:   
    Pipe(sf::FloatRect&& bounds, sf::FloatRect&& hitbox_bounds, sf::Texture& texture);
    ~Pipe();

    void update(const float& dt);
    void render(sf::RenderTarget& target);
};

