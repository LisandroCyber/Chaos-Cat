#include "Juego.h"
#include "Constantes.h"
#include "NivelCocina.h"
#include <iostream>

Juego::Juego()
    : _window(sf::VideoMode(ANCHO_VENTANA, ALTO_VENTANA), "Chaos Cat SFML 2.5"),
      _gato(),
      _nivel(new NivelCocina())
{
    _window.setFramerateLimit(LIMITE_FPS);
    _window.setKeyRepeatEnabled(false);
    _nivel->pausarMusica();
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
    sf::Event evento;

    while (_window.pollEvent(evento))
    {
        if (evento.type == sf::Event::Closed)
        {
            _window.close();
        }

        if (!_enMenu &&
            evento.type == sf::Event::KeyPressed &&
            evento.key.code == sf::Keyboard::Escape)
        {
            _enPausa = !_enPausa;
            _menuPausa.reiniciarSeleccion();

            if (_enPausa)
            {
                _nivel->pausarMusica();
            }
            else
            {
                _nivel->continuarMusica();
            }

            continue;
        }

        int opcion = -1;

        if (_enMenu)
        {
            opcion = _menuPrincipal.procesarEvento(evento);
        }
        else if (_enPausa)
        {
            opcion = _menuPausa.procesarEvento(evento);
        }

        if (opcion == 0)
        {
            _enMenu = false;
            _enPausa = false;
            _nivel->continuarMusica();
        }
        else if (opcion == 1)
        {
            _nivel->pausarMusica();
            _window.close();
        }
    }
}

void Juego::actualizar()
{
    if (_enMenu || _enPausa)
    {
        return;
    }
    _gato.update();
    _nivel->actualizar(_gato);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        _nivel->reiniciarObjetos();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
    {
        std::cout << "Posision en x: " << _gato.getPosx() << std::endl;
        std::cout << "Posision en y: " << _gato.getPosy() << std::endl;
    }
}

void Juego::dibujar()
{
    _window.clear(sf::Color(30, 30, 40));

    if (_enMenu)
    {
        _menuPrincipal.dibujar(_window);
    }
    else
    {
        // La partida queda visible detrás de la pausa.
        _nivel->dibujar(_window, _gato);

        if (_enPausa)
        {
            sf::RectangleShape fondo(
                sf::Vector2f(
                    static_cast<float>(_window.getSize().x),
                    static_cast<float>(_window.getSize().y)
                )
            );

            fondo.setFillColor(sf::Color(0, 0, 0, 180));
            _window.draw(fondo);

            _menuPausa.dibujar(_window);
        }
    }

    _window.display();
}
