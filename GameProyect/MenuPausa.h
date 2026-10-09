#pragma once
#include "Menu.h"
#include <SFML/Audio.hpp>

class MenuPausa : public Menu
{
private:
    sf::Music _musicaFondo;
protected:
    void draw(
        sf::RenderTarget& destino,
        sf::RenderStates estados
    ) const override;

public:
    MenuPausa();

    void continuarMusica();
    void pausarMusica();
};