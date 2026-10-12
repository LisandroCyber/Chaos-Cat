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

    agregarSuperficie(
        sf::FloatRect(1143.6f, 490.f, 40.f, 20.f)
    );
    
    agregarObjeto(
        "images/2-Living/obj/Florero.png",
        { 550.f, 390.f },
        0.17f,
        2,
        "images/2-Living/obj/FloreroRoto.png",
        "sound effects/objetos/vidrioRoto.wav"
    );

    agregarObjeto(
        "images/2-Living/obj/TazaCafe.png",
        { 855.f, 484.f },
        0.25f,
        1,
        "images/2-Living/obj/TazaCafe_rota.png",
        "sound effects/objetos/vidrioRoto.wav"
    );

    agregarObjeto(
        "images/2-Living/obj/PilaDeLibros.png",
        { 1350.f, 433.f },
        0.15f,
        1,
        "images/2-Living/obj/pilaDeLibrosTirados.png",
        "sound effects/objetos/golpeFruta.wav"
    );


    /// base para darle profundidad al psio
    agregarSuperficie(
        sf::FloatRect(
            0.f,
            ALTO_VENTANA - 40.f,
            getAnchoNivel(),
            40.f
        )
    );
}