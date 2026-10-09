#pragma once
#include <SFML/Graphics.hpp>

class Menu : public sf::Drawable
{
protected:
    sf::Font _fuente;
    sf::Text _titulo;
    sf::Text _opciones[2];

    int _seleccion = 0;

    int obtenerOpcionEn(const sf::Vector2f& posicionMouse) const;

    void draw(
        sf::RenderTarget& destino,
        sf::RenderStates estados
    ) const override;

public:
    Menu();
    virtual ~Menu() = default;

    virtual int procesarEvento(
        const sf::Event& evento,
        const sf::RenderWindow& ventana
    );

    virtual void reiniciarSeleccion();
};