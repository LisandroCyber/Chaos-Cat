#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Humano : public sf::Drawable
{
private:
    sf::Texture _textura;
    sf::Sprite _sprite;
    int _frameAncho;
    int _frameAlto;

    static sf::Texture cargarTextura(const std::string& rutaTextura);
    static sf::Vector2f obtenerOrigenVisible(const sf::Texture& textura,
        int frameAncho,
        int frameAlto);

public:
    Humano(const std::string& rutaTextura,
        const sf::Vector2f& posicion,
        int frameAncho,
        int frameAlto,
        const sf::Vector2f& escala);

    void draw(sf::RenderTarget& target,
        sf::RenderStates states) const override;
};
