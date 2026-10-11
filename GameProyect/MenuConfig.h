#pragma once

#include <SFML/Graphics.hpp>
#include "Configuracion.h"

class MenuConfiguracion : public sf::Drawable
{
private:
    Configuracion& _configuracion;

    sf::Font _fuente;
    sf::Text _titulo;
    sf::Text _etiquetas[4];
    sf::Text _botones[5][2];
    sf::Text _mensaje;

    int _fila = 0;
    int _columna = 0;

    sf::FloatRect obtenerAreaBoton(int fila, int columna) const;
    bool seleccionarConMouse(const sf::Vector2f& posicion);
    bool activarSeleccion();

    void draw(
        sf::RenderTarget& destino,
        sf::RenderStates estados
    ) const override;

public:
    MenuConfiguracion(Configuracion& configuracion);

    void abrir();

    // Devuelve true cuando se guarda y se debe volver.
    bool procesarEvento(
        const sf::Event& evento,
        const sf::RenderWindow& ventana
    );
};