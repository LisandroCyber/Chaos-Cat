#include "NivelCocina.h"

NivelCocina::NivelCocina()
{
    cargarFondo("images/cocina.png");

    if (cargarMusicaFondo("music/loopPrincipal.wav", 5.f))
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
        sf::FloatRect(285.f, 70.f, 585.f, 1470.f));

    agregarMueble("images/mesa-larga.png",
        { 356.06f, 400.f },
        { 0.280825f, 0.384588f },
        sf::FloatRect(47.f, 320.f, 1442.f, 561.f));

    agregarObjeto("images/TazaCafe.png", { 465.f, 480.f }, 0.25f);
    agregarObjeto("images/frutero.png", { 600.f, 450.f }, 0.15f);
    agregarObjeto("images/cacerola.png", { 1139.f, 405.f }, 0.50f);
    agregarObjeto("images/platos.png", { 75.f, 235.f }, 0.08f);

    agregarSuperficie(sf::FloatRect(1090.f, 490.f, 202.f, 265.f)); // Horno
    
}
