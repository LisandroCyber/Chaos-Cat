#include "NivelCocina.h"
#include <iostream>

NivelCocina::NivelCocina()
{
    cargarFondo("images/1-Cocina/cocina.png");
    setAnchoNivel(static_cast<float>(ANCHO_VENTANA));

    if (!cargarMusicaFondo("music/EnPartida/Cocina/LoopNivelCocina.wav", 22.f))
    {
        std::cout << "ERROR AL CARGAR LA MUSICA\n";
    }

    agregarEnemigo("images/Enemigos/frames_enemigo.png",
        { 672.f, 664.f },
        600,
        724,
        { 0.7f, 0.82f },
        "sound effects/enemigos/huu_duenio.wav",
        VOLUMEN_ALERTA_DUENIO);

    agregarMueble("images/1-Cocina/Muebles/heladera.png",
        { 3.f, 300.f },
        { 0.25f, 0.272f },
        sf::FloatRect(185.f, 70.f, 585.f, 100.f));
    agregarZonaEscondite(sf::FloatRect(0.f, 520.f, 145.f, 235.f)); // zona escondite heladera
    agregarObjeto("images/1-Cocina/Objetos/platos.png", { 75.f, 235.f }, 0.08f, 2, "images/1-Cocina/Objetos/rotos/platos_rotos.png", "sound effects/objetos/vidrioRoto.wav");

    agregarMueble("images/1-Cocina/Muebles/mesa-larga.png",
        { 396.06f, 400.f },
        { 0.280825f, 0.384588f },
        sf::FloatRect(47.f, 320.f, 1442.f, 100.f));
    agregarObjeto("images/1-Cocina/Objetos/TazaCafe.png", { 505.f, 480.f }, 0.25f, 1, "images/1-Cocina/Objetos/rotos/TazaCafe_rota.png", "sound effects/objetos/vidrioRoto.wav");
    agregarObjeto("images/1-Cocina/Objetos/frutero.png", { 640.f, 450.f }, 0.15f, 3, "images/1-Cocina/Objetos/rotos/frutero_caido.png", "sound effects/objetos/golpeFruta.wav");

    agregarSuperficie(sf::FloatRect(1090.f, 490.f, 250.f, 50.f)); // superficie Horno
    agregarObjeto("images/1-Cocina/Objetos/cacerola.png", { 1139.f, 405.f }, 0.50f, 3, "images/1-Cocina/Objetos/rotos/cacerola_caida.png", "sound effects/objetos/golpeMetal.wav");
    agregarZonaEscondite(sf::FloatRect(1185.f, 485.f, 95.f, 235.f)); // zona escondite horno
    

}
