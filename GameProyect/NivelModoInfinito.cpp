#include "NivelModoInfinito.h"

NivelModoInfinito::NivelModoInfinito()
{
    cargarEscenario();
    cargarEnemigos();
    cargarMuebles();
    cargarObjetos();
}

void NivelModoInfinito::cargarEscenario()
{
    cargarFondo("images/ModoInfinito/living.png");
}

void NivelModoInfinito::cargarEnemigos()
{
}

void NivelModoInfinito::cargarMuebles()
{
    agregarMueble(
        "images/ModoInfinito/muebles/baul.png",
        { 0.f, 557.8f },
        { 0.17f, 0.18f },
        sf::FloatRect(0.f, 0.f, 0.f, 0.f)
    );

    agregarZonaEscondite(
        sf::FloatRect(10.f, 588.f, 255.f, 137.f)
    );

    agregarMueble(
        "images/ModoInfinito/muebles/sillon_individual.png",
        { 874.f, 515.3f },
        { 0.8f, 0.8f },
        sf::FloatRect(42.f, 160.f, 145.f, 30.f)
    );

    agregarSuperficie(
        sf::FloatRect(1023.6f, 605.3f, 40.f, 20.f)
    );

    agregarBarreraLateral(
        sf::FloatRect(1023.6f, 625.3f, 40.f, 40.f)
    );

    agregarSuperficie(
        sf::FloatRect(873.6f, 605.3f, 40.f, 20.f)
    );

    agregarBarreraLateral(
        sf::FloatRect(873.6f, 625.3f, 40.f, 40.f)
    );

    agregarZonaEscondite(
        sf::FloatRect(907.6f, 533.3f, 160.f, 140.f)
    );

    agregarMueble(
        "images/ModoInfinito/muebles/mueble_tele.png",
        { 1397.f, 493.3f },
        { 0.339f, 0.408f },
        sf::FloatRect(68.f, 257.f, 1962.f, 24.5f)
    );

    agregarBarreraLateral(
        sf::FloatRect(1420.f, 598.3f, 689.f, ALTO_VENTANA - 598.3f),
        true
    );

    agregarMueble(
        "images/ModoInfinito/muebles/tele.png",
        { 1593.f, 381.5f },
        { 1.f, 1.f },
        sf::FloatRect(0.f, 0.f, 0.f, 0.f)
    );

    agregarZonaEscondite(
        sf::FloatRect(1603.f, 381.5f, 390.f, 220.f)
    );

    //creo un vector con las distintas posiciones de las plataformas, me va a servir para cuando cargue los objetos
    const sf::Vector2f posicionesPlataformas[] = {
        { 67.f, 451.f },
        { 229.f, 129.f },
        { 438.f, 597.f },
        { 596.f, 327.f },
        { 893.f, 233.f },
        { 1126.f, 474.f },
        { 1410.f, 269.f },
        { 1871.f, 261.f },
        { 2259.f, 455.f }
    };

    const sf::Vector2f escalaPlataforma(0.75f, 0.75f);
    const sf::FloatRect hitboxPlataforma(12.f, 17.f, 232.f, 8.f);

    for (const sf::Vector2f& posicion : posicionesPlataformas)
    {
        agregarMueble(
            "images/ModoInfinito/muebles/plataforma.png",
            posicion,
            escalaPlataforma,
            hitboxPlataforma
        );
    }
}

void NivelModoInfinito::cargarObjetos()
{
}
