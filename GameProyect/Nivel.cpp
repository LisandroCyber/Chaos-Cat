#include "Nivel.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

Nivel::Nivel()
    : _spriteFondo(_texturaFondo),
      _mostrarHitboxes(false)
{
}

Nivel::~Nivel()
{
    for (Enemigo* enemigo : _enemigos)
    {
        delete enemigo;
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
    _anchoNivel = std::max(
        static_cast<float>(ANCHO_VENTANA),
        _spriteFondo.getGlobalBounds().width
    );
}

void Nivel::setAnchoNivel(float ancho)
{
    _anchoNivel = std::max(static_cast<float>(ANCHO_VENTANA), ancho);
}

void Nivel::agregarEnemigo(
    const std::string& rutaTextura,
    const sf::Vector2f& posicion,
    int frameAncho,
    int frameAlto,
    const sf::Vector2f& escala,
    bool seAsomaPorPuerta)
{
    Enemigo* enemigo = new Enemigo(
        rutaTextura,
        posicion,
        frameAncho,
        frameAlto,
        escala
    );

    if (seAsomaPorPuerta)
    {
        enemigo->configurarAsomada();
    }

    _enemigos.push_back(enemigo);
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
    float escala,
    int golpesNecesarios,
    const std::string& rutaTexturaCaida,
    const std::string& rutaSonidoCaida)
{
    _objetos.push_back(new Objeto(
        rutaTextura,
        posicion,
        escala,
        golpesNecesarios,
        rutaTexturaCaida,
        rutaSonidoCaida
    ));
}

void Nivel::agregarSuperficie(const sf::FloatRect& superficie)
{
    _superficiesFijas.push_back(superficie);
}

void Nivel::agregarZonaEscondite(const sf::FloatRect& zona)
{
    if (zona.width <= 0.f || zona.height <= 0.f)
    {
        return;
    }

    _zonasEscondite.push_back(zona);
    _halosEscondite.emplace_back();

    const int ancho = static_cast<int>(std::ceil(zona.width)) + RADIO_HALO_ESCONDITE * 2;
    const int alto = static_cast<int>(std::ceil(zona.height)) + RADIO_HALO_ESCONDITE * 2;
    const float mitadAncho = zona.width / 2.f;
    const float mitadAlto = zona.height / 2.f;
    const float radioEsquina = std::min(12.f, std::min(mitadAncho, mitadAlto));
    const float suavidad = 4.5f;
    const float opacidadMaxima = 85.f;
    sf::Image halo;
    halo.create(ancho, alto, sf::Color::Transparent);

    // La distancia al borde redondeado permite difuminar sin rellenar la zona.
    for (int y = 0; y < alto; y++)
    {
        for (int x = 0; x < ancho; x++)
        {
            const float dx = std::abs(x - RADIO_HALO_ESCONDITE + 0.5f - mitadAncho) -
                (mitadAncho - radioEsquina);
            const float dy = std::abs(y - RADIO_HALO_ESCONDITE + 0.5f - mitadAlto) -
                (mitadAlto - radioEsquina);
            const float exteriorX = std::max(dx, 0.f);
            const float exteriorY = std::max(dy, 0.f);
            const float distancia = std::sqrt(exteriorX * exteriorX + exteriorY * exteriorY) +
                std::min(std::max(dx, dy), 0.f) - radioEsquina;
            const float intensidad = std::exp(-distancia * distancia / (2.f * suavidad * suavidad));
            const sf::Uint8 opacidad = static_cast<sf::Uint8>(opacidadMaxima * intensidad);
            halo.setPixel(x, y, sf::Color(255, 255, 255, opacidad));
        }
    }

    sf::Texture& textura = _halosEscondite.back();
    if (!textura.loadFromImage(halo))
    {
        std::cout << "ERROR: NO SE PUDO CREAR EL HALO DEL ESCONDITE\n";
    }
    else
    {
        textura.setSmooth(true);
    }
}

void Nivel::actualizar(Personaje& gato)
{
    for (Enemigo* enemigo : _enemigos)
    {
        enemigo->actualizar();
    }

    for (Objeto* objeto : _objetos)
    {
        //la flecha llama al atributo o metodo si el objetoes un puntero
        const bool estabaEnElPiso = objeto->estaEnElPiso();
        objeto->update(_anchoNivel);

        //avisa solo en el momento del impacto, no en cada actualizacion.
        if (!estabaEnElPiso && objeto->estaEnElPiso())
        {
            for (Enemigo* enemigo : _enemigos)
            {
                enemigo->reaccionarACaida();
            }
        }
    }

    resolverColisiones(gato);
    actualizarEscondite(gato);
}

void Nivel::setPausado(bool pausado)
{
    for (Enemigo* enemigo : _enemigos)
    {
        enemigo->setPausado(pausado);
    }

    for (Objeto* objeto : _objetos)
    {
        objeto->setPausado(pausado);
    }
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
    limitarMovimientoGato(gato);
    // Primero resolvemos golpes y bloqueos laterales.
    for (Objeto* objeto : _objetos)
    {
        resolverColisionGatoObjeto(gato, *objeto);
    }

    // Reunimos las superficies sobre las que puede apoyarse.
    std::vector<sf::FloatRect> superficies;
    
    if(!gato.quiereBajarDeSuperficie())
    {
        for (Mueble* mueble : _muebles)
        {
            superficies.push_back(mueble->getGlobalBounds());
        }

        for (const sf::FloatRect& superficie : _superficiesFijas)
        {
            superficies.push_back(superficie);
        }
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

    resolverBarrerasLaterales(gato);

    limitarMovimientoGato(gato);
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

            objeto.recibirGolpe(direccion, gato.getNumeroGolpe());

            if (objeto.estaTirado())
            {
                return;
            }
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

    for (const Enemigo* enemigo : _enemigos)
    {
        enemigo->dibujar(ventana);
    }

    for (const Mueble* mueble : _muebles)
    {
        mueble->dibujar(ventana);
    }

    dibujarZonasEscondite(ventana);
    gato.dibujar(ventana);

    for (const Objeto* objeto : _objetos)
    {
        objeto->dibujar(ventana);
    }

    dibujarHitboxes(ventana, gato);
}

void Nivel::dibujarZonasEscondite(sf::RenderWindow& ventana) const
{
    for (std::size_t i = 0; i < _zonasEscondite.size(); i++)
    {
        if (_halosEscondite[i].getSize().x == 0)
        {
            continue;
        }

        sf::Sprite halo(_halosEscondite[i]);
        halo.setPosition(
            _zonasEscondite[i].left - RADIO_HALO_ESCONDITE,
            _zonasEscondite[i].top - RADIO_HALO_ESCONDITE);
        ventana.draw(halo);
    }
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

    for (const sf::FloatRect& barrera : _barrerasLaterales)
    {
        dibujarHitbox(ventana, barrera, sf::Color::Yellow);
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

bool Nivel::gatoFueDetectado(
    const Personaje& gato,
    const sf::View& camara) const
{
    const sf::Vector2f centro = camara.getCenter();
    const sf::Vector2f tamanio = camara.getSize();

    const sf::FloatRect areaVisible(
        centro.x - tamanio.x / 2.f,
        centro.y - tamanio.y / 2.f,
        tamanio.x,
        tamanio.y
    );

    for (const Enemigo* enemigo : _enemigos)
    {
        if (enemigo->detectaAl(gato, areaVisible))
        {
            return true;
        }
    }

    return false;
}

void Nivel::setVolumenMusica(float volumen)
{
    _musicaFondo.setVolume(volumen);
}

void Nivel::ocultarHitboxes()
{
    _mostrarHitboxes = false;
}

void Nivel::alternarHitboxes()
{
    _mostrarHitboxes = !_mostrarHitboxes;
}

bool Nivel::todosLosObjetosEnElPiso() const
{
    if (_objetos.empty())
    {
        return false;
    }

    for (const Objeto* objeto : _objetos)
    {
        if (!objeto->estaEnElPiso())
        {
            return false;
        }
    }

    return true;
}

float Nivel::getAnchoNivel() const
{
    return _anchoNivel;
}

void Nivel::limitarMovimientoGato(Personaje& gato)
{
    const sf::FloatRect area = gato.getGlobalBounds();

    if (area.left < 0.f)
    {
        gato.mover({ -area.left, 0.f });
    }
    else if (area.left + area.width > _anchoNivel)
    {
        gato.mover({
            _anchoNivel - (area.left + area.width),
            0.f
            });
    }
}

void Nivel::agregarBarreraLateral(const sf::FloatRect& barrera)
{
    _barrerasLaterales.push_back(barrera);
}

void Nivel::resolverBarrerasLaterales(Personaje& gato)
{
    for (const sf::FloatRect& barrera : _barrerasLaterales)
    {
        const sf::FloatRect area = gato.getGlobalBounds();

        if (!area.intersects(barrera))
        {
            continue;
        }

        const sf::FloatRect anterior = gato.getAreaAnterior();

        const float centroAnterior =
            anterior.left + anterior.width / 2.f;

        const float centroBarrera =
            barrera.left + barrera.width / 2.f;

        if (centroAnterior < centroBarrera)
        {
            gato.mover({
                barrera.left - (area.left + area.width),
                0.f
                });
        }
        else
        {
            gato.mover({
                barrera.left + barrera.width - area.left,
                0.f
                });
        }
    }
}
