#include "NivelHabitacion.h"
#include <iostream>

NivelHabitacion::NivelHabitacion()
{
    cargarFondo("images/4-Habitacion/habitacion.png");
    setAnchoNivel(static_cast<float>(ANCHO_VENTANA));

    if (!cargarMusicaFondo("music/EnPartida/Habitacion/LoopNivelHabitacion.wav", 22.f))
    {
        std::cout << "ERROR AL CARGAR LA MUSICA\n";
    }

    /// cargar aca la camara de seguridad
    /// zona escondite arriba del placard, aca iria la camara
    agregarSuperficie(sf::FloatRect(1200.f, 138.f, 80.f, 8.f));
    agregarZonaEscondite(sf::FloatRect(1180.f, 18.f, 100.f, 128.f));

    /// La enemiga se asoma por la puerta y reacciona a los objetos que caen.
    agregarEnemigo(
        "images/Enemigos/duenia_puerta_estados_nocturna.png",
        { -25.f, 285.f },
        724,
        724,
        { 0.22f, 0.22f },
        "sound effects/enemigos/mmh_duenia_habitacion.wav",
        VOLUMEN_ALERTA_DUENIA_HABITACION,
        true
    );


    /// mesa de cama y television con escondite
    agregarMueble(
        "images/4-Habitacion/muebles/mueble_tele_nocturno.png",
        { 395.4f, 587.5f },
        { 0.245f, 0.23f },
        sf::FloatRect(47.f, 237.f, 1975.f, 30.f)
    );

    agregarMueble(
        "images/4-Habitacion/muebles/tele_nocturna.png",
        { 505.5f, 489.4f },
        { 0.18f, 0.18f },
        sf::FloatRect(0.f, 0.f, 0.f, 0.f)
        );

    agregarZonaEscondite(sf::FloatRect(513.f, 500.f, 296.f, 144.f)); // zona escondite television
   
    /// 3 Estantes de la parte izquierda y sus objetos

    // agregarZonaEscondite(sf::FloatRect(330.f, 58.f, 140.f, 120.f)); // zona escondite estante de arriba
    agregarMueble(
        "images/4-Habitacion/muebles/soporte_planta_v2.png",
        { 108.3f, 121.6f },
        { 0.11f, 0.11f },
        sf::FloatRect(300.f, 416.f, 815.f, 30.f)
    );

    agregarObjeto("images/4-Habitacion/objetos/maceta_colgante.png",
        { 170.6f, 130.5f },
        0.065f,
        2, 
        "images/4-Habitacion/objetos/rotos/maceta_colgante_rota.png", 
        "sound effects/objetos/golpeFruta.wav");
    //
    agregarMueble(
        "images/4-Habitacion/muebles/soporte_planta_v2.png",
        { 208.3f, 241.6f },
        { 0.11f, 0.11f },
        sf::FloatRect(300.f, 416.f, 815.f, 30.f)
    );
    agregarObjeto("images/4-Habitacion/objetos/maceta_Hojas_grandes.png",
        { 246.2f, 216.6f },
        0.065f,
        2,
        "images/4-Habitacion/objetos/rotos/maceta_hojas_grandes_rota.png",
        "sound effects/objetos/golpeFruta.wav");

    //
    agregarMueble(
        "images/4-Habitacion/muebles/soporte_planta_v2.png",
        { 128.3f, 391.6f },
        { 0.11f, 0.11f },
        sf::FloatRect(300.f, 416.f, 815.f, 30.f)
    );
    agregarObjeto(
        "images/4-Habitacion/objetos/cuadroFoto.png",
        { 174.1f , 406.2f },
        0.05f,
        1,
        "images/4-Habitacion/objetos/rotos/cuadroFotoRoto.png",
        "sound effects/objetos/vidrioRoto.wav"
    );
    
    /// Mesa de luz derecha
    agregarSuperficie(sf::FloatRect(817.f, 480.f, 113.f, 8.f));
    agregarObjeto(
        "images/4-Habitacion/objetos/vaso_agua.png",
        { 828.5f , 460.4f },
        0.0175f,
        1,
        "images/4-Habitacion/objetos/rotos/vaso_roto.png",
        "sound effects/objetos/vidrioRoto.wav"
    );
    agregarObjeto(
        "images/4-Habitacion/objetos/lampara_derecha_apagada.png",
        { 870.1f , 419.2f },
        0.075f,
        2,
        "images/4-Habitacion/objetos/rotos/lampara_derecha_rota.png",
        "sound effects/objetos/GolpeMetal.wav"
    );

    /// Mesa de luz izquierda
    agregarSuperficie(sf::FloatRect(369.f, 480.f, 113.f, 8.f));
    agregarObjeto(
        "images/4-Habitacion/objetos/lampara_izquierda_apagada.png",
        { 401.3f , 418.1f },
        0.075f,
        2,
        "images/4-Habitacion/objetos/rotos/lampara_izquierda_rota.png",
        "sound effects/objetos/GolpeMetal.wav"
    );

    /// Estante derecho
    agregarMueble(
        "images/4-Habitacion/muebles/soporte_planta_v2.png",
        { 923.3f, 314.2f },
        { 0.11f, 0.11f },
        sf::FloatRect(300.f, 416.f, 815.f, 30.f)
    );
    agregarObjeto(
        "images/4-Habitacion/objetos/reloj_despertador.png",
        { 966.6f , 334.3f },
        0.034f,
        1,
        "images/4-Habitacion/objetos/rotos/reloj_despertador_roto.png",
        "sound effects/objetos/GolpeMetal.wav"
    );

    /// canasto de ropa
    agregarObjeto(
        "images/4-Habitacion/objetos/canasto_ropa.png",
        { 1125.7f , 614.6f },
        0.145f,
        2,
        "images/4-Habitacion/objetos/rotos/canasto_ropa_tirado.png",
        "sound effects/objetos/GolpeFruta.wav"
    );

}
