#include "MenuConfig.h"
#include <iostream>
#include <string>

MenuConfiguracion::MenuConfiguracion(Configuracion& configuracion)
    : _configuracion(configuracion)
{
    if (!_fuente.loadFromFile("fonts/Starcatcher.ttf"))
    {
        std::cout << "ERROR AL CARGAR LA FUENTE\n";
    }

    _titulo.setFont(_fuente);
    _titulo.setString("CONFIGURACION");
    _titulo.setCharacterSize(55);
    _titulo.setPosition(180.f, 90.f);

    const char* etiquetas[4] = {
        "Volumen general",
        "Volumen de musica",
        "Movimiento",
        "Modo debug"
    };

    for (int fila = 0; fila < 4; fila++)
    {
        _etiquetas[fila].setFont(_fuente);
        _etiquetas[fila].setString(etiquetas[fila]);
        _etiquetas[fila].setCharacterSize(30);
        _etiquetas[fila].setPosition(
            180.f,
            220.f + fila * 75.f
        );
    }

    for (int fila = 0; fila < 5; fila++)
    {
        for (int columna = 0; columna < 2; columna++)
        {
            _botones[fila][columna].setFont(_fuente);
            _botones[fila][columna].setCharacterSize(24);
        }
    }

    _botones[0][0].setString("-");
    _botones[0][1].setString("+");

    _botones[1][0].setString("-");
    _botones[1][1].setString("+");

    _botones[2][0].setString("WASD");
    _botones[2][1].setString("Flechas");

    _botones[3][0].setString("Desactivado");
    _botones[3][1].setString("Activado");

    _botones[4][0].setString("Guardar y volver");

    _mensaje.setFont(_fuente);
    _mensaje.setCharacterSize(20);
    _mensaje.setPosition(180.f, 630.f);

    abrir();
}

void MenuConfiguracion::abrir()
{
    _fila = 0;
    _columna = 0;

    _mensaje.setString(
        "Flechas: seleccionar. Enter o click: activar."
    );
}

sf::FloatRect MenuConfiguracion::obtenerAreaBoton(
    int fila,
    int columna) const
{
    if (fila == 4)
    {
        return sf::FloatRect(440.f, 540.f, 400.f, 55.f);
    }

    return sf::FloatRect(
        680.f + columna * 210.f,
        210.f + fila * 75.f,
        190.f,
        55.f
    );
}

bool MenuConfiguracion::seleccionarConMouse(
    const sf::Vector2f& posicion)
{
    for (int fila = 0; fila < 5; fila++)
    {
        const int cantidadBotones = fila == 4 ? 1 : 2;

        for (int columna = 0; columna < cantidadBotones; columna++)
        {
            if (obtenerAreaBoton(fila, columna).contains(
                posicion.x, posicion.y))
            {
                _fila = fila;
                _columna = columna;

                return true;
            }
        }
    }

    return false;
}

bool MenuConfiguracion::activarSeleccion()
{
    const int cambio = _columna == 0 ? -5 : 5;

    if (_fila == 0)
    {
        _configuracion.cambiarVolumenGeneral(cambio);
    }
    else if (_fila == 1)
    {
        _configuracion.cambiarVolumenMusica(cambio);
    }
    else if (_fila == 2)
    {
        _configuracion.setUsarFlechas(_columna == 1);
    }
    else if (_fila == 3)
    {
        _configuracion.setDebug(_columna == 1);
    }
    else if (_fila == 4)
    {
        if (_configuracion.guardar())
        {
            return true;
        }

        _mensaje.setString("No se pudo guardar cfg.dat.");
    }

    return false;
}

bool MenuConfiguracion::procesarEvento(
    const sf::Event& evento,
    const sf::RenderWindow& ventana)
{
    if (evento.type == sf::Event::MouseMoved)
    {
        seleccionarConMouse(
            ventana.mapPixelToCoords(sf::Vector2i(
                evento.mouseMove.x,
                evento.mouseMove.y
            ))
        );
    }

    if (evento.type == sf::Event::MouseButtonPressed &&
        evento.mouseButton.button == sf::Mouse::Left)
    {
        const sf::Vector2f posicion =
            ventana.mapPixelToCoords(sf::Vector2i(
                evento.mouseButton.x,
                evento.mouseButton.y
            ));

        if (seleccionarConMouse(posicion))
        {
            return activarSeleccion();
        }
    }

    if (evento.type == sf::Event::KeyPressed)
    {
        if (evento.key.code == sf::Keyboard::Up)
        {
            _fila = (_fila + 4) % 5;
        }
        else if (evento.key.code == sf::Keyboard::Down)
        {
            _fila = (_fila + 1) % 5;
        }
        else if (evento.key.code == sf::Keyboard::Left)
        {
            _columna = 0;
        }
        else if (evento.key.code == sf::Keyboard::Right)
        {
            _columna = 1;
        }
        else if (evento.key.code == sf::Keyboard::Enter)
        {
            return activarSeleccion();
        }
        else if (evento.key.code == sf::Keyboard::Escape)
        {
            _fila = 4;
            _columna = 0;

            return activarSeleccion();
        }

        if (_fila == 4)
        {
            _columna = 0;
        }
    }

    return false;
}

void MenuConfiguracion::draw(
    sf::RenderTarget& destino,
    sf::RenderStates estados) const
{
    sf::RectangleShape fondo(sf::Vector2f(
        static_cast<float>(destino.getSize().x),
        static_cast<float>(destino.getSize().y)
    ));

    fondo.setFillColor(sf::Color(30, 30, 40));
    destino.draw(fondo, estados);
    destino.draw(_titulo, estados);

    for (int fila = 0; fila < 4; fila++)
    {
        sf::Text etiqueta = _etiquetas[fila];

        if (fila == 0)
        {
            etiqueta.setString(
                "Volumen general: " +
                std::to_string(_configuracion.getVolumenGeneral()) + "%"
            );
        }
        else if (fila == 1)
        {
            etiqueta.setString(
                "Volumen de musica: " +
                std::to_string(_configuracion.getVolumenMusica()) + "%"
            );
        }

        destino.draw(etiqueta, estados);
    }

    for (int fila = 0; fila < 5; fila++)
    {
        const int cantidadBotones = fila == 4 ? 1 : 2;

        for (int columna = 0; columna < cantidadBotones; columna++)
        {
            const sf::FloatRect area =
                obtenerAreaBoton(fila, columna);

            const bool seleccionado =
                fila == _fila && columna == _columna;

            bool elegido = false;

            if (fila == 2)
            {
                elegido =
                    _configuracion.usaFlechas() == (columna == 1);
            }
            else if (fila == 3)
            {
                elegido =
                    _configuracion.debugActivado() == (columna == 1);
            }

            sf::RectangleShape boton(
                sf::Vector2f(area.width, area.height)
            );

            boton.setPosition(area.left, area.top);
            boton.setFillColor(
                elegido
                ? sf::Color(40, 100, 65)
                : sf::Color(55, 55, 70)
            );

            boton.setOutlineThickness(2.f);
            boton.setOutlineColor(
                seleccionado ? sf::Color::Yellow : sf::Color::White
            );

            destino.draw(boton, estados);

            sf::Text texto = _botones[fila][columna];
            const sf::FloatRect limites = texto.getLocalBounds();

            texto.setOrigin(
                limites.left + limites.width / 2.f,
                limites.top + limites.height / 2.f
            );

            texto.setPosition(
                area.left + area.width / 2.f,
                area.top + area.height / 2.f
            );

            destino.draw(texto, estados);
        }
    }

    destino.draw(_mensaje, estados);
}