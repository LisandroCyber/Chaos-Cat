#include "Nivel.h"

#include <cstdlib>
#include <iostream>

Nivel::Nivel()
    : _spriteFondo(_texturaFondo),
      _mostrarHitboxes(true)
{
}

Nivel::~Nivel()
{
    for (Humano* humano : _humanos)
    {
        delete humano;
    }

    for (Mueble* mueble : _muebles)
    {
        delete mueble;
    }

    for (Objeto* objeto : _objetos)
    {
        delete objeto;
    }
}

void Nivel::cargarFondo(const std::string& rutaTextura)
{
    if (!_texturaFondo.loadFromFile(rutaTextura))
    {
        std::cout << "ERROR: NO SE PUDO CARGAR EL FONDO " << rutaTextura << '\n';
        exit(-1);
    }

    _spriteFondo.setTexture(_texturaFondo, true);
}

void Nivel::agregarHumano(const std::string& rutaTextura,
    const sf::Vector2f& posicion,
    int frameAncho,
    int frameAlto,
    const sf::Vector2f& escala)
{
    _humanos.push_back(new Humano(
        rutaTextura,
        posicion,
        frameAncho,
        frameAlto,
        escala
    ));
}

void Nivel::agregarMueble(const std::string& rutaTextura,
    const sf::Vector2f& posicion,
    const sf::Vector2f& escala,
    const sf::FloatRect& hitboxLocal)
{
    _muebles.push_back(new Mueble(
        rutaTextura,
        posicion,
        escala,
        hitboxLocal
    ));
}

void Nivel::agregarObjeto(const std::string& rutaTextura,
    const sf::Vector2f& posicion,
    float escala)
{
    _objetos.push_back(new Objeto(
        rutaTextura,
        posicion,
        escala
    ));
}

void Nivel::agregarSuperficie(const sf::FloatRect& superficie)
{
    _superficiesFijas.push_back(superficie);
}

void Nivel::agregarZonaEscondite(const sf::FloatRect& zona)
{
    _zonasEscondite.push_back(zona);
}

void Nivel::actualizar(Personaje& gato)
{
    for (Objeto* objeto : _objetos)
    {
        objeto->update();
    }

    resolverColisiones(gato);
    actualizarEscondite(gato);
}

void Nivel::actualizarEscondite(Personaje& gato)
{
    if (!gato.estaAgachado())
    {
        gato.setEscondido(false);
        return;
    }

    const sf::FloatRect areaGato = gato.getGlobalBounds();
    const float derechaGato = areaGato.left + areaGato.width;
    const float abajoGato = areaGato.top + areaGato.height;

    for (const sf::FloatRect& zona : _zonasEscondite)
    {
        const float derechaZona = zona.left + zona.width;
        const float abajoZona = zona.top + zona.height;

        // Toda la hitbox debe quedar dentro de la zona de escondite.
        const bool estaDentro =
            areaGato.left >= zona.left &&
            derechaGato <= derechaZona &&
            areaGato.top >= zona.top &&
            abajoGato <= abajoZona;

        if (estaDentro)
        {
            gato.setEscondido(true);
            return;
        }
    }

    gato.setEscondido(false);
}

void Nivel::reiniciarObjetos()
{
    for (Objeto* objeto : _objetos)
    {
        objeto->reiniciar();
    }
}

void Nivel::resolverColisiones(Personaje& gato)
{
    // Primero resolvemos golpes y bloqueos laterales.
    for (Objeto* objeto : _objetos)
    {
        resolverColisionGatoObjeto(gato, *objeto);
    }

    // Reunimos las superficies sobre las que puede apoyarse.
    std::vector<sf::FloatRect> superficies;

    for (Mueble* mueble : _muebles)
    {
        superficies.push_back(mueble->getGlobalBounds());
    }

    for (const sf::FloatRect& superficie : _superficiesFijas)
    {
        superficies.push_back(superficie);
    }

    for (Objeto* objeto : _objetos)
    {
        if (!objeto->estaTirado())
        {
            superficies.push_back(objeto->getGlobalBounds());
        }
    }

    bool gatoApoyado = false;
    float alturaApoyo = 0.f;

    for (const sf::FloatRect& superficie : superficies)
    {
        if (gatoPuedeApoyarseEn(gato, superficie))
        {
            // Si cruzó varias superficies al caer, elegimos
            // la más alta: en pantalla tiene menor coordenada Y.
            if (!gatoApoyado || superficie.top < alturaApoyo)
            {
                alturaApoyo = superficie.top;
                gatoApoyado = true;
            }
        }
    }

    // Ajustamos la altura una sola vez.
    if (gatoApoyado)
    {
        gato.apoyarEn(alturaApoyo);
    }
    else
    {
        gato.iniciarCaidaSiEstaElevado();
    }
}

void Nivel::resolverColisionGatoObjeto(Personaje& gato, Objeto& objeto)
{
    if (objeto.estaTirado())
    {
        return;
    }

    const sf::FloatRect areaObjeto = objeto.getGlobalBounds();
    const sf::FloatRect areaGato = gato.getGlobalBounds();
    const sf::FloatRect areaAnterior = gato.getAreaAnterior();

    const bool puedeApoyarse =
        gatoPuedeApoyarseEn(gato, areaObjeto);

    // Conserve el golpe frontal y el golpe desde arriba.
    if (gato.estaGolpeando())
    {

        const bool golpeFrontal =
            gato.getHitboxGolpe().intersects(areaObjeto);

        if (golpeFrontal || puedeApoyarse)
        {
            const float centroGato =
                areaGato.left + areaGato.width / 2.f;

            const float centroObjeto =
                areaObjeto.left + areaObjeto.width / 2.f;

            const float direccion =
                centroGato <= centroObjeto ? 1.f : -1.f;

            objeto.tirar(direccion);
            return;
        }
    }

    // Si viene cayendo desde arriba, la función principal resuelve el apoyo.
    
    if (puedeApoyarse)
    {
        return;
    }

    sf::FloatRect interseccion;

    if (!areaGato.intersects(areaObjeto, interseccion))
    {
        return;
    }

    // Resuelve las colisiones laterales, corrigiendo la posision del gato
    // moviendolo la cantidad de pixeles de la intereccion, hacia
    // el lado donde sea la colision

    const float derechaAnterior =
        areaAnterior.left + areaAnterior.width;

    const float derechaObjeto =
        areaObjeto.left + areaObjeto.width;

    if (derechaAnterior <= areaObjeto.left)
    {
        // Entró por el costado izquierdo.
        const float correccion =
            areaObjeto.left - (areaGato.left + areaGato.width);

        gato.mover({ correccion, 0.f });
    }
    else if (areaAnterior.left >= derechaObjeto)
    {
        // Entró por el costado derecho.
        const float correccion =
            derechaObjeto - areaGato.left;

        gato.mover({ correccion, 0.f });
    }
    else
    {
        // Si ya había superposición, por ejemplo porque
        // cambió el tamaño de la hitbox al cambiar de estado,
        // corregimos hacia el lado donde estaba el gato.
        const float centroAnterior =
            areaAnterior.left + areaAnterior.width / 2.f;

        const float centroObjeto =
            areaObjeto.left + areaObjeto.width / 2.f;

        if (centroAnterior < centroObjeto)
        {
            gato.mover({
                areaObjeto.left - (areaGato.left + areaGato.width),
                0.f
                });
        }
        else
        {
            gato.mover({
                derechaObjeto - areaGato.left,
                0.f
                });
        }
    }
}

bool Nivel::gatoPuedeApoyarseEn(Personaje& gato,
    const sf::FloatRect& superficie) const
{
    const sf::FloatRect areaGato = gato.getGlobalBounds();

    const float baseAnterior = gato.getBaseAnterior();
    const float baseActual = gato.getBaseY();

    // Si está subiendo, atraviesa la plataforma.
    if (baseActual < baseAnterior)
    {
        return false;
    }

    const bool seCruzanEnX =
        areaGato.left < superficie.left + superficie.width &&
        areaGato.left + areaGato.width > superficie.left;

    // Margen pequeño para errores de precisión decimal.
    const float tolerancia = 0.5f;

    const bool antesEstabaArriba =
        baseAnterior <= superficie.top + tolerancia;

    const bool ahoraAlcanzoLaSuperficie =
        baseActual >= superficie.top - tolerancia;

    return seCruzanEnX &&
        antesEstabaArriba &&
        ahoraAlcanzoLaSuperficie;
}

void Nivel::dibujar(sf::RenderWindow& ventana,
    const Personaje& gato) const
{
    ventana.draw(_spriteFondo);

    for (const Humano* humano : _humanos)
    {
        humano->dibujar(ventana);
    }

    for (const Mueble* mueble : _muebles)
    {
        mueble->dibujar(ventana);
    }

    gato.dibujar(ventana);

    for (const Objeto* objeto : _objetos)
    {
        objeto->dibujar(ventana);
    }

    dibujarHitboxes(ventana, gato);
}

void Nivel::dibujarHitboxes(sf::RenderWindow& ventana,
    const Personaje& gato) const
{
    if (!_mostrarHitboxes)
    {
        return;
    }

    dibujarHitbox(ventana, gato.getGlobalBounds(), sf::Color::Green);

    for (const Objeto* objeto : _objetos)
    {
        dibujarHitbox(ventana, objeto->getGlobalBounds(), sf::Color::Red);
    }

    if (gato.estaGolpeando())
    {
        dibujarHitbox(ventana, gato.getHitboxGolpe(), sf::Color::Cyan);
    }

    for (const Mueble* mueble : _muebles)
    {
        dibujarHitbox(ventana, mueble->getGlobalBounds(), sf::Color::Blue);
    }

    for (const sf::FloatRect& superficie : _superficiesFijas)
    {
        dibujarHitbox(ventana, superficie, sf::Color::Magenta);
    }

    for (const sf::FloatRect& zona : _zonasEscondite)
    {
        dibujarHitbox(ventana, zona, sf::Color(128, 0, 32));
    }
}

void Nivel::dibujarHitbox(sf::RenderWindow& ventana,
    const sf::FloatRect& hitbox,
    const sf::Color& color)
{
    sf::RectangleShape rectangulo(sf::Vector2f(hitbox.width, hitbox.height));
    rectangulo.setPosition(hitbox.left, hitbox.top);
    rectangulo.setFillColor(sf::Color::Transparent);
    rectangulo.setOutlineColor(color);
    rectangulo.setOutlineThickness(2.f);

    ventana.draw(rectangulo);
}

bool Nivel::cargarMusicaFondo(const std::string& rutaMusica, float volumen)
{
    if (!_musicaFondo.openFromFile(rutaMusica))
    {
        std::cout << "No se pudo cargar la musica: "
            << rutaMusica << "\n";

        return false;
    }

    _musicaFondo.setVolume(volumen);
    _musicaFondo.setLoop(true);

    return true;
}


void Nivel::configurarLoopMusica(sf::Time inicioLoop,
    sf::Time duracionLoop)
{
    _musicaFondo.setLoopPoints({
        inicioLoop,
        duracionLoop
        });
}

void Nivel::reproducirMusicaFondo(sf::Time inicioReproduccion)
{
    _musicaFondo.setPlayingOffset(inicioReproduccion);
    _musicaFondo.play();
}

void Nivel::pausarMusica()
{
    _musicaFondo.pause();
}

void Nivel::continuarMusica()
{
    if (_musicaFondo.getStatus() != sf::SoundSource::Playing)
    {
        _musicaFondo.play();
    }
}
