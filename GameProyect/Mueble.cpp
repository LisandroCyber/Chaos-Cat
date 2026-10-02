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

    return sf::FloatRect(
        posicion.x + _hitboxLocal.left * escala.x,
        posicion.y + _hitboxLocal.top * escala.y,
        _hitboxLocal.width * escala.x,
        _hitboxLocal.height * escala.y
    );
}

void Mueble::dibujar(sf::RenderWindow& ventana) const
{
    ventana.draw(_sprite);
}
