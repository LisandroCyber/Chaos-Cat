#include "NivelHabitacion.h"
#include <iostream>

NivelHabitacion::NivelHabitacion()
{
    cargarFondo("images/4-Habitacion/habitacion.png");

    if (!cargarMusicaFondo("music/EnPartida/Habitacion/LoopNivelHabitacion.wav", 22.f))
    {
        std::cout << "ERROR AL CARGAR LA MUSICA\n";
    }

    /// cargar aca la camara de seguridad
    /// zona escondite arriba del placard, aca iria la camara
    agregarSuperficie(sf::FloatRect(1390.f, 120.f, 200.f, 5.f));
    agregarZonaEscondite(sf::FloatRect(1400.f, 5.f, 200.f, 125.f));

    /// Enemigo entra a la habitacion si esucha ruido
    agregarEnemigo(
        "images/Enemigos/duenio_entrando.png",
        { 60.f, 615.f },   // Puerta: centro del cuadro y altura de sus pies.
        525,
        525,
        { 0.5f, 0.6f },
        true
    );


    /// mesa de cama y television con escondite
    agregarMueble(
        "images/4-Habitacion/muebles/mueble_tele_nocturno.png",
        { 470.f, 530.f },
        { 0.25f, 0.35f },
        sf::FloatRect(47.f, 237.f, 1975.f, 30.f)
    );

    agregarMueble(
        "images/4-Habitacion/muebles/tele_nocturna.png",
        { 585.f, 435.f },
        { 0.2f, 0.2f },
        sf::FloatRect(0.f, 0.f, 0.f, 0.f)
        );
    agregarObjeto(
        "images/4-Habitacion/objetos/control_remoto.png",
        { 500.f, 590.f },
        0.08f,
        1,
        "images/4-Habitacion/objetos/rotos/control_remoto_tirado.png",
        "sound effects/objetos/golpeFruta.wav"
    );
    agregarZonaEscondite(sf::FloatRect(595.f, 445.f, 330.f, 185.f)); // zona escondite television
   
    /// 3 Estantes de la parte izquierda y sus objetos

    // agregarZonaEscondite(sf::FloatRect(330.f, 58.f, 140.f, 120.f)); // zona escondite estante de arriba
    agregarMueble(
        "images/4-Habitacion/muebles/soporte_planta_v2.png",
        { 300.f, 105.f },
        { 0.15f, 0.15f },
        sf::FloatRect(300, 450.f, 815.f, 30.f)
    );
    agregarObjeto("images/4-Habitacion/objetos/maceta_colgante.png",
        { 397.f, 97.f }, 
        0.13f, 
        2, 
        "images/4-Habitacion/objetos/rotos/maceta_colgante_rota.png", 
        "sound effects/objetos/golpeFruta.wav");
    //
    agregarMueble(
        "images/4-Habitacion/muebles/soporte_planta_v2.png",
        { 130.f, 225.f },
        { 0.15f, 0.15f },
        sf::FloatRect(300, 450.f, 815.f, 30.f)
    );
    agregarObjeto("images/4-Habitacion/objetos/maceta_Hojas_grandes.png",
        { 158.f, 190.f },
        0.1f,
        2,
        "images/4-Habitacion/objetos/rotos/maceta_hojas_grandes_rota.png",
        "sound effects/objetos/golpeFruta.wav");
    //
    agregarMueble(
        "images/4-Habitacion/muebles/soporte_planta_v2.png",
        { 180.f, 375.f },
        { 0.15f, 0.15f },
        sf::FloatRect(300, 450.f, 815.f, 30.f)
    );
    agregarObjeto(
        "images/4-Habitacion/objetos/cuadroFoto.png",
        { 230.f , 393.f },
        0.08f,
        1,
        "images/4-Habitacion/objetos/rotos/cuadroFotoRoto.png",
        "sound effects/objetos/vidrioRoto.wav"
    );
    
    /// Mesa de luz derecha
    agregarSuperficie(sf::FloatRect(969.f, 461.f, 121.f, 5.f));
    agregarObjeto(
        "images/4-Habitacion/objetos/vaso_agua.png",
        { 962.f , 432.f },
        0.025f,
        1,
        "images/4-Habitacion/objetos/rotos/vaso_roto.png",
        "sound effects/objetos/vidrioRoto.wav"
    );
    agregarObjeto(
        "images/4-Habitacion/objetos/lampara_derecha_apagada.png",
        { 1010.f , 361.f },
        0.12f,
        2,
        "images/4-Habitacion/objetos/rotos/lampara_derecha_rota.png",
        "sound effects/objetos/GolpeMetal.wav"
    );

    /// Mesa de luz izquierda
    agregarSuperficie(sf::FloatRect(435.f, 461.f, 121.f, 5.f)); 
    agregarObjeto(
        "images/4-Habitacion/objetos/lampara_izquierda_apagada.png",
        { 432.f , 361.f },
        0.12f,
        2,
        "images/4-Habitacion/objetos/rotos/lampara_izquierda_rota.png",
        "sound effects/objetos/GolpeMetal.wav"
    );

    /// Estante derecho
    agregarMueble(
        "images/4-Habitacion/muebles/soporte_planta.png",
        { 1150.f, 308.f },
        { 0.15f, 0.15f },
        sf::FloatRect(300, 450.f, 815.f, 30.f)
    );
    agregarObjeto(
        "images/4-Habitacion/objetos/reloj_despertador.png",
        { 1240.f , 317.f },
        0.08f,
        1,
        "images/4-Habitacion/objetos/rotos/reloj_despertador_roto.png",
        "sound effects/objetos/GolpeMetal.wav"
    );

    /// canasto de ropa
    agregarObjeto(
        "images/4-Habitacion/objetos/canasto_ropa.png",
        { 1200.f , 605.f },
        0.13f,
        2,
        "images/4-Habitacion/objetos/rotos/canasto_ropa_tirado.png",
        "sound effects/objetos/GolpeFruta.wav"
    );

}