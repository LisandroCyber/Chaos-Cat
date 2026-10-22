#include "NivelPatio.h"
#include <iostream>

NivelPatio::NivelPatio()
{
    cargarFondo("images/3-Patio/patio.png");
    setAnchoNivel(static_cast<float>(ANCHO_VENTANA));

    //TODO: buscar musica
    if (!cargarMusicaFondo("music/EnPartida/Cocina/LoopNivelCocina.wav", 20.f))
    {
        std::cout << "No se pudo cargar la musica del Patio\n";
    }

    Enemigo* perro = agregarEnemigo("images/Enemigos/perro.png",
        { 680.f, 320.f }, 512, 768, { 0.38f, 0.38f },
        "", VOLUMEN_ALERTA_PERRO); // Pendiente: ruta del audio del perro

    perro->configurarTiempos(
        TIEMPO_PERRO_REPOSO,
        TIEMPO_PERRO_REPOSO,
        TIEMPO_PERRO_ALERTA,
        TIEMPO_PERRO_VIGILANCIA);

    //reacciona al ruido, pero sigue su alerta normal
    perro->configurarRuido(true, false);

    perro->configurarPresentacion(FRAME_PERRO_DETECCION, false);

    Enemigo* camara = agregarEnemigo("images/Enemigos/camara_estados.png",
        { 1050.f, 62.f }, 724, 724, { 0.17f, 0.17f },
        "", VOLUMEN_ALERTA_CAMARA); //Pendiente: ruta del audio de la camara

    camara->configurarTiempos(
        TIEMPO_CAMARA_REPOSO,
        TIEMPO_CAMARA_REPOSO,
        TIEMPO_CAMARA_ALERTA,
        TIEMPO_CAMARA_VIGILANCIA);

    //ignora las caidas y conserva el tercer frame al detecta
    camara->configurarRuido(false, false);
    camara->configurarPresentacion(FRAME_ENEMIGO_SIN_CAMBIO, false);

    //muebles
    agregarMueble("images/3-Patio/muebles/banco.png",
        { 176.f, 382.f }, { 0.26f, 0.26f },
        sf::FloatRect(160.f, 500.f, 1450.f, 55.f));

    agregarMueble("images/3-Patio/muebles/mesa.png",
        { 263.f, 524.f }, { 0.16f, 0.16f },
        sf::FloatRect(160.f, 170.f, 1220.f, 100.f));

    agregarMueble("images/3-Patio/muebles/estante_plantas.png",
        { 781.1f, 474.8f }, { 0.204f, 0.204f },
        sf::FloatRect(180.f, 220.f, 870.f, 65.f));

    agregarMueble("images/3-Patio/muebles/cajon.png",
        { 1027.2f, 566.9f },
        { 0.1815f, 0.1815f },
        sf::FloatRect(210.f, 240.f, 1100.f, 75.f));

    agregarMueble("images/3-Patio/objetos/maceton_grande.png",
        { -8.f, 461.f },
        { 0.18f, 0.18f },
        sf::FloatRect());

    //superficies adicionales
    agregarSuperficie(sf::FloatRect(215.f, 413.f, 375.f, 12.f)); //parte superir del banco
    agregarSuperficie(sf::FloatRect(580.f, 470.f, 48.f, 12.f)); //apoyabrazo derecho del banco
    agregarSuperficie(sf::FloatRect(818.3f, 617.6f, 177.6f, 13.2f)); //repisa inferior del estante de planta
    agregarSuperficie(sf::FloatRect(171.f, 480.f, 46.f, 10.f)); //apoyabrazo izquierdo del banco

    //escondite
    agregarZonaEscondite(sf::FloatRect(0.f, 535.f, 165.f, 185.f)); //maceton
    agregarZonaEscondite(sf::FloatRect(1065.315f, 574.8f, 199.65f, 145.2f)); // cajon de madera

    //macetas sobre el respaldo del banco
    agregarObjeto("images/3-Patio/objetos/maceta_mediana_amarillas.png",
        { 266.86f, 314.06f }, 0.083f, 3,
        "images/3-Patio/objetos/rotos/maceta_mediana_amarillas_rota.png",
        "sound effects/objetos/vidrioRoto.wav");

    agregarObjeto("images/3-Patio/objetos/maceta_mediana_rosadas.png",
        { 449.79f, 311.68f }, 0.085f, 3,
        "images/3-Patio/objetos/rotos/maceta_mediana_rosadas_rota.png",
        "sound effects/objetos/vidrioRoto.wav");

    //regadera sobre el asiento y toalla sobre el apoyabrazos
    agregarObjeto("images/3-Patio/objetos/regadera.png",
        { 251.12f, 464.4f }, 0.05f, 2,
        "images/3-Patio/objetos/rotos/regadera_rota.png",
        "sound effects/objetos/golpeMetal.wav");

    agregarObjeto("images/3-Patio/objetos/toalla.png",
        { 552.36f, 464.24f }, 0.06f, 1,
        "images/3-Patio/objetos/rotos/toalla_rota.png",
        "sound effects/objetos/golpeFruta.wav");

    //jarra y vaso sobre la mesa
    agregarObjeto("images/3-Patio/objetos/jarra_agua.png",
        { 317.38f, 491.8f }, 0.05f, 1,
        "images/3-Patio/objetos/rotos/jarra_agua_rota.png",
        "sound effects/objetos/vidrioRoto.wav");

    agregarObjeto("images/3-Patio/objetos/vaso.png",
        { 406.57f, 515.36f }, 0.033f, 1,
        "images/3-Patio/objetos/rotos/vaso_roto.png",
        "sound effects/objetos/vidrioRoto.wav");

    //maceta con flores arriba y suculenta en la repisa inferior
    agregarObjeto("images/3-Patio/objetos/maceta_mediana_blancas.png",
        { 835.22f, 422.44f }, 0.085f, 3,
        "images/3-Patio/objetos/rotos/maceta_mediana_blancas_rota.png",
        "sound effects/objetos/vidrioRoto.wav");

    agregarObjeto("images/3-Patio/objetos/maceta_chica_04.png",
        { 887.02f, 578.24f }, 0.04f, 2,
        "images/3-Patio/objetos/rotos/maceta_chica_04_rota.png",
        "sound effects/objetos/vidrioRoto.wav");

    //planta sobre el cajon y maceta chica junto al banco
    agregarObjeto("images/3-Patio/objetos/maceta_chica_02.png",
        { 1114.8f, 511.4f }, 0.09f, 3,
        "images/3-Patio/objetos/rotos/maceta_chica_02_rota.png",
        "sound effects/objetos/vidrioRoto.wav");

    agregarObjeto("images/3-Patio/objetos/maceta_chica_03.png",
        { 159.77f, 424.8f }, 0.05f, 2,
        "images/3-Patio/objetos/rotos/maceta_chica_03_rota.png",
        "sound effects/objetos/vidrioRoto.wav");

    //la pelota es golpeable pero al hacerlo se pierde la partida porque el perro se despierta de una jajajj
    agregarObjeto("images/3-Patio/objetos/pelota.png",
        { 633.59f, 642.f }, 0.05f, 1,
        "images/3-Patio/objetos/pelota.png",
        "sound effects/objetos/golpeFruta.wav");
}
