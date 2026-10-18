#include "NivelLiving.h"

NivelLiving::NivelLiving()
{
    cargarFondo("images/2-Living/living.png");

    agregarMueble("images/2-living/mesa_ratona.png",
        { 430.f, 500.f },
        { 1.2f, 1.f },
        sf::FloatRect(6.f, 19.f, 400.f, 30.f)
    );

    agregarMueble(
        "images/2-Living/sillon_individual.png",
        { 994.f, 400.f },
        { 0.8f, 0.8f },
        sf::FloatRect(42.f, 160.f, 145.f, 30.f)
    );

    agregarSuperficie(
        sf::FloatRect(1143.6f, 490.f, 40.f, 20.f)
    );

    agregarBarreraLateral(
        sf::FloatRect(1143.6f, 510.f, 40.f, 40.f)
    );

    agregarSuperficie(
        sf::FloatRect(993.6f, 490.f, 40.f, 20.f)
    );

    agregarBarreraLateral(
        sf::FloatRect(993.6f, 510.f, 40.f, 40.f)
    );

    agregarZonaEscondite(
        sf::FloatRect(1027.6f, 418.f, 160.f, 140.f)
    );

    agregarMueble(
        "images/2-Living/mesa_chica.png",
        { 1350.f, 480.f },
        { 1.2f, 1.2f },
        sf::FloatRect(9.f, 25.f, 116.f, 15.f)
    );

    agregarMueble(
        "images/2-Living/mueble_tele.png",
        { 1750.f, 500.f },
        { 1.f, 1.f },
        sf::FloatRect(5.f, 20.f, 665.f, 10.f)
    );

    agregarMueble(
        "images/2-Living/tele.png",
        { 1980.f, 320.f  },
        { 1.f, 1.f },
        sf::FloatRect(0.f , 20.f , 400.f, 200.f)
    );

    agregarZonaEscondite(
        sf::FloatRect(1990.f, 320.f, 390.f, 220.f)
    );



    agregarSuperficie(
        sf::FloatRect(1143.6f, 490.f, 40.f, 20.f)
    );
    
    agregarObjeto(
        "images/2-Living/Florero.png",
        { 550.f, 390.f },
        0.17f,
        2,
        "images/2-Living/FloreroRoto.png",
        "sound effects/objetos/vidrioRoto.wav"
    );

    agregarObjeto(
        "images/2-Living/TazaCafe.png",
        { 855.f, 484.f },
        0.25f,
        1,
        "images/2-Living/TazaCafe_rota.png",
        "sound effects/objetos/vidrioRoto.wav"
    );

    agregarObjeto(
        "images/2-Living/PilaDeLibros.png",
        { 1350.f, 433.f },
        0.15f,
        2,
        "images/2-Living/pilaDeLibrosTirados.png",
        "sound effects/objetos/golpeFruta.wav"
    );

    agregarObjeto(
        "images/2-Living/control_remoto.png",
        { 1820.f , 500.f},
        0.08f,
        1,
        "images/2-Living/control_remoto_tirado.png",
        "sound effects/objetos/golpeFruta.wav"
    );

    agregarMueble(
    "images/2-Living/cuadroMessi.png",
        { 575.f , 180.f },
        {0.13f , 0.13f},
        sf::FloatRect(0.f, 0.f, 100.f, 100.f)
    );

    agregarMueble(
        "images/2-Living/baul.png",
        { 120.f, 525.f },
        { 0.17f, 0.18f },
        sf::FloatRect(90.f, 195.f, 1440.f, 20.f) /// arreglar
    );

    agregarZonaEscondite(
        sf::FloatRect(130.f, 551.f, 260.f, 220.f)
    );

    agregarObjeto(
        "images/2-Living/cuadroFoto.png",
        { 218.f , 500.f },
        0.1f,
        1,
        "images/2-Living/cuadroFotoRoto.png",
        "sound effects/objetos/vidrioRoto.wav"
    );

    agregarEnemigo("images/Enemigos/frames_enemiga.png", /// DUEÑA
        { 1600.f, 500.f },
        600,
        724,
        { 0.52f, 0.53f });

    agregarEnemigo("images/Enemigos/frames_enemigo.png", /// DUEÑO
        { 310.f, 500.f },
        600,
        724,
        { 0.52f, 0.53f });
}