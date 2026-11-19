#pragma once
#include "Menu.h"

class ConfirmacionSalida : public Menu
{
private:
    void acomodarTextos(
        sf::Text& titulo,
        sf::Text* opciones,
        const sf::RenderTarget& destino
    ) const;

protected:
    void draw(
        sf::RenderTarget& destino,
        sf::RenderStates estados
    ) const override;

public:
    ConfirmacionSalida();

    void reiniciarSeleccion() override;

    int procesarEvento(
        const sf::Event& evento,
        const sf::RenderWindow& ventana
    ) override;
};
