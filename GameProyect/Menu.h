#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Menu
{
protected:
    sf::Font _fuente;
    sf::Text _titulo;
    sf::Music _musicaFondo;
    sf::Text _opciones[2];
    int _seleccion = 0;

public:
    Menu();

    int procesarEvento(const sf::Event& evento);
    void dibujar(sf::RenderWindow& ventana);
    void reiniciarSeleccion();
    bool cargarMusicaFondo(const std::string& rutaMusica, float volumen);
};