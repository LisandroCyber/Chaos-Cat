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

void Nivel::actualizar(Personaje& gato)
{
    for (Objeto* objeto : _objetos)
    {
        objeto->update();
    }

    resolverColisiones(gato);
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
    bool gatoApoyado = false;

    for (Mueble* mueble : _muebles)
    {
        gatoApoyado = gatoPuedeApoyarseEn(gato, mueble->getGlobalBounds()) || gatoApoyado;
    }

    for (const sf::FloatRect& superficie : _superficiesFijas)
    {
        gatoApoyado = gatoPuedeApoyarseEn(gato, superficie) || gatoApoyado;
    }

    for (Objeto* objeto : _objetos)
    {
        gatoApoyado = resolverColisionGatoObjeto(gato, *objeto) || gatoApoyado;
    }

    if (!gatoApoyado)
    {
        gato.iniciarCaidaSiEstaElevado();
    }
}

bool Nivel::resolverColisionGatoObjeto(Personaje& gato, Objeto& objeto)
{
    if (objeto.estaTirado())
    {
        return false;
    }

    const sf::FloatRect areaObjeto = objeto.getGlobalBounds();
    const sf::FloatRect areaGolpe = gato.getHitboxGolpe();
    const sf::FloatRect areaGato = gato.getGlobalBounds();

    if (gato.estaGolpeando() && areaGolpe.findIntersection(areaObjeto))
    {
        const float centroGato = areaGato.position.x + areaGato.size.x / 2.f;
        const float centroObjeto = areaObjeto.position.x + areaObjeto.size.x / 2.f;
        const float direccion = centroObjeto >= centroGato ? 1.f : -1.f;

        objeto.tirar(direccion);
        return false;
    }

    return gatoPuedeApoyarseEn(gato, areaObjeto);
}

bool Nivel::gatoPuedeApoyarseEn(Personaje& gato,
    const sf::FloatRect& superficie) const
{
    const sf::FloatRect areaGato = gato.getGlobalBounds();
    const float gatoIzquierda = areaGato.position.x;
    const float gatoDerecha = areaGato.position.x + areaGato.size.x;
    const float superficieIzquierda = superficie.position.x;
    const float superficieDerecha = superficie.position.x + superficie.size.x;
    const float superficieArriba = superficie.position.y;
    const float baseGato = gato.getBaseY();

    const bool seCruzanEnX = gatoDerecha > superficieIzquierda && gatoIzquierda < superficieDerecha;
    const bool gatoCercaDeArriba = baseGato >= superficieArriba - 8.f
        && baseGato <= superficieArriba + 30.f;

    if (seCruzanEnX && gatoCercaDeArriba)
    {
        gato.apoyarEn(superficieArriba);
        return true;
    }

    return false;
}

void Nivel::dibujar(sf::RenderWindow& ventana,
    const Personaje& gato) const
{
    ventana.draw(_spriteFondo);

    for (const Humano* humano : _humanos)
    {
        ventana.draw(*humano);
    }

    for (const Mueble* mueble : _muebles)
    {
        ventana.draw(*mueble);
    }

    ventana.draw(gato);

    for (const Objeto* objeto : _objetos)
    {
        ventana.draw(*objeto);
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
}

void Nivel::dibujarHitbox(sf::RenderWindow& ventana,
    const sf::FloatRect& hitbox,
    const sf::Color& color)
{
    sf::RectangleShape rectangulo(hitbox.size);
    rectangulo.setPosition(hitbox.position);
    rectangulo.setFillColor(sf::Color::Transparent);
    rectangulo.setOutlineColor(color);
    rectangulo.setOutlineThickness(2.f);

    ventana.draw(rectangulo);
}
