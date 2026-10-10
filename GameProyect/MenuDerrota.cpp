#include "MenuDerrota.h"

MenuDerrota::MenuDerrota()
{
    _titulo.setString("TE DESCUBRIERON!");
    _titulo.setCharacterSize(55);
    _titulo.setPosition(420.f, 180.f);

    _opciones[0].setString("Reintentar");
    _opciones[1].setString("Salir");
}

void MenuDerrota::draw(
    sf::RenderTarget& destino,
    sf::RenderStates estados) const
{
    sf::RectangleShape fondo(sf::Vector2f(
        static_cast<float>(destino.getSize().x),
        static_cast<float>(destino.getSize().y)
    ));

    fondo.setFillColor(sf::Color(0, 0, 0, 200));

    destino.draw(fondo, estados);
    Menu::draw(destino, estados);
}