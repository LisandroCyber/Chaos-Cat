#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
protected:
    sf::Font _fuente;
    sf::Text _titulo;
    sf::Text _opciones[2];
    int _seleccion = 0;

public:
    Menu();

    int procesarEvento(const sf::Event& evento);
    void dibujar(sf::RenderWindow& ventana);
    void reiniciarSeleccion();
};