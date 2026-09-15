#include "Mueble.h"

#include <cstdlib>
#include <iostream>

sf::Texture Mueble::cargarTextura(const std::string& rutaTextura)
{
    sf::Texture textura;

    if (!textura.loadFromFile(rutaTextura))
    {
        std::cout << "ERROR: NO SE PUDO CARGAR EL MUEBLE " << rutaTextura << '\n';
        exit(-1);
    }

    return textura;
}

Mueble::Mueble(const std::string& rutaTextura,
    const sf::Vector2f& posicion,
    const sf::Vector2f& escala,
    const sf::FloatRect& hitboxLocal)
    : _textura(cargarTextura(rutaTextura)),
      _sprite(_textura),
      _hitboxLocal(hitboxLocal)
{
    _sprite.setPosition(posicion);
    _sprite.setScale(escala);
}

sf::FloatRect Mueble::getGlobalBounds() const
{
    const sf::Vector2f posicion = _sprite.getPosition();
    const sf::Vector2f escala = _sprite.getScale();

    return {
        {
            posicion.x + _hitboxLocal.position.x * escala.x,
            posicion.y + _hitboxLocal.position.y * escala.y
        },
        {
            _hitboxLocal.size.x * escala.x,
            _hitboxLocal.size.y * escala.y
        }
    };
}

void Mueble::dibujar(sf::RenderWindow& ventana) const
{
    ventana.draw(_sprite);
}
