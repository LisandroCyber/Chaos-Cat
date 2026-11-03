#pragma once
#include "Menu.h"

class MenuVictoria : public Menu
{
private:
    sf::Texture _texturaGato;
    sf::Sprite _spriteGato;
    sf::Text _mensajeInfinito;
    sf::RenderTexture _fondoDesenfocado;
    sf::Shader _shaderDesenfoque;
    bool _shaderDisponible = false;
    bool _fondoPreparado = false;
    bool _victoriaFinal = false;

    static void centrarTexto(sf::Text& texto, float x, float y);

protected:
    void draw(
        sf::RenderTarget& destino,
        sf::RenderStates estados
    ) const override;

public:
    MenuVictoria();
    void configurarVictoriaFinal(bool victoriaFinal);
    void prepararFondo(const sf::RenderWindow& ventana);
    void reiniciarSeleccion() override;
};
