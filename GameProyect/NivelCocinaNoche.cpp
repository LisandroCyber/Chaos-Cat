#include "NivelCocinaNoche.h"
#include <iostream>

NivelCocinaNoche::NivelCocinaNoche()
{
    cargarFondo("images/5-Cocina_noche/cocina_noche.png");
    setAnchoNivel(static_cast<float>(ANCHO_VENTANA));

    //TODO: cargar musica de la cocina de noche
    if (!cargarMusicaFondo("music/EnPartida/Cocina/LoopNivelCocina.wav", 22.f))
    {
        std::cout << "ERROR AL CARGAR LA MUSICA\n";
    }

    //TODO: cambiar sonido de dueños a uno mas borracho
    agregarEnemigo("images/Enemigos/frames_enemigo_fiesta_borracho.png",
        { 672.f, 664.f },
        600,
        724,
        { 0.7f, 0.82f },
        "sound effects/enemigos/huu_duenio.wav",
        VOLUMEN_ALERTA_DUENIO);

    agregarEnemigo("images/Enemigos/frames_enemiga_fiesta_vestido_borracha.png",
        { 372.f, 664.f },
        600,
        724,
        { 0.7f, 0.82f },
        "sound effects/enemigos/mmh_duenia.wav",
        VOLUMEN_ALERTA_DUENIA_COCINA);

    agregarMueble("images/5-Cocina_noche/muebles/heladera_nocturna.png",
        { 3.f, 300.f },
        { 0.25f, 0.272f },
        sf::FloatRect(185.f, 70.f, 585.f, 100.f));
    agregarZonaEscondite(sf::FloatRect(0.f, 520.f, 145.f, 235.f)); // zona escondite heladera

    agregarMueble("images/5-Cocina_noche/muebles/mesa-larga_nocturna.png",
        { 396.06f, 400.f },
        { 0.280825f, 0.384588f },
        sf::FloatRect(47.f, 320.f, 1442.f, 100.f));

    agregarSuperficie(sf::FloatRect(1090.f, 490.f, 250.f, 50.f)); // superficie Horno
    agregarZonaEscondite(sf::FloatRect(1185.f, 485.f, 95.f, 235.f)); // zona escondite horno

    agregarObjeto("images/5-Cocina_noche/objetos/bandeja_sanguchitos_miga_nocturna.png", { 75.f, 265.f }, 0.15f, 2, "images/5-Cocina_noche/objetos/rotos/bandeja_sanguchitos_caida_nocturna.png", "sound effects/objetos/vidrioRoto.wav");
    agregarObjeto("images/5-Cocina_noche/objetos/botella_ambar_vacia_nocturna.png", { 726.82f, 433.60f }, 0.14f, 3, "images/5-Cocina_noche/objetos/rotos/botella_ambar_rota_nocturna.png", "sound effects/objetos/vidrioRoto.wav");
    agregarObjeto("images/5-Cocina_noche/objetos/botella_verde_vacia_nocturna.png", { 687.33f, 435.07f }, 0.12f, 3, "images/5-Cocina_noche/objetos/rotos/botella_verde_rota_nocturna.png", "sound effects/objetos/vidrioRoto.wav");
    agregarObjeto("images/5-Cocina_noche/objetos/jarra_vacia_nocturna.png", { 504.67f, 456.60f }, 0.11f, 3, "images/5-Cocina_noche/objetos/rotos/jarra_rota_nocturna.png", "sound effects/objetos/vidrioRoto.wav");
    agregarObjeto("images/5-Cocina_noche/objetos/sarten_con_comida_nocturna.png", { 1132.70f, 426.92f }, 0.18f, 3, "images/5-Cocina_noche/objetos/rotos/sarten_con_comida_rota_nocturna.png", "sound effects/objetos/golpeMetal.wav");
    agregarObjeto("images/5-Cocina_noche/objetos/vaso_cerveza_nocturno.png", { 615.60f, 479.21f }, 0.08f, 2, "images/5-Cocina_noche/objetos/rotos/vaso_cerveza_roto_nocturno.png", "sound effects/objetos/vidrioRoto.wav");
    agregarObjeto("images/5-Cocina_noche/objetos/vaso_cerveza_nocturno.png", { 653.27f, 479.21f }, 0.08f, 2, "images/5-Cocina_noche/objetos/rotos/vaso_cerveza_roto_nocturno.png", "sound effects/objetos/vidrioRoto.wav");
    agregarObjeto("images/5-Cocina_noche/objetos/vaso_vino_nocturno.png", { 463.68f, 475.73f }, 0.09f, 2, "images/5-Cocina_noche/objetos/rotos/vaso_vino_roto_nocturno.png", "sound effects/objetos/vidrioRoto.wav");
    agregarObjeto("images/5-Cocina_noche/objetos/vaso_vino_nocturno.png", { 567.27f, 475.73f }, 0.09f, 2, "images/5-Cocina_noche/objetos/rotos/vaso_vino_roto_nocturno.png", "sound effects/objetos/vidrioRoto.wav");
    agregarObjeto("images/5-Cocina_noche/objetos/barril_cerveza_metal_nocturno.png", { 987.42f, 545.10f }, 0.30f, 5, "images/5-Cocina_noche/objetos/rotos/barril_cerveza_metal_roto_nocturno.png", "sound effects/objetos/golpeBarril.wav");

}