#pragma once
#include "Menu.h"

class MenuDerrota : public Menu
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
    MenuDerrota();
    void prepararFondo(const sf::RenderWindow& ventana);
    void reiniciarSeleccion() override;
};
