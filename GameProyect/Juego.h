#pragma once

#include <SFML/Graphics.hpp>
#include "Nivel.h"
#include "Personaje.h"
#include "MenuPrincipal.h"
#include "MenuPausa.h"
#include "ConfirmacionSalida.h"
#include "MenuDerrota.h"

class Juego
{
private:
    sf::RenderWindow _window;

    Personaje _gato;
    Nivel* _nivel;

    sf::Texture _texturaOjoEscondido;
    sf::Sprite _spriteOjoEscondido;

    MenuPrincipal _menuPrincipal;
    MenuPausa _menuPausa;
    ConfirmacionSalida _menuSalida;
    MenuDerrota _menuDerrota;


    bool _perdio = false;
    bool _enMenu = true;
    bool _enPausa = false;
    bool _confirmarSalida = false;
    bool _partidaPausada = true;

    void procesarEventos();
    void actualizar();
    void actualizarPausaPartida();
    void dibujar();

    void solicitarSalida();
    void cancelarSalida();
    void reiniciarPartida();

public:
    Juego();
    ~Juego();

    void ejecutar();
};
