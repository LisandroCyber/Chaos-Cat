#pragma once

#include <SFML/Graphics.hpp>
#include "Nivel.h"
#include "Personaje.h"
#include "MenuPrincipal.h"
#include "MenuPausa.h"

class Juego
{
private:
    sf::RenderWindow _window;

    Personaje _gato;
    Nivel* _nivel;
    MenuPrincipal _menuPrincipal;
    MenuPausa _menuPausa;

    bool _enMenu = true;
    bool _enPausa = false;

    void procesarEventos();
    void actualizar();
    void dibujar();

public:
    Juego();
    ~Juego();
    void ejecutar();
};
