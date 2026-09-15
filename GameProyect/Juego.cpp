#include "Juego.h"
#include "Constantes.h"
#include "NivelCocina.h"
#include <iostream>

Juego::Juego()
    : _window(sf::VideoMode({ ANCHO_VENTANA, ALTO_VENTANA }), "Chaos Cat SFML 3"),
      _gato(),
      _nivel(new NivelCocina())
{
    _window.setFramerateLimit(LIMITE_FPS);
}

Juego::~Juego()
{
    delete _nivel;
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
    _nivel->actualizar(_gato);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
    {
        _nivel->reiniciarObjetos();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
    {
        std::cout << "Posision en x: " << _gato.getPosx() << std::endl;
        std::cout << "Posision en y: " << _gato.getPosy() << std::endl;
    }
}

void Juego::dibujar()
{
    _window.clear();
    _nivel->dibujar(_window, _gato);
    _window.display();
}
