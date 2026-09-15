#pragma once

#include <SFML/Graphics.hpp>
#include "Nivel.h"
#include "Personaje.h"

class Juego
{
private:
    sf::RenderWindow _window;

    Personaje _gato;
    Nivel* _nivel;

    void procesarEventos();
    void actualizar();
    void dibujar();

public:
    Juego();
    ~Juego();
    void ejecutar();
};
