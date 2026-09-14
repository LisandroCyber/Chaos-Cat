#include "Juego.h"
#include "Constantes.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

Juego::Juego()
    : _window(sf::VideoMode({ ANCHO_VENTANA, ALTO_VENTANA }), "Chaos Cat SFML 3"),
      _spriteFondo(_texturaFondo),
      _taza("images/TazaCafe.png", { 458.f, 490.f }, 0.2f),
      _heladera("images/heladera.png", { 3.f, 300.f }, { 0.25f, 0.272f },
          { { 177.f, 40.f }, { 695.f, 1459.f } }),
      _mesa("images/mesa-larga.png", { 356.06f, 400.f }, { 0.280825f, 0.384588f },
          { { 47.f, 293.f }, { 1442.f, 561.f } }),
      _hitboxCocina({ { 1090.f, 470.f }, { 202.f, 265.f } }),
      _tocandoTaza(false),
      _mostrarHitboxes(true)
{
    _window.setFramerateLimit(LIMITE_FPS);

    if (!_texturaFondo.loadFromFile("images/cocina.png"))
    {
        std::cout << "Error al cargar la imagen de fondo!" << std::endl;
        exit(-1);
    }

    _spriteFondo.setTexture(_texturaFondo, true);
}

void Juego::ejecutar()
{
    while (_window.isOpen())
    {
        procesarEventos();
        actualizar();
        dibujar();
    }
}

void Juego::procesarEventos()
{
    while (const auto event = _window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            _window.close();
        }
    }
}

void Juego::actualizar()
{
    _gato.update();
    resolverColisionesGato();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
    {
        std::cout << "Posision en x: " << _gato.getPosx() << std::endl;
        std::cout << "Posision en y: " << _gato.getPosy() << std::endl;
    }
}

void Juego::dibujar()
{
    _window.clear();
    _window.draw(_spriteFondo);
    _window.draw(_heladera);
    _window.draw(_mesa);
    _window.draw(_gato);
    _window.draw(_taza);
    dibujarHitboxes();
    _window.display();
}

void Juego::resolverColisionesGato()
{
    bool gatoApoyado = false;

    gatoApoyado = gatoPuedeApoyarseEn(_heladera.getGlobalBounds()) || gatoApoyado;
    gatoApoyado = gatoPuedeApoyarseEn(_hitboxCocina) || gatoApoyado;
    gatoApoyado = gatoPuedeApoyarseEn(_mesa.getGlobalBounds()) || gatoApoyado;
    gatoApoyado = resolverColisionGatoTaza() || gatoApoyado;

    if (!gatoApoyado)
    {
        _gato.iniciarCaidaSiEstaElevado();
    }
}

bool Juego::resolverColisionGatoTaza()
{
    const sf::FloatRect areaTaza = _taza.getGlobalBounds();
    const sf::FloatRect areaGolpe = _gato.getHitboxGolpe();

    if (_gato.estaGolpeando() && areaGolpe.findIntersection(areaTaza))
    {
        if (!_tocandoTaza)
        {
            std::cout << "TIRAR TAZA" << std::endl;
            _tocandoTaza = true;
        }
    }
    else
    {
        _tocandoTaza = false;
    }

    return gatoPuedeApoyarseEn(areaTaza);
}

bool Juego::gatoPuedeApoyarseEn(const sf::FloatRect& superficie)
{
    const sf::FloatRect areaGato = _gato.getGlobalBounds();
    const float gatoIzquierda = areaGato.position.x;
    const float gatoDerecha = areaGato.position.x + areaGato.size.x;
    const float superficieIzquierda = superficie.position.x;
    const float superficieDerecha = superficie.position.x + superficie.size.x;
    const float superficieArriba = superficie.position.y;
    const float baseGato = _gato.getBaseY();

    const bool seCruzanEnX = gatoDerecha > superficieIzquierda && gatoIzquierda < superficieDerecha;
    const bool gatoCercaDeArriba = baseGato >= superficieArriba - 8.f
        && baseGato <= superficieArriba + 30.f;

    if (seCruzanEnX && gatoCercaDeArriba)
    {
        _gato.apoyarEn(superficieArriba);
        return true;
    }

    return false;
}

void Juego::dibujarHitboxes()
{
    if (!_mostrarHitboxes)
    {
        return;
    }

    const sf::FloatRect hitboxGato = _gato.getGlobalBounds();
    sf::RectangleShape rectGato(hitboxGato.size);
    rectGato.setPosition(hitboxGato.position);
    rectGato.setFillColor(sf::Color::Transparent);
    rectGato.setOutlineColor(sf::Color::Green);
    rectGato.setOutlineThickness(2.f);

    const sf::FloatRect hitboxTaza = _taza.getGlobalBounds();
    sf::RectangleShape rectTaza(hitboxTaza.size);
    rectTaza.setPosition(hitboxTaza.position);
    rectTaza.setFillColor(sf::Color::Transparent);
    rectTaza.setOutlineColor(sf::Color::Red);
    rectTaza.setOutlineThickness(2.f);

    _window.draw(rectGato);
    _window.draw(rectTaza);

    if (_gato.estaGolpeando())
    {
        const sf::FloatRect hitboxGolpe = _gato.getHitboxGolpe();
        sf::RectangleShape rectGolpe(hitboxGolpe.size);
        rectGolpe.setPosition(hitboxGolpe.position);
        rectGolpe.setFillColor(sf::Color::Transparent);
        rectGolpe.setOutlineColor(sf::Color::Cyan);
        rectGolpe.setOutlineThickness(2.f);
        _window.draw(rectGolpe);
    }

    const sf::FloatRect hitboxHeladera = _heladera.getGlobalBounds();
    sf::RectangleShape rectHeladera(hitboxHeladera.size);
    rectHeladera.setPosition(hitboxHeladera.position);
    rectHeladera.setFillColor(sf::Color::Transparent);
    rectHeladera.setOutlineColor(sf::Color::Blue);
    rectHeladera.setOutlineThickness(2.f);

    sf::RectangleShape rectCocina(_hitboxCocina.size);
    rectCocina.setPosition(_hitboxCocina.position);
    rectCocina.setFillColor(sf::Color::Transparent);
    rectCocina.setOutlineColor(sf::Color::Magenta);
    rectCocina.setOutlineThickness(2.f);

    const sf::FloatRect hitboxMesa = _mesa.getGlobalBounds();
    sf::RectangleShape rectMesa(hitboxMesa.size);
    rectMesa.setPosition(hitboxMesa.position);
    rectMesa.setFillColor(sf::Color::Transparent);
    rectMesa.setOutlineColor(sf::Color::Yellow);
    rectMesa.setOutlineThickness(2.f);

    _window.draw(rectHeladera);
    _window.draw(rectCocina);
    _window.draw(rectMesa);
}
