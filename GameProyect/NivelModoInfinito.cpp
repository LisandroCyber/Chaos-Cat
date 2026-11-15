#include "NivelModoInfinito.h"
#include <algorithm>
#include <climits>

namespace
{
    const std::array<sf::Vector2f, 9> POSICIONES_PLATAFORMAS = {{
        { 67.f, 451.f },
        { 229.f, 129.f },
        { 438.f, 597.f },
        { 596.f, 327.f },
        { 893.f, 233.f },
        { 1126.f, 474.f },
        { 1410.f, 269.f },
        { 1871.f, 261.f },
        { 2259.f, 455.f }
    }};
    const sf::Vector2f ESCALA_PLATAFORMA(0.75f, 0.75f);
    const sf::FloatRect HITBOX_PLATAFORMA(12.f, 17.f, 232.f, 8.f);
}

NivelModoInfinito::NivelModoInfinito()
{
    cargarEscenario();
    cargarEnemigos();
    cargarMuebles();
    cargarObjetos();
    for (ObjetoActivo& espacio : _objetosActivos)
    {
        generarObjeto(espacio);
    }
}

NivelModoInfinito::~NivelModoInfinito()
{
    for (Objeto* objeto : _reserva)
    {
        delete objeto;
    }
}

//revisa si hay algun objeto roto y lo reemplaza
void NivelModoInfinito::actualizar(Personaje& gato)
{
    Nivel::actualizar(gato);

    for (ObjetoActivo& espacio : _objetosActivos)
    {
        if (espacio.objeto->estaEnElPiso() && !espacio.objeto->estaSonandoCaida())
        {
            generarObjeto(espacio);
            break;
        }
    }
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

    agregarZonaEscondite(sf::FloatRect(10.f, 588.f, 255.f, 137.f));//escondite baul

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

    agregarZonaEscondite(sf::FloatRect(907.6f, 533.3f, 160.f, 140.f));//escondite sillon

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

    agregarZonaEscondite(sf::FloatRect(1603.f, 381.5f, 390.f, 220.f)); //escondite tele

    for (const sf::Vector2f& posicion : POSICIONES_PLATAFORMAS)
    {
        agregarMueble(
            "images/ModoInfinito/muebles/plataforma.png",
            posicion,
            ESCALA_PLATAFORMA,
            HITBOX_PLATAFORMA
        );
    }
}

void NivelModoInfinito::cargarObjetos()
{
    _reserva.reserve(30);

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/bandeja_sanguchitos_miga_nocturna.png",
        { 0.f, 0.f },
        0.14f,
        1,
        "images/ModoInfinito/objetos/rotos/bandeja_sanguchitos_caida_nocturna.png",
        "sound effects/objetos/golpeFruta.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/botella_vino_nocturna.png",
        { 0.f, 0.f },
        0.4f,
        1,
        "images/ModoInfinito/objetos/rotos/botella_vino_nocturna_rota.png",
        "sound effects/objetos/vidrioRoto.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/bowl_papitas_nocturno.png",
        { 0.f, 0.f },
        0.4f,
        1,
        "images/ModoInfinito/objetos/rotos/bowl_papitas_nocturno_roto.png",
        "sound effects/objetos/vidrioRoto.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/cacerola.png",
        { 0.f, 0.f },
        0.5f,
        1,
        "images/ModoInfinito/objetos/rotos/cacerola_caida.png",
        "sound effects/objetos/golpeMetal.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/casita_ceramica_nocturna.png",
        { 0.f, 0.f },
        0.45f,
        1,
        "images/ModoInfinito/objetos/rotos/casita_ceramica_nocturna_rota.png",
        "sound effects/objetos/vidrioRoto.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/control_remoto.png",
        { 0.f, 0.f },
        0.08f,
        1,
        "images/ModoInfinito/objetos/rotos/control_remoto_tirado.png",
        "sound effects/objetos/golpeFruta.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/copa_vino_nocturna.png",
        { 0.f, 0.f },
        0.35f,
        1,
        "images/ModoInfinito/objetos/rotos/copa_vino_nocturna_rota.png",
        "sound effects/objetos/vidrioRoto.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/CuadroFoto.png",
        { 0.f, 0.f },
        0.1f,
        1,
        "images/ModoInfinito/objetos/rotos/CuadroFotoRoto.png",
        "sound effects/objetos/vidrioRoto.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/Florero.png",
        { 0.f, 0.f },
        0.14f,
        1,
        "images/ModoInfinito/objetos/rotos/FloreroRoto.png",
        "sound effects/objetos/vidrioRoto.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/frasco_aceitunas_nocturno.png",
        { 0.f, 0.f },
        0.4f,
        1,
        "images/ModoInfinito/objetos/rotos/frasco_aceitunas_nocturno_roto.png",
        "sound effects/objetos/vidrioRoto.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/jarra_agua.png",
        { 0.f, 0.f },
        0.1f,
        1,
        "images/ModoInfinito/objetos/rotos/jarra_agua_rota.png",
        "sound effects/objetos/vidrioRoto.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/lampara_izquierda_apagada.png",
        { 0.f, 0.f },
        0.095f,
        1,
        "images/4-Habitacion/objetos/rotos/lampara_izquierda_rota.png",
        "sound effects/objetos/golpeMetal.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/maceta.png",
        { 0.f, 0.f },
        0.48f,
        1,
        "images/ModoInfinito/objetos/rotos/maceta_rota.png",
        "sound effects/objetos/vidrioRoto.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/parlante_portatil_nocturno.png",
        { 0.f, 0.f },
        0.48f,
        1,
        "images/ModoInfinito/objetos/rotos/parlante_portatil_nocturno_roto.png",
        "sound effects/objetos/golpeFruta.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/pilaDeLibros.png",
        { 0.f, 0.f },
        0.13f,
        1,
        "images/ModoInfinito/objetos/rotos/pilaDeLibrosTirados.png",
        "sound effects/objetos/golpeFruta.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/plato_torta_nocturno.png",
        { 0.f, 0.f },
        0.47f,
        1,
        "images/ModoInfinito/objetos/rotos/plato_torta_nocturno_roto.png",
        "sound effects/objetos/vidrioRoto.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/regadera.png",
        { 0.f, 0.f },
        0.14f,
        1,
        "images/ModoInfinito/objetos/rotos/regadera_rota.png",
        "sound effects/objetos/golpeMetal.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/reloj_despertador.png",
        { 0.f, 0.f },
        0.08f,
        1,
        "images/ModoInfinito/objetos/rotos/reloj_despertador_roto.png",
        "sound effects/objetos/golpeMetal.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/TazaCafe.png",
        { 0.f, 0.f },
        0.25f,
        1,
        "images/ModoInfinito/objetos/rotos/TazaCafe_rota.png",
        "sound effects/objetos/vidrioRoto.wav"
    ));

    _reserva.push_back(agregarObjeto(
        "images/ModoInfinito/objetos/vaso.png",
        { 0.f, 0.f },
        0.085f,
        1,
        "images/ModoInfinito/objetos/rotos/vaso_roto.png",
        "sound effects/objetos/vidrioRoto.wav"
    ));

    for (Objeto* objeto : _reserva)
    {
        objeto->colocarSobre({ 0.f, 0.f });
        retirarObjeto(objeto);
    }
}

void NivelModoInfinito::generarObjeto(ObjetoActivo& espacio)
{
    std::uniform_int_distribution<std::size_t> sortearTipo(0, _reserva.size() - 1);
    std::size_t tipo = sortearTipo(_generador);
    while (_reserva[tipo] == nullptr)
    {
        tipo = sortearTipo(_generador);
    }

    const std::size_t indicePlataforma = sortearPlataformaLibre();
    const sf::Vector2f& plataforma = POSICIONES_PLATAFORMAS[indicePlataforma];
    const sf::Vector2f apoyo(
        plataforma.x + (HITBOX_PLATAFORMA.left + HITBOX_PLATAFORMA.width / 2.f) * ESCALA_PLATAFORMA.x,
        plataforma.y + HITBOX_PLATAFORMA.top * ESCALA_PLATAFORMA.y
    );

    Objeto* objeto = _reserva[tipo];
    objeto->reiniciar();
    objeto->setGolpesNecesarios(calcularGolpesSiguienteObjeto());
    objeto->colocarSobre(apoyo);
    incorporarObjeto(objeto);
    _reserva[tipo] = nullptr;

    if (espacio.objeto != nullptr)
    {
        retirarObjeto(espacio.objeto);
        _reserva[espacio.tipo] = espacio.objeto;
    }
    espacio = { objeto, tipo, indicePlataforma };
    ++_objetosGenerados;
}

std::size_t NivelModoInfinito::sortearPlataformaLibre()
{
    std::array<bool, POSICIONES_PLATAFORMAS.size()> ocupadas{};
    for (const ObjetoActivo& activo : _objetosActivos)
    {
        if (activo.objeto != nullptr)
        {
            ocupadas[activo.plataforma] = true;
        }
    }

    std::uniform_int_distribution<std::size_t> sortear(0, ocupadas.size() - 1);
    std::size_t indice = sortear(_generador);
    while (ocupadas[indice])
    {
        indice = sortear(_generador);
    }
    return indice;
}

int NivelModoInfinito::calcularGolpesSiguienteObjeto() const
{
    const std::uint64_t grupo = _objetosGenerados / CANTIDAD_OBJETOS;
    constexpr std::uint64_t grupoMaximo = (INT_MAX - 1) / 2;
    return 1 + 2 * static_cast<int>(std::min(grupo, grupoMaximo));
}
