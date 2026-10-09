#pragma once

#include <SFML/Graphics.hpp>
#include "Nivel.h"
#include "Personaje.h"
#include "MenuPrincipal.h"
#include "MenuPausa.h"
#include "ConfirmacionSalida.h"

class Juego
{
private:
    sf::RenderWindow _window;

    Personaje _gato;
    Nivel* _nivel;

    MenuPrincipal _menuPrincipal;
    MenuPausa _menuPausa;
    ConfirmacionSalida _menuSalida;

    bool _enMenu = true;
    bool _enPausa = false;
    bool _confirmarSalida = false;

    void procesarEventos();
    void actualizar();
    void dibujar();

    void solicitarSalida();
    void cancelarSalida();

public:
    Juego();
    ~Juego();

    void ejecutar();
};
