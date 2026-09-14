#pragma once
#include <SFML/Graphics.hpp>
#include "Mueble.h"
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
    Mueble _heladera;
    Mueble _mesa;
    sf::FloatRect _hitboxCocina;

    bool _tocandoTaza;
    bool _mostrarHitboxes;

    void procesarEventos();
    void actualizar();
    void dibujar();
    void resolverColisionesGato();
    bool resolverColisionGatoTaza();
    bool gatoPuedeApoyarseEn(const sf::FloatRect& superficie);
    void dibujarHitboxes();

public:
    Juego();
    void ejecutar();
};
