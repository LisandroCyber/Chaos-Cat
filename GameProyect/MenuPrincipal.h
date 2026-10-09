#pragma once
#include "Menu.h"
#include <SFML/Audio.hpp>

class MenuPrincipal : public Menu
{
private:
    sf::Texture _texturaFondo;
    sf::Sprite _fondo;
    sf::Music _musicaFondo;

protected:
    void draw(
        sf::RenderTarget& destino,
        sf::RenderStates estados
    ) const override;

public:
    MenuPrincipal();

    void pausarMusica();
    void continuarMusica();
};