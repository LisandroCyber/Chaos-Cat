#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include <iostream>

sf::Texture Personaje::cargarTextura()
{
    sf::Texture textura;

    if (!textura.loadFromFile("images/GatoNaranja.png"))
    {
        std::cout << "ERROR: NO SE PUDO CARGAR EL GATO\n";
        exit(-1);
    }

    return textura;
}

Personaje::Personaje()
    : _texture(cargarTextura()), _sprite(_texture)
{
    _velocity = { 4,4 };
    _sprite.setPosition({ 579.f, 476.f });
    _sprite.setScale({ 0.3f, 0.3f });
    _velocity = {0,0};

    _sprite.setOrigin({
        _sprite.getLocalBounds().size.x / 2.f,
        _sprite.getLocalBounds().size.y / 2.f
    });
}

void Personaje::update()
{
    float velocidadActual = 2.2f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
    {
        velocidadActual = 5.f; // CORRER
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
    {
        velocidadActual = 0.75f; // AGACHADO
    }

    _velocity = { 0.f, 0.f };


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        _velocity.x = -velocidadActual;
        _sprite.setScale({ -0.3f, 0.3f });
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        _velocity.x = velocidadActual;
        _sprite.setScale({ 0.3f, 0.3f });
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        _velocity.y = -velocidadActual;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        _velocity.y = velocidadActual;
    }

    _sprite.move(_velocity);

    
/*
    if (_sprite.getPosition().x < 0)
        _sprite.setPosition({ 0, _sprite.getPosition().y });
    
    if (_sprite.getPosition().x + _sprite.getGlobalBounds().size.x > 1280)
    {
        _sprite.setPosition({
            1280 - _sprite.getGlobalBounds().size.x,
            _sprite.getPosition().y
            });
    }
    
    if (_sprite.getPosition().y < 0)
        _sprite.setPosition({
            _sprite.getPosition().x,
            0
            });
    
    if (_sprite.getPosition().y + _sprite.getGlobalBounds().size.y > 720)
    {
        _sprite.setPosition({
            _sprite.getPosition().x,
            720 - _sprite.getGlobalBounds().size.y
            });
    }

*/

    float ancho = _sprite.getGlobalBounds().size.x;
    float alto = _sprite.getGlobalBounds().size.y;

    float mitadAncho = ancho / 2.f;
    float mitadAlto = alto / 2.f;

    if (_sprite.getPosition().x - mitadAncho < 0)
    {
        _sprite.setPosition({
            mitadAncho,
            _sprite.getPosition().y
            });
    }

    if (_sprite.getPosition().x + mitadAncho > 1280)
    {
        _sprite.setPosition({
            1280.f - mitadAncho,
            _sprite.getPosition().y
            });
    }

    if (_sprite.getPosition().y - mitadAlto < 0)
    {
        _sprite.setPosition({
            _sprite.getPosition().x,
            mitadAlto
            });
    }

    if (_sprite.getPosition().y + mitadAlto > 720)
    {
        _sprite.setPosition({
            _sprite.getPosition().x,
            720.f - mitadAlto
            });
    }

}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

float Personaje::getPosx() {
    return _sprite.getPosition().x;
}

float Personaje::getPosy() {
    return _sprite.getPosition().y;
}

sf::FloatRect Personaje::getGlobalBounds() const
{
    return _sprite.getGlobalBounds();
}

void Personaje::mover(const sf::Vector2f& desplazamiento)
{
    _sprite.move(desplazamiento);
}
