#include "NivelCocina.h"
#include <iostream>

NivelCocina::NivelCocina()
{
    cargarFondo("images/1-Cocina/cocina.png");

    if (!cargarMusicaFondo("music/EnPartida/LoopNivelCocina.wav", 2.f))
    {
        std::cout << "ERROR AL CARGAR LA MUSICA\n";
    }
    reproducirMusicaFondo(sf::Time::Zero);

    agregarEnemigo("images/frames_enemigo.png",
        { 672.f, 664.f },
        600,
        724,
        { 0.7f, 0.82f });

    agregarMueble("images/1-Cocina/heladera.png",
        { 3.f, 300.f },
        { 0.25f, 0.272f },
        sf::FloatRect(185.f, 70.f, 585.f, 100.f));

    agregarMueble("images/1-Cocina/mesa-larga.png",
        { 396.06f, 400.f },
        { 0.280825f, 0.384588f },
        sf::FloatRect(47.f, 320.f, 1442.f, 100.f));

    agregarObjeto("images/1-Cocina/TazaCafe.png", { 505.f, 480.f }, 0.25f);
    agregarObjeto("images/1-Cocina/frutero.png", { 640.f, 450.f }, 0.15f);
    agregarObjeto("images/1-Cocina/cacerola.png", { 1139.f, 405.f }, 0.50f);
    agregarObjeto("images/1-Cocina/platos.png", { 75.f, 235.f }, 0.08f);

    agregarSuperficie(sf::FloatRect(1090.f, 490.f, 250.f, 50.f)); // superficie Horno

    agregarZonaEscondite(sf::FloatRect(0.f, 520.f, 145.f, 235.f)); // zona escondite heladera
    agregarZonaEscondite(sf::FloatRect(1185.f, 485.f, 95.f, 235.f)); // zona escondite cocina

}
