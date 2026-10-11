#pragma once
#include "Menu.h"

class MenuVictoria : public Menu
{
private:
    sf::Texture _texturaGato;
    sf::Sprite _spriteGato;
    sf::RenderTexture _fondoDesenfocado;
    sf::Shader _shaderDesenfoque;
    bool _shaderDisponible = false;
    bool _fondoPreparado = false;

protected:
    void draw(
        sf::RenderTarget& destino,
        sf::RenderStates estados
    ) const override;

public:
    MenuVictoria();
    void prepararFondo(const sf::RenderWindow& ventana);
    void reiniciarSeleccion() override;
};
