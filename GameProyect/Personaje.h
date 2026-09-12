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
    sf::FloatRect getGlobalBounds() const;
    void mover(const sf::Vector2f& desplazamiento);

    void draw(sf::RenderTarget& target,
        sf::RenderStates states) const override;
};