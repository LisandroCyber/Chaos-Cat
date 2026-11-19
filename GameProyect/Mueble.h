#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Mueble
{
private:
    sf::Texture _textura;
    sf::Sprite _sprite;
    sf::FloatRect _hitboxLocal;

    static sf::Texture cargarTextura(const std::string& rutaTextura);

public:
    Mueble(const std::string& rutaTextura,
        const sf::Vector2f& posicion,
        const sf::Vector2f& escala,
        const sf::FloatRect& hitboxLocal);

    sf::FloatRect getGlobalBounds() const;

    void dibujar(sf::RenderWindow& ventana) const;
};
