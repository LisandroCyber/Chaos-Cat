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

    agregarBarreraLateral(
        sf::FloatRect(1143.6f, 510.f, 40.f, 40.f)
    );

    agregarSuperficie(
        sf::FloatRect(1143.6f, 490.f, 40.f, 20.f)
    );

    agregarBarreraLateral(
        sf::FloatRect(993.6f, 510.f, 40.f, 40.f)
    );

    agregarSuperficie(
        sf::FloatRect(993.6f, 490.f, 40.f, 20.f)
    );

    agregarZonaEscondite(
        sf::FloatRect(1027.6f, 418.f, 160.f, 140.f)
    );
    
    agregarObjeto(
        "images/2-Living/obj/Florero.png",
        { 550.f, 410.f },
        0.15f,
        2,
        "images/2-Living/obj/FloreroRoto.png",
        "sound effects/objetos/vidrioRoto.wav"
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