#include "MenuPrincipal.h"
#include <algorithm>
#include <iostream>

MenuPrincipal::MenuPrincipal()
    : Menu(4)
{
    _titulo.setString("CHAOS CAT");

    _opciones[0].setString("Jugar");
    _opciones[1].setString("Tutorial");
    _opciones[2].setString("Configuracion");
    _opciones[3].setString("Salir");


    if (!_texturaFondo.loadFromFile("images/UI/MenuPrincipal.png"))
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
    const sf::Vector2u tamanioVentana = destino.getSize();

    //Licha, aca cambie un poco la imagen para que mantenga las proporciones al agrandarlo
    if (tamanio.x > 0 && tamanio.y > 0 &&
        tamanioVentana.x > 0 && tamanioVentana.y > 0)
    {
        const sf::View vistaAnterior = destino.getView();
        const sf::Vector2f area(
            static_cast<float>(tamanioVentana.x),
            static_cast<float>(tamanioVentana.y));

        // El fondo usa pixeles para evitar la segunda escala de la vista fija.
        destino.setView(sf::View(sf::FloatRect(0.f, 0.f, area.x, area.y)));

        const float escala = std::max(
            area.x / tamanio.x,
            area.y / tamanio.y);

        sf::Sprite fondo = _fondo;
        fondo.setOrigin(tamanio.x / 2.f, tamanio.y / 2.f);
        fondo.setPosition(area.x / 2.f, area.y / 2.f);
        fondo.setScale(escala, escala);
        destino.draw(fondo, estados);

        destino.setView(vistaAnterior);
    }

    Menu::draw(destino, estados);
}

void MenuPrincipal::setVolumenMusica(float volumen)
{
    _musicaFondo.setVolume(volumen);
}
