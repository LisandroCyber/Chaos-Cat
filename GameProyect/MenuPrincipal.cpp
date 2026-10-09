#include "MenuPrincipal.h"
#include <iostream>

MenuPrincipal::MenuPrincipal()
{
    _titulo.setString("CHAOS CAT");
    _opciones[0].setString("Jugar");

    if (!_texturaFondo.loadFromFile("images/MenuPrincipal.png"))
    {
        std::cout << "ERROR AL CARGAR EL FONDO DEL MENU\n";
    }
    else
    {
        _fondo.setTexture(_texturaFondo);
    }

    if (!_musicaFondo.openFromFile(
        "music/MenuPrincipal/LoopMenuPrincipal.wav"))
    {
        std::cout << "ERROR AL CARGAR LA MUSICA DEL MENU\n";
    }
    else
    {
        _musicaFondo.setVolume(25.f);
        _musicaFondo.setLoop(true);
    }
}

void MenuPrincipal::pausarMusica()
{
    _musicaFondo.pause();
}

void MenuPrincipal::continuarMusica()
{
    if (_musicaFondo.getStatus() != sf::Music::Playing)
    {
        _musicaFondo.play();
    }
}

void MenuPrincipal::draw(
    sf::RenderTarget& destino,
    sf::RenderStates estados) const
{
    const sf::Vector2u tamanio = _texturaFondo.getSize();

    if (tamanio.x > 0 && tamanio.y > 0)
    {
        sf::Sprite fondo = _fondo;

        fondo.setScale(
            static_cast<float>(destino.getSize().x) / tamanio.x,
            static_cast<float>(destino.getSize().y) / tamanio.y
        );

        destino.draw(fondo, estados);
    }

    Menu::draw(destino, estados);
}