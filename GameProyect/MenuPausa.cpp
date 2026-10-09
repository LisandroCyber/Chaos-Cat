#include "MenuPausa.h"
#include <iostream>
#include <SFML/Audio.hpp>

MenuPausa::MenuPausa()
{
    _titulo.setString("PAUSA");
    _opciones[0].setString("Continuar");

    if (!_musicaFondo.openFromFile("music/MenuPausa/LoopMenuPausa.wav"))
    {
        std::cout << "ERROR AL CARGAR LA MUSICA DE PAUSA\n";
    }
    else
    {
        _musicaFondo.setVolume(20.f);
        _musicaFondo.setLoop(true);
    }
}

void MenuPausa::draw(
    sf::RenderTarget& destino,
    sf::RenderStates estados) const
{
    sf::RectangleShape fondo(sf::Vector2f(
        static_cast<float>(destino.getSize().x),
        static_cast<float>(destino.getSize().y)
    ));

    fondo.setFillColor(sf::Color(0, 0, 0, 180));

    destino.draw(fondo, estados);
    Menu::draw(destino, estados);
}

void MenuPausa::continuarMusica()
{
    if (_musicaFondo.getStatus() != sf::Music::Playing)
    {
        _musicaFondo.play();
    }
}

void MenuPausa::pausarMusica()
{
    _musicaFondo.pause();
}