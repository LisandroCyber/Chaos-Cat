#include "Menu.h"
#include <iostream>

Menu::Menu()
{
    if (!_fuente.loadFromFile("fonts/starcatcher.ttf"))
    {
        std::cout << "ERROR AL CARGAR LA FUENTE\n";
    }

    _titulo.setFont(_fuente);
    _titulo.setCharacterSize(80);
    _titulo.setPosition(440.f, 180.f);

    for (int i = 0; i < 2; i++)
    {
        _opciones[i].setFont(_fuente);
        _opciones[i].setCharacterSize(36);
        _opciones[i].setPosition(550.f, 350.f + i * 70.f);
    }

    _opciones[1].setString("Salir");
}

int Menu::procesarEvento(const sf::Event& evento, const sf::RenderWindow& ventana)
{
    //verifica si el mouse se mueve dentro de la pantalla
    if (evento.type == sf::Event::MouseMoved)
    {
        const sf::Vector2f posicionMouse =
            ventana.mapPixelToCoords(sf::Vector2i(
                evento.mouseMove.x,
                evento.mouseMove.y
            ));

        const int opcion = obtenerOpcionEn(posicionMouse);

        if (opcion != -1)
        {
            _seleccion = opcion;
        }
    }

    if (evento.type == sf::Event::MouseButtonPressed &&
        evento.mouseButton.button == sf::Mouse::Left)
    {
        const sf::Vector2f posicionMouse =
            ventana.mapPixelToCoords(sf::Vector2i(
                evento.mouseButton.x,
                evento.mouseButton.y
            ));

        return obtenerOpcionEn(posicionMouse);
    }

    if (evento.type == sf::Event::KeyPressed)
    {
        if (evento.key.code == sf::Keyboard::Up ||
            evento.key.code == sf::Keyboard::Down)
        {
            _seleccion = 1 - _seleccion;
        }

        if (evento.key.code == sf::Keyboard::Enter)
        {
            return _seleccion;
        }
    }

    return -1;
}

void Menu::dibujar(sf::RenderWindow& ventana)
{
    ventana.draw(_titulo);

    for (int i = 0; i < 2; i++)
    {
        _opciones[i].setFillColor(
            i == _seleccion ? sf::Color::Yellow : sf::Color::White
        );

        ventana.draw(_opciones[i]);
    }
}

void Menu::reiniciarSeleccion()
{
    _seleccion = 0;
}

bool Menu::cargarMusicaFondo(const std::string& rutaMusica, float volumen)
{
    if (!_musicaFondo.openFromFile(rutaMusica))
    {
        return false;
    }

    _musicaFondo.setVolume(volumen);
    _musicaFondo.setLoop(true);
    _musicaFondo.play();

    return true;
}

//recorre las opciones y verifica si el mouse esta sobre uno de ellos o no
int Menu::obtenerOpcionEn(
    const sf::Vector2f& posicionMouse) const
{
    for (int i = 0; i < 2; i++)
    {
        if (_opciones[i].getGlobalBounds().contains(
            posicionMouse.x, posicionMouse.y))
        {
            return i;
        }
    }

    return -1;
}
