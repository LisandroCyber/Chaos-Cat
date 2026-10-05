#include "Juego.h"
#include "Constantes.h"
#include "NivelCocina.h"
#include <iostream>
#include <stdexcept>

Juego::Juego()
    : _window(sf::VideoMode(ANCHO_VENTANA, ALTO_VENTANA), "Chaos Cat SFML 2.5"),
    _gato(),
    _nivel(new NivelCocina())
{
    _window.setFramerateLimit(LIMITE_FPS);
    _window.setKeyRepeatEnabled(false);
    _nivel->pausarMusica();
    _fuenteConfirmacion.loadFromFile("fonts/starcatcher.ttf");

    for (int i = 0; i < 2; i++)
    {
        _opcionesSalida[i].setFont(_fuenteConfirmacion);
        _opcionesSalida[i].setString(i == 0 ? "Si" : "No");
        _opcionesSalida[i].setCharacterSize(30);
    }
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
        // También confirmar cuando se presiona la X.
        if (evento.type == sf::Event::Closed)
        {
            _confirmarSalida = true;
            _opcionSalida = 1;
            _nivel->pausarMusica();
            continue;
        }

        if (_confirmarSalida)
        {
            actualizarOpcionesSalida();

            if (evento.type == sf::Event::MouseMoved)
            {
                const sf::Vector2f posicionMouse =
                    _window.mapPixelToCoords(sf::Vector2i(
                        evento.mouseMove.x,
                        evento.mouseMove.y
                    ));

                const int opcion = obtenerOpcionSalidaEn(posicionMouse);

                if (opcion != -1)
                {
                    _opcionSalida = opcion;
                }
            }

            if (evento.type == sf::Event::MouseButtonPressed &&
                evento.mouseButton.button == sf::Mouse::Left)
            {
                const sf::Vector2f posicionMouse =
                    _window.mapPixelToCoords(sf::Vector2i(
                        evento.mouseButton.x,
                        evento.mouseButton.y
                    ));

                const int opcion = obtenerOpcionSalidaEn(posicionMouse);

                if (opcion == 0)
                {
                    _window.close();
                }
                else if (opcion == 1)
                {
                    _confirmarSalida = false;

                    if (!_enMenu && !_enPausa)
                    {
                        _nivel->continuarMusica();
                    }
                }
            }

            if (evento.type == sf::Event::KeyPressed)
            {
                if (evento.key.code == sf::Keyboard::Left ||
                    evento.key.code == sf::Keyboard::Right)
                {
                    _opcionSalida = 1 - _opcionSalida;
                }

                if (evento.key.code == sf::Keyboard::Escape)
                {
                    _confirmarSalida = false;

                    if (!_enMenu && !_enPausa)
                    {
                        _nivel->continuarMusica();
                    }
                }
                else if (evento.key.code == sf::Keyboard::Enter)
                {
                    if (_opcionSalida == 0)
                    {
                        _window.close();
                    }
                    else
                    {
                        _confirmarSalida = false;

                        if (!_enMenu && !_enPausa)
                        {
                            _nivel->continuarMusica();
                        }
                    }
                }
            }

            continue;
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
            opcion = _menuPrincipal.procesarEvento(evento, _window);
        }
        else if (_enPausa)
        {
            opcion = _menuPausa.procesarEvento(evento, _window);
        }

        if (opcion == 0)
        {
            _enMenu = false;
            _enPausa = false;
            _nivel->continuarMusica();
        }
        else if (opcion == 1)
        {
            _confirmarSalida = true;
            _opcionSalida = 1;
            _nivel->pausarMusica();
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

    if (_confirmarSalida)
    {
        dibujarConfirmacion();
    }

    _window.display();
}

void Juego::dibujarConfirmacion()
{
    const float ancho = static_cast<float>(_window.getSize().x);
    const float alto = static_cast<float>(_window.getSize().y);

    sf::RectangleShape fondo(sf::Vector2f(ancho, alto));
    fondo.setFillColor(sf::Color(0, 0, 0, 180));
    _window.draw(fondo);

    sf::RectangleShape cuadro(sf::Vector2f(500.f, 220.f));
    cuadro.setPosition(ancho / 2.f - 250.f, alto / 2.f - 110.f);
    cuadro.setFillColor(sf::Color(40, 40, 55));
    cuadro.setOutlineThickness(2.f);
    cuadro.setOutlineColor(sf::Color::White);
    _window.draw(cuadro);

    sf::Text pregunta;
    pregunta.setFont(_fuenteConfirmacion);
    pregunta.setString("Salir del juego?");
    pregunta.setCharacterSize(32);

    sf::FloatRect area = pregunta.getLocalBounds();
    pregunta.setOrigin(area.left + area.width / 2.f, area.top);
    pregunta.setPosition(ancho / 2.f, alto / 2.f - 65.f);
    _window.draw(pregunta);

    actualizarOpcionesSalida();

    for (int i = 0; i < 2; i++)
    {
        _window.draw(_opcionesSalida[i]);
    }
}

void Juego::actualizarOpcionesSalida()
{
    const float ancho = static_cast<float>(_window.getSize().x);
    const float alto = static_cast<float>(_window.getSize().y);

    for (int i = 0; i < 2; i++)
    {
        sf::FloatRect area = _opcionesSalida[i].getLocalBounds();

        _opcionesSalida[i].setOrigin(
            area.left + area.width / 2.f,
            area.top
        );

        _opcionesSalida[i].setPosition(
            ancho / 2.f + (i == 0 ? -100.f : 100.f),
            alto / 2.f + 30.f
        );

        _opcionesSalida[i].setFillColor(
            i == _opcionSalida ? sf::Color::Yellow : sf::Color::White
        );
    }
}

int Juego::obtenerOpcionSalidaEn(
    const sf::Vector2f& posicionMouse) const
{
    for (int i = 0; i < 2; i++)
    {
        if (_opcionesSalida[i].getGlobalBounds().contains(
            posicionMouse.x, posicionMouse.y))
        {
            return i;
        }
    }

    return -1;
}