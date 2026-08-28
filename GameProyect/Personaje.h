#pragma once
#include <SFML/Graphics.hpp>

class Personaje : public sf::Drawable
{
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Vector2f _velocity;

    static sf::Texture cargarTextura();

public:
    Personaje();

    void update();
    float getPosx();
    float getPosy();

    void draw(sf::RenderTarget& target,
        sf::RenderStates states) const override;
};