#include "MenuPausa.h"
#include "Constantes.h"
#include <iostream>
#include <SFML/Audio.hpp>

MenuPausa::MenuPausa()
    : Menu(4)
{
    _titulo.setString("PAUSA");

    _opciones[0].setString("Continuar");
    _opciones[1].setString("Configuracion");
    _opciones[2].setString("Volver al menu principal");
    _opciones[3].setString("Salir");

    const sf::FloatRect limitesTitulo = _titulo.getLocalBounds();
    _titulo.setOrigin(
        limitesTitulo.left + limitesTitulo.width / 2.f,
        limitesTitulo.top + limitesTitulo.height / 2.f);
    _titulo.setPosition(ANCHO_VENTANA / 2.f, 220.f);

    for (int i = 0; i < _cantidadOpciones; i++)
    {
        const sf::FloatRect limites = _opciones[i].getLocalBounds();
        _opciones[i].setOrigin(
            limites.left + limites.width / 2.f,
            limites.top + limites.height / 2.f);
        _opciones[i].setPosition(ANCHO_VENTANA / 2.f, 350.f + i * 70.f);
    }

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

void MenuPausa::setVolumenMusica(float volumen)
{
    _musicaFondo.setVolume(volumen);
}
