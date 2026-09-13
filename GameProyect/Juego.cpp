#include "Juego.h"
#include "Constantes.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

Juego::Juego()
    : _window(sf::VideoMode({ ANCHO_VENTANA, ALTO_VENTANA }), "Chaos Cat SFML 3"),
      _spriteFondo(_texturaFondo),
      _taza("images/TazaCafe.png", { 458.f, 478.f }, 0.2f),
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
    resolverColisionGatoTaza();

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
    _window.draw(_gato);
    _window.draw(_taza);
    dibujarHitboxes();
    _window.display();
}

void Juego::resolverColisionGatoTaza()
{
    const sf::FloatRect areaTaza = _taza.getGlobalBounds();
    const sf::FloatRect areaGato = _gato.getGlobalBounds();
    bool gatoApoyadoSobreTaza = false;

    float gatoIzquierda = areaGato.position.x;
    float gatoDerecha = areaGato.position.x + areaGato.size.x;
    float baseGato = _gato.getBaseY();

    float tazaIzquierda = areaTaza.position.x;
    float tazaDerecha = areaTaza.position.x + areaTaza.size.x;
    float tazaArriba = areaTaza.position.y;

    bool seCruzanEnX = gatoDerecha > tazaIzquierda && gatoIzquierda < tazaDerecha;
    bool gatoCercaDeArriba = baseGato >= tazaArriba - 8.f && baseGato <= tazaArriba + 30.f;

    if (areaGato.findIntersection(areaTaza))
    {
        if (!_tocandoTaza)
        {
            std::cout << "TIRAR TAZA" << std::endl;
            _tocandoTaza = true;
        }

        if (seCruzanEnX && gatoCercaDeArriba)
        {
            _gato.apoyarEn(tazaArriba);
            gatoApoyadoSobreTaza = true;
        }
    }
    else
    {
        _tocandoTaza = false;

        if (seCruzanEnX && gatoCercaDeArriba)
        {
            gatoApoyadoSobreTaza = true;
        }
    }

    if (!gatoApoyadoSobreTaza)
    {
        _gato.iniciarCaidaSiEstaElevado();
    }
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
}
