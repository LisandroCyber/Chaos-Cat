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

    if (!cargarMusicaFondo("music/cancion_pantalla_principal.wav", 3.f))
    {
        std::cout << "ERROR AL CARGAR LA MUSICA\n";
    }
}

void MenuPrincipal::dibujar(sf::RenderWindow& ventana)
{
    const sf::Vector2u tamanio = _texturaFondo.getSize();

    if (tamanio.x > 0 && tamanio.y > 0)
    {
        // Ajustar la imagen al tamaño de la ventana.
        _fondo.setScale(
            static_cast<float>(ventana.getSize().x) / tamanio.x,
            static_cast<float>(ventana.getSize().y) / tamanio.y
        );

        ventana.draw(_fondo);
    }

    // Dibujar el título y las opciones sobre la imagen.
    Menu::dibujar(ventana);
}