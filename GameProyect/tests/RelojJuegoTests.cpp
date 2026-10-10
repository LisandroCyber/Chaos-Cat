#include "../RelojJuego.h"

#include <cassert>
#include <iostream>

int main()
{
    RelojJuego reloj;

    // Esperar en el menu principal no consume tiempo de partida.
    sf::sleep(sf::milliseconds(40));
    assert(reloj.getElapsedTime() == sf::Time::Zero);

    reloj.setPausado(false);
    sf::sleep(sf::milliseconds(30));
    reloj.setPausado(true);
    const sf::Time antesDePausar = reloj.getElapsedTime();
    assert(antesDePausar > sf::Time::Zero);

    sf::sleep(sf::milliseconds(60));
    assert(reloj.getElapsedTime() == antesDePausar);

    // Abrir o cancelar la salida desde pausa debe mantenerlo congelado.
    reloj.setPausado(true);
    sf::sleep(sf::milliseconds(40));
    assert(reloj.getElapsedTime() == antesDePausar);

    sf::Clock referencia;
    reloj.setPausado(false);
    sf::sleep(sf::milliseconds(30));
    const sf::Time tiempoReanudado = reloj.getElapsedTime() - antesDePausar;
    assert(tiempoReanudado > sf::Time::Zero);
    assert(tiempoReanudado <= referencia.getElapsedTime());

    // Reanudar dos veces no reinicia ni pierde lo acumulado.
    const sf::Time antesDeReanudarOtraVez = reloj.getElapsedTime();
    reloj.setPausado(false);
    assert(reloj.getElapsedTime() >= antesDeReanudarOtraVez);

    referencia.restart();
    const sf::Time antesDeReiniciar = reloj.restart();
    assert(antesDeReiniciar >= antesDeReanudarOtraVez);
    assert(reloj.getElapsedTime() <= referencia.getElapsedTime());
    sf::sleep(sf::milliseconds(20));
    assert(reloj.getElapsedTime() > sf::Time::Zero);

    // Reiniciar en derrota deja el reloj en cero y todavia pausado.
    reloj.setPausado(true);
    const sf::Time antesDeReintentar = reloj.getElapsedTime();
    assert(reloj.restart() == antesDeReintentar);
    sf::sleep(sf::milliseconds(30));
    assert(reloj.getElapsedTime() == sf::Time::Zero);

    reloj.setPausado(false);
    sf::sleep(sf::milliseconds(20));
    assert(reloj.getElapsedTime() > sf::Time::Zero);

    // Cada animacion tiene su acumulador independiente.
    RelojJuego otroReloj;
    assert(otroReloj.getElapsedTime() == sf::Time::Zero);
    const sf::Time antesDeOtroReinicio = reloj.getElapsedTime();
    otroReloj.restart();
    assert(reloj.getElapsedTime() >= antesDeOtroReinicio);

    std::cout << "OK: inicio, pausa, pausa repetida, reanudacion y reinicio.\n";
}
