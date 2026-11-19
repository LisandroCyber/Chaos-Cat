#pragma once
#include "Menu.h"

class TablaPuntos : public Menu
{
public:
    TablaPuntos();
    void registrar(int puntos);

protected:
    void draw(sf::RenderTarget& destino,
        sf::RenderStates estados) const override;

private:
    static constexpr int CANTIDAD = 5;
    int _mejores[CANTIDAD]{};
    sf::Texture _texturaFondo;
    sf::Sprite _fondo;
};