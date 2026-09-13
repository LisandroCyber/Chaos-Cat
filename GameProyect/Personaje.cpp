#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include <iostream>

sf::Texture Personaje::cargarTextura()
{
    sf::Texture textura;

    if (!textura.loadFromFile("images/GatoNaranja_spritesheet_5frames_fixed.png"))
    {
        std::cout << "ERROR: NO SE PUDO CARGAR EL GATO\n";
        exit(-1);
    }

    return textura;
}

Personaje::Personaje()
    : _texture(cargarTextura()), _sprite(_texture)
{
    _frameAncho = 600;
    _frameAlto = 724;

    _sprite.setPosition({ 100.f, 100.f });
    _sprite.setScale({ 0.3f, 0.3f });
    _velocity = { 0.f, 0.f };

    _estado = EstadoGato::Quieto;
    _contandoQuieto = false;

    _saltando = false;
    _alturaSalto = 0.f;
    _velocidadSalto = 0.f;

    _sprite.setOrigin({
        _frameAncho / 2.f,
        _frameAlto / 2.f
    });

    _sprite.setTextureRect(sf::IntRect(
        { 0, 0 },
        { _frameAncho, _frameAlto }
    ));

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
    bool seMueve = false;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        _velocity.x = -velocidadActual;
        _sprite.setScale({ -0.3f, 0.3f });
        seMueve = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        _velocity.x = velocidadActual;
        _sprite.setScale({ 0.3f, 0.3f });
        seMueve = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        _velocity.y = -velocidadActual;
        seMueve = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        _velocity.y = velocidadActual;
        seMueve = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        saltar();
    }

    if (seMueve || _saltando || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
    {
        _contandoQuieto = false;
    }

    if (_saltando)
    {
        _estado = EstadoGato::Saltando;

        _alturaSalto += _velocidadSalto;
        _velocidadSalto += 0.5f;

        if (_alturaSalto >= 0.f)
        {
            _alturaSalto = 0.f;
            _velocidadSalto = 0.f;
            _saltando = false;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
    {
        _estado = EstadoGato::Sentado;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
    {
        _estado = EstadoGato::Agachado;
    }
    else if (seMueve)
    {
        _estado = EstadoGato::Caminando;
    }
    else
    {
        if (!_contandoQuieto)
        {
            _relojQuieto.restart();
            _contandoQuieto = true;
            _estado = EstadoGato::Quieto;
        }
        else if (_relojQuieto.getElapsedTime().asSeconds() >= 0.5f)
        {
            _estado = EstadoGato::Sentado;
        }
        else
        {
            _estado = EstadoGato::Quieto;
        }
    }

    _sprite.move(_velocity);
    actualizarSprite();

    sf::FloatRect hitbox = getGlobalBounds();
    float ancho = hitbox.size.x;
    float alto = hitbox.size.y;

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

void Personaje::actualizarSprite()
{
    int frame = 0;

    if (_estado == EstadoGato::Quieto)
        frame = 0;
    else if (_estado == EstadoGato::Caminando)
        frame = 1;
    else if (_estado == EstadoGato::Agachado)
        frame = 2;
    else if (_estado == EstadoGato::Saltando)
        frame = 3;
    else if (_estado == EstadoGato::Sentado)
        frame = 4;

    _sprite.setTextureRect(sf::IntRect(
        { frame * _frameAncho, 0 },
        { _frameAncho, _frameAlto }
    ));
}

void Personaje::saltar()
{
    if (!_saltando)
    {
        _saltando = true;
        _velocidadSalto = -8.f;
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
    float escalaX = _sprite.getScale().x < 0.f ? -_sprite.getScale().x : _sprite.getScale().x;
    float escalaY = _sprite.getScale().y < 0.f ? -_sprite.getScale().y : _sprite.getScale().y;

    float ancho = 360.f * escalaX;
    float alto = 360.f * escalaY;

    if (_estado == EstadoGato::Agachado)
    {
        ancho = 420.f * escalaX;
        alto = 300.f * escalaY;
    }
    else if (_estado == EstadoGato::Saltando)
    {
        ancho = 420.f * escalaX;
        alto = 320.f * escalaY;
    }
    else if (_estado == EstadoGato::Sentado)
    {
        ancho = 270.f * escalaX;
        alto = 360.f * escalaY;
    }

    return sf::FloatRect(
        {
            _sprite.getPosition().x - ancho / 2.f,
            _sprite.getPosition().y - alto / 2.f
        },
        { ancho, alto }
    );
}

void Personaje::mover(const sf::Vector2f& desplazamiento)
{
    _sprite.move(desplazamiento);
}
