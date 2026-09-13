#pragma once
#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include "ObjetoChico.h"

class Juego
{
private:
    sf::RenderWindow _window;
    sf::Texture _texturaFondo;
    sf::Sprite _spriteFondo;

    Personaje _gato;
    ObjetoChico _taza;

    bool _tocandoTaza;
    bool _mostrarHitboxes;

    void procesarEventos();
    void actualizar();
    void dibujar();
    void resolverColisionGatoTaza();
    void dibujarHitboxes();

public:
    Juego();
    void ejecutar();
};
