#include "NivelLivingNoche.h"
#include <iostream>

NivelLivingNoche::NivelLivingNoche()
{
    cargarEscenario();
    cargarEnemigos();
    cargarMuebles();
    cargarObjetos();
}

void NivelLivingNoche::cargarEscenario()
{
    cargarFondo("images/6-Living_noche/living_noche.png");

    if (!cargarMusicaFondo("music/EnPartida/Living/LoopNivelLiving.wav", 22.f))
    {
        std::cout << "ERROR AL CARGAR LA MUSICA\n";
    }
}

void NivelLivingNoche::cargarEnemigos()
{
    Enemigo* duenia = agregarEnemigo("images/Enemigos/frames_enemiga_sofa_borracha.png", //dueña
        { 1600.f, 500.f },
        600,
        724,
        { 0.52f, 0.53f },
        "sound effects/enemigos/mmh_duenia.wav",
        VOLUMEN_ALERTA_DUENIA_LIVING);
    duenia->configurarReinicioFueraDeCamara();

    Enemigo* duenio = agregarEnemigo("images/Enemigos/frames_enemigo_sofa_borracho.png", //dueño
        { 930.f, 570.f },
        600,
        724,
        { 0.52f, 0.53f },
        "sound effects/enemigos/huu_duenio.wav",
        VOLUMEN_ALERTA_DUENIO);
    duenio->configurarReinicioFueraDeCamara();
}

void NivelLivingNoche::cargarMuebles()
{
    // Baul con escondite
    agregarMueble(
        "images/2-Living/Muebles/baul.png",
        { 0.f, 550.f },
        { 0.17f, 0.18f },
        sf::FloatRect(90.f, 195.f, 1440.f, 20.f) /// arreglar
    );

    agregarZonaEscondite(
        sf::FloatRect(10.f, 576.f, 260.f, 220.f)
    );

    // Mesa ratona
    agregarMueble(
        "images/6-living_noche/Muebles/mesa_ratona_nocturna.png",
        { 310.f, 500.f },
        { 1.f, 1.0f },
        sf::FloatRect(6.f, 19.f, 400.f, 30.f)
    );

    // Cuadro Messi (decoracion)
    agregarMueble(
        "images/6-Living_noche/Muebles/cuadroMessi_nocturno.png",
        { 575.f , 180.f },
        { 0.13f , 0.13f },
        sf::FloatRect(0.f, 0.f, 100.f, 100.f)
    );

    // Mesa chica izquierda
    agregarMueble(
        "images/6-Living_noche/Muebles/mesa_chica_nocturna.png",
        { 1190.f, 480.f },
        { 1.0f, 1.0f },
        sf::FloatRect(9.f, 25.f, 116.f, 15.f)
    );

    // Mesa tele
    agregarMueble(
        "images/6-Living_noche/Muebles/mueble_tele_nocturno.png",
        { 1340.f, 495.f },
        { 0.339f, 0.408f },
        sf::FloatRect(68.f, 257.f, 1962.f, 24.5f)
    );

    // Mesa chica derecha
    agregarMueble(
        "images/6-Living_noche/Muebles/mesa_chica_nocturna.png",
        { 2230.f, 480.f },
        { 0.8f, 0.8f },
        sf::FloatRect(9.f, 25.f, 116.f, 15.f)
    );

    // Pila de regalos
    agregarMueble(
        "images/6-Living_noche/Muebles/pila_regalos_nocturna.png",
        { 2370.f, 490.f },
        { 0.4f, 0.420f },
        sf::FloatRect(68.f, 520.f, 160.f, 24.5f)
    );

    agregarZonaEscondite(
        sf::FloatRect(2360.6f, 530.f, 230.f, 200.f)
    );
}

void NivelLivingNoche::cargarObjetos()
{
    agregarObjeto(
        "images/6-Living_noche/Objetos/portarretrato_espalda_nocturno.png",
        { 98.f , 525.f },
        0.37f,
        1,
        "images/6-Living_noche/Objetos/rotos/portarretrato_espalda_nocturno_roto.png",
        "sound effects/objetos/vidrioRoto.wav"
    );

    agregarObjeto(
        "images/6-Living_noche/Objetos/botella_vino_nocturna.png",
        { 355.f, 420.f },
        0.46f,
        2,
        "images/6-Living_noche/Objetos/rotos/botella_vino_nocturna_rota.png",
        "sound effects/objetos/vidrioRoto.wav"
    );

    agregarObjeto(
        "images/6-Living_noche/Objetos/copa_vino_nocturna.png",
        { 410.f, 460.f },
        0.4f,
        1,
        "images/6-Living_noche/Objetos/rotos/copa_vino_nocturna_rota.png",
        "sound effects/objetos/vidrioRoto.wav"
    );

    agregarObjeto(
        "images/6-Living_noche/Objetos/vaso_cerveza_nocturno.png",
        { 540.f, 470.f },
        0.35f,
        1,
        "images/6-Living_noche/Objetos/rotos/vaso_cerveza_nocturno_roto.png",
        "sound effects/objetos/vidrioRoto.wav"
    );

    agregarObjeto(
        "images/6-Living_noche/Objetos/bowl_papitas_nocturno.png",
        { 610.f, 475.f },
        0.35f,
        2,
        "images/6-Living_noche/Objetos/rotos/bowl_papitas_nocturno_roto.png",
        "sound effects/objetos/vidrioRoto.wav"
    );

    agregarObjeto(
        "images/6-Living_noche/Objetos/frasco_aceitunas_nocturno.png",
        { 695.f, 467.f },
        0.35f,
        2,
        "images/6-Living_noche/Objetos/rotos/frasco_aceitunas_nocturno_roto.png",
        "sound effects/objetos/vidrioRoto.wav"
    );


    agregarObjeto(
        "images/6-Living_noche/Objetos/jarra_clerico_nocturna.png",
        { 1235.f, 440.f },
        0.35f,
        2,
        "images/6-Living_noche/Objetos/rotos/jarra_clerico_nocturna_rota.png",
        "sound effects/objetos/vidrioRoto.wav"
    );

    agregarObjeto(
        "images/6-Living_noche/Objetos/parlante_portatil_nocturno.png",
        { 1406.f, 540.f },
        0.52f,
        1,
        "images/6-Living_noche/Objetos/rotos/parlante_portatil_nocturno_roto.png",
        "sound effects/objetos/vidrioRoto.wav"
    );

    agregarObjeto(
        "images/6-Living_noche/Objetos/tele_nocturna.png",
        { 1600.f, 455.f },
        0.7f,
        4,
        "images/6-Living_noche/Objetos/rotos/tele_nocturna_rota.png",
        "sound effects/objetos/vidrioRoto.wav"
    );

    agregarObjeto(
        "images/6-Living_noche/Objetos/casita_ceramica_nocturna.png",
        { 1997.f, 510.f },
        0.53f,
        2,
        "images/6-Living_noche/Objetos/rotos/casita_ceramica_nocturna_rota.png",
        "sound effects/objetos/vidrioRoto.wav"
    );

    agregarObjeto(
        "images/6-Living_noche/Objetos/plato_torta_nocturno.png",
        { 2240.f, 462.f },
        0.3f,
        1,
        "images/6-Living_noche/Objetos/rotos/plato_torta_nocturno_roto.png",
        "sound effects/objetos/vidrioRoto.wav"
    );
}
