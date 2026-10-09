#include "Juego.h"
#include "Constantes.h"
#include "NivelCocina.h"
#include <iostream>

Juego::Juego()
    : _window(
        sf::VideoMode(ANCHO_VENTANA, ALTO_VENTANA),
        "Chaos Cat SFML 2.5"
    ),
    _gato(),
    _nivel(new NivelCocina())
{
    _window.setFramerateLimit(LIMITE_FPS);
    _window.setKeyRepeatEnabled(false);

    _nivel->pausarMusica();
    _menuPrincipal.continuarMusica();
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

        if (!_window.isOpen())
        {
            break;
        }

        actualizar();
        dibujar();
    }
}

void Juego::solicitarSalida()
{
    _confirmarSalida = true;
    _menuSalida.reiniciarSeleccion();

    _menuPrincipal.pausarMusica();
    _menuPausa.pausarMusica();
    _nivel->pausarMusica();
}

void Juego::cancelarSalida()
{
    _confirmarSalida = false;

    if (_enMenu)
    {
        _menuPrincipal.continuarMusica();
    }
    else if (_enPausa)
    {
        _menuPausa.continuarMusica();
    }
    else
    {
        _nivel->continuarMusica();
    }
}

void Juego::procesarEventos()
{
    sf::Event evento;

    while (_window.pollEvent(evento))
    {
        if (evento.type == sf::Event::Closed)
        {
            solicitarSalida();
            continue;
        }

        // La confirmacion tiene prioridad sobre los otros menus.
        if (_confirmarSalida)
        {
            const int opcion =
                _menuSalida.procesarEvento(evento, _window);

            if (opcion == 0)
            {
                _window.close();
                return;
            }
            else if (opcion == 1)
            {
                cancelarSalida();
            }

            continue;
        }

        if (_enMenu)
        {
            const int opcion =
                _menuPrincipal.procesarEvento(evento, _window);

            if (opcion == 0)
            {
                _enMenu = false;

                _menuPrincipal.pausarMusica();
                _nivel->continuarMusica();
            }
            else if (opcion == 1)
            {
                solicitarSalida();
            }

            continue;
        }

        if (evento.type == sf::Event::KeyPressed &&
            evento.key.code == sf::Keyboard::Escape)
        {
            _enPausa = !_enPausa;

            if (_enPausa)
            {
                _menuPausa.reiniciarSeleccion();

                _nivel->pausarMusica();
                _menuPausa.continuarMusica();
            }
            else
            {
                _menuPausa.pausarMusica();
                _nivel->continuarMusica();
            }

            continue;
        }

        if (_enPausa)
        {
            const int opcion =
                _menuPausa.procesarEvento(evento, _window);

            if (opcion == 0)
            {
                _enPausa = false;

                _menuPausa.pausarMusica();
                _nivel->continuarMusica();
            }
            else if (opcion == 1)
            {
                solicitarSalida();
            }
        }
    }
}

void Juego::actualizar()
{
    if (_enMenu || _enPausa || _confirmarSalida)
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
        std::cout << "Posicion en x: "
            << _gato.getPosx() << std::endl;

        std::cout << "Posicion en y: "
            << _gato.getPosy() << std::endl;
    }
}

void Juego::dibujar()
{
    _window.clear(sf::Color(30, 30, 40));

    if (_enMenu)
    {
        _window.draw(_menuPrincipal);
    }
    else
    {
        // La partida permanece visible detras de la pausa.
        _nivel->dibujar(_window, _gato);

        if (_enPausa)
        {
            _window.draw(_menuPausa);
        }
    }

    if (_confirmarSalida)
    {
        _window.draw(_menuSalida);
    }

    _window.display();
}