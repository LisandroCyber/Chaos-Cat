#include "Juego.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

Juego::Juego()
    : _window(sf::VideoMode({ 1280, 720 }), "Chaos Cat SFML 3"),
      _spriteFondo(_texturaFondo),
      _tocandoTaza(false),
      _mostrarHitboxes(false)
{
    _window.setFramerateLimit(144);

    if (!_texturaFondo.loadFromFile("images/fondo.jpg"))
    {
        std::cout << "Error al cargar la imagen de fondo!" << std::endl;
        exit(-1);
    }
}

void Juego::ejecutar()
{
    while (_window.isOpen())
    {
        procesarEventos();
        actualizar();
        dibujar();
    }
}

void Juego::procesarEventos()
{
    while (const auto event = _window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            _window.close();
        }
    }
}

void Juego::actualizar()
{
    _gato.update();
    resolverColisionGatoTaza();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
    {
        std::cout << "Posision en x: " << _gato.getPosx() << std::endl;
        std::cout << "Posision en y: " << _gato.getPosy() << std::endl;
    }
}

void Juego::dibujar()
{
    _window.clear();
    _window.draw(_spriteFondo);
    _window.draw(_gato);
    _window.draw(_taza);
    dibujarHitboxes();
    _window.display();
}

void Juego::resolverColisionGatoTaza()
{
    const sf::FloatRect areaTaza = _taza.getGlobalBounds();
    const sf::FloatRect areaGato = _gato.getGlobalBounds();

    if (areaGato.findIntersection(areaTaza))
    {
        if (!_tocandoTaza)
        {
            std::cout << "TIRAR TAZA" << std::endl;
            _tocandoTaza = true;
        }

        float dx1 = areaTaza.position.x - (areaGato.position.x + areaGato.size.x);
        float dx2 = (areaTaza.position.x + areaTaza.size.x) - areaGato.position.x;
        float dy1 = areaTaza.position.y - (areaGato.position.y + areaGato.size.y);
        float dy2 = (areaTaza.position.y + areaTaza.size.y) - areaGato.position.y;

        float dx = (std::abs(dx1) < std::abs(dx2)) ? dx1 : dx2;
        float dy = (std::abs(dy1) < std::abs(dy2)) ? dy1 : dy2;

        if (std::abs(dx) < std::abs(dy))
        {
            _gato.mover({ dx, 0.f });
        }
        else
        {
            _gato.mover({ 0.f, dy });
        }
    }
    else
    {
        _tocandoTaza = false;
    }
}

void Juego::dibujarHitboxes()
{
    if (!_mostrarHitboxes)
    {
        return;
    }

    const sf::FloatRect hitboxGato = _gato.getGlobalBounds();
    sf::RectangleShape rectGato(hitboxGato.size);
    rectGato.setPosition(hitboxGato.position);
    rectGato.setFillColor(sf::Color::Transparent);
    rectGato.setOutlineColor(sf::Color::Green);
    rectGato.setOutlineThickness(2.f);

    const sf::FloatRect hitboxTaza = _taza.getGlobalBounds();
    sf::RectangleShape rectTaza(hitboxTaza.size);
    rectTaza.setPosition(hitboxTaza.position);
    rectTaza.setFillColor(sf::Color::Transparent);
    rectTaza.setOutlineColor(sf::Color::Red);
    rectTaza.setOutlineThickness(2.f);

    _window.draw(rectGato);
    _window.draw(rectTaza);
}
