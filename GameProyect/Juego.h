#pragma once

#include <SFML/Graphics.hpp>
#include "Nivel.h"
#include "Personaje.h"
#include "MenuPrincipal.h"
#include "MenuPausa.h"
#include "ConfirmacionSalida.h"
#include "MenuDerrota.h"
#include "Configuracion.h"
#include "MenuConfig.h"

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
    Configuracion _configuracion;
    MenuConfiguracion _menuConfiguracion;
    MenuDerrota _menuDerrota;
    ConfirmacionSalida _menuSalida;

    bool _enConfiguracion = false;
    bool _perdio = false;
    bool _enMenu = true;
    bool _enPausa = false;
    bool _confirmarSalida = false;
    bool _partidaPausada = true;

    void aplicarConfiguracion();
    void procesarEventos();
    void actualizar();
    void actualizarPausaPartida();
    void dibujar();
    void volverAlMenuPrincipal();

    void solicitarSalida();
    void cancelarSalida();
    void reiniciarPartida();

public:
    Juego();
    ~Juego();

    void ejecutar();
};
