#include "Humano.h"

#include <cstdlib>
#include <iostream>

sf::Texture Humano::cargarTextura(const std::string& rutaTextura)
{
    sf::Texture textura;

    if (!textura.loadFromFile(rutaTextura))
    {
        std::cout << "ERROR: NO SE PUDO CARGAR EL HUMANO " << rutaTextura << '\n';
        exit(-1);
    }

    return textura;
}

sf::Vector2f Humano::obtenerOrigenVisible(const sf::Texture& textura,
    int frameAncho,
    int frameAlto)
{
    const sf::Image imagen = textura.copyToImage();
    unsigned int izquierda = static_cast<unsigned int>(frameAncho);
    unsigned int derecha = 0;
    unsigned int abajo = 0;
    bool encontroPixelVisible = false;

    for (unsigned int y = 0; y < static_cast<unsigned int>(frameAlto); y++)
    {
        for (unsigned int x = 0; x < static_cast<unsigned int>(frameAncho); x++)
        {
            if (imagen.getPixel({ x, y }).a > 0)
            {
                if (x < izquierda)
                {
                    izquierda = x;
                }

                if (x > derecha)
                {
                    derecha = x;
                }

                if (y > abajo)
                {
                    abajo = y;
                }

                encontroPixelVisible = true;
            }
        }
    }

    if (!encontroPixelVisible)
    {
        return {
            frameAncho / 2.f,
            static_cast<float>(frameAlto)
        };
    }

    return {
        (izquierda + derecha) / 2.f,
        static_cast<float>(abajo)
    };
}

Humano::Humano(const std::string& rutaTextura,
    const sf::Vector2f& posicion,
    int frameAncho,
    int frameAlto,
    const sf::Vector2f& escala)
    : _textura(cargarTextura(rutaTextura)),
      _sprite(_textura),
      _frameAncho(frameAncho),
      _frameAlto(frameAlto)
{
    _sprite.setTextureRect(sf::IntRect(
        { 0, 0 },
        { _frameAncho, _frameAlto }
    ));
    _sprite.setOrigin(obtenerOrigenVisible(_textura, _frameAncho, _frameAlto));
    _sprite.setPosition(posicion);
    _sprite.setScale(escala);
}

void Humano::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}
