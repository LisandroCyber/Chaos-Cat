#include "NivelLiving.h"

NivelLiving::NivelLiving()
{
    cargarFondo("images/2-Living/living.png");
    
    Enemigo* duenia = agregarEnemigo("images/Enemigos/frames_enemiga.png", //dueña
        { 1600.f, 500.f },
        600,
        724,
        { 0.52f, 0.53f },
        "sound effects/enemigos/mmh_duenia.wav",
        VOLUMEN_ALERTA_DUENIA_LIVING);
    duenia->configurarReinicioFueraDeCamara();

    Enemigo* duenio = agregarEnemigo("images/Enemigos/frames_enemigo_limpiando.png", //dueño
        { 310.f, 500.f },
        600,
        724,
        { 0.52f, 0.53f },
        "sound effects/enemigos/huu_duenio.wav",
        VOLUMEN_ALERTA_DUENIO);
    duenio->configurarReinicioFueraDeCamara();

    agregarMueble("images/2-living/Muebles/mesa_ratona.png", 
        { 430.f, 500.f },
        { 1.2f, 1.f },
        sf::FloatRect(6.f, 19.f, 400.f, 30.f)
    );

    agregarObjeto(
        "images/2-Living/Objetos/Florero.png",
        { 550.f, 390.f },
        0.17f,
        2,
        "images/2-Living/Objetos/rotos/FloreroRoto.png",
        "sound effects/objetos/vidrioRoto.wav"
    );

    agregarObjeto(
        "images/2-Living/Objetos/TazaCafe.png",
        { 855.f, 484.f },
        0.25f,
        1,
        "images/2-Living/Objetos/rotos/TazaCafe_rota.png",
        "sound effects/objetos/vidrioRoto.wav"
    );

    /// Sillon individual
    agregarMueble(
        "images/2-Living/Muebles/sillon_individual.png",
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
        "images/2-Living/Muebles/mesa_chica.png",
        { 1350.f, 480.f },
        { 1.2f, 1.2f },
        sf::FloatRect(9.f, 25.f, 116.f, 15.f)
    );
    
    agregarObjeto(
        "images/2-Living/Objetos/PilaDeLibros.png",
        { 1350.f, 433.f },
        0.15f,
        2,
        "images/2-Living/Objetos/rotos/pilaDeLibrosTirados.png",
        "sound effects/objetos/golpeFruta.wav"
    );

    // Compensa los margenes del PNG nuevo y baja el conjunto hasta el piso.
    agregarMueble(
        "images/2-Living/Muebles/mueble_tele.png",
        { 1732.f, 495.f },
        { 0.339f, 0.408f },
        sf::FloatRect(68.f, 257.f, 1962.f, 24.5f)
    );

    // Bloquea el cuerpo del mueble sin impedir apoyarse sobre su tapa.
    agregarBarreraLateral(
        sf::FloatRect(1755.f, 600.f, 689.f, ALTO_VENTANA - 600.f),
        true
    );

    agregarMueble(
        "images/2-Living/Muebles/tele.png",
        { 1980.f, 400.f  },
        { 1.f, 1.f },
        sf::FloatRect(0.f , 20.f , 400.f, 200.f)
    );

    agregarZonaEscondite(
        sf::FloatRect(1990.f, 400.f, 390.f, 220.f)
    );

    agregarSuperficie(
        sf::FloatRect(1143.6f, 490.f, 40.f, 20.f)
    );

    agregarObjeto(
        "images/2-Living/Objetos/control_remoto.png",
        { 1820.f , 580.f},
        0.08f,
        1,
        "images/2-Living/Objetos/rotos/control_remoto_tirado.png",
        "sound effects/objetos/golpeFruta.wav"
    );

    agregarMueble(
        "images/2-Living/Muebles/baul.png",
        { 0.f, 550.f },
        { 0.17f, 0.18f },
        sf::FloatRect(90.f, 195.f, 1440.f, 20.f) /// arreglar
    );

    agregarZonaEscondite(
        sf::FloatRect(10.f, 576.f, 260.f, 220.f)
    );

    agregarObjeto(
        "images/2-Living/Objetos/cuadroFoto.png",
        { 98.f , 525.f },
        0.1f,
        1,
        "images/2-Living/Objetos/rotos/cuadroFotoRoto.png",
        "sound effects/objetos/vidrioRoto.wav"
    );

    agregarMueble(
        "images/2-Living/Muebles/cuadroMessi.png",
        { 575.f , 180.f },
        { 0.13f , 0.13f },
        sf::FloatRect(0.f, 0.f, 100.f, 100.f)
    );
}
