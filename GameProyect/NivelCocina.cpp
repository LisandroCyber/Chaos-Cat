#include "NivelCocina.h"

NivelCocina::NivelCocina()
{
    cargarFondo("images/cocina.png");

    if (cargarMusicaFondo("music/cocina.mp3", 20.f))
    {
        reproducirMusicaFondo(sf::seconds(0.f));
    }

    agregarHumano("images/frames_humano.png",
        { 672.f, 664.f },
        600,
        724,
        { 0.7f, 0.82f });

    agregarMueble("images/heladera.png",
        { 3.f, 300.f },
        { 0.25f, 0.272f },
        sf::FloatRect(177.f, 40.f, 695.f, 1459.f));

    agregarMueble("images/mesa-larga.png",
        { 356.06f, 400.f },
        { 0.280825f, 0.384588f },
        sf::FloatRect(47.f, 330.f, 1442.f, 561.f));

    agregarObjeto("images/TazaCafe.png", { 530.f, 490.f }, 0.2f);
    agregarObjeto("images/manzana.png", { 580.f, 483.f }, 0.3f);
    agregarObjeto("images/llaves.png", { 415.f, 480.f }, 0.3f);

    agregarObjeto("images/joystick.png", { 695.f, 485.f }, 0.4f); /// No va en este nivel, solo de prueba


    agregarSuperficie(sf::FloatRect(1090.f, 470.f, 202.f, 265.f));
    agregarSuperficie(sf::FloatRect(180.f, 453.f, 1000.f, 450.f));
    

}
