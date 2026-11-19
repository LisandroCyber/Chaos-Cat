#pragma once

#include <SFML/System.hpp>

//tuve que crear esta clase porque sfml 2.5 no tiene algo para pausar el juego
//esta clase guarda el tiempo que paso antes de la pausa, descarta el tiempo durante la pausa
//y retoma con el tiempo que seguia antes de la pausa

class RelojJuego
{
private:
    sf::Clock _reloj;
    sf::Time _tiempoAcumulado = sf::Time::Zero;
    bool _pausado = true;

public:
    sf::Time getElapsedTime() const;
    sf::Time restart();
    void setPausado(bool pausado);
};
