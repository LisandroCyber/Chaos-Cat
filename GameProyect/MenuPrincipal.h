#pragma once
#include "Menu.h"

class MenuPrincipal : public Menu
{
private:
    sf::Texture _texturaFondo;
    sf::Sprite _fondo;

public:
    MenuPrincipal();
    void dibujar(sf::RenderWindow& ventana);
};