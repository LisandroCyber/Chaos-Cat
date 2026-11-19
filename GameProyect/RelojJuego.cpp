#include "RelojJuego.h"

sf::Time RelojJuego::getElapsedTime() const
{
    if (_pausado)
    {
        return _tiempoAcumulado;
    }

    return _tiempoAcumulado + _reloj.getElapsedTime();
}

sf::Time RelojJuego::restart()
{
    const sf::Time transcurrido = getElapsedTime();
    _tiempoAcumulado = sf::Time::Zero;
    _reloj.restart();

    // Reiniciar no cambia si el reloj esta pausado o en marcha.
    return transcurrido;
}

void RelojJuego::setPausado(bool pausado)
{
    if (_pausado == pausado)
    {
        return;
    }

    if (pausado)
    {
        _tiempoAcumulado += _reloj.getElapsedTime();
    }
    else
    {
        _reloj.restart();
    }

    _pausado = pausado;
}
