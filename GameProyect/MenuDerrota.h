#pragma once
#include "Menu.h"

class MenuDerrota : public Menu
{
protected:
    void draw(
        sf::RenderTarget& destino,
        sf::RenderStates estados
    ) const override;

public:
    MenuDerrota();
};
