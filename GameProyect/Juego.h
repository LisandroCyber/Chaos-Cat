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
    bool _confirmarSalida = false;
    int _opcionSalida = 1; // Empieza seleccionado "No".
    sf::Font _fuenteConfirmacion;

    void dibujarConfirmacion();

    void procesarEventos();
    void actualizar();
    void dibujar();

public:
    Juego();
    ~Juego();
    void ejecutar();
};
