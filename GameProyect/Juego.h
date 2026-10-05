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
    sf::Text _opcionesSalida[2];//guardo los textos como atributos para poder seleccionarlos

    void dibujarConfirmacion();

    void procesarEventos();
    void actualizar();
    void dibujar();

    void actualizarOpcionesSalida();
    int obtenerOpcionSalidaEn(
        const sf::Vector2f& posicionMouse) const;

public:
    Juego();
    ~Juego();
    void ejecutar();
};
