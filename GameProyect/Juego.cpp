#include "Juego.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

Juego::Juego()
    : _window(sf::VideoMode({ 1280, 720 }), "Chaos Cat SFML 3"),
      _spriteFondo(_texturaFondo),
      _tocandoTaza(false),
      _mostrarHitboxes(true)
{
    _window.setFramerateLimit(144);

    if (!_texturaFondo.loadFromFile("images/fondo.jpg"))
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

    // M para mostrar posision del gato (para debug)
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
    // tolerancia en px de las medidas necesarias para la colision superior
    const float TOLERANCIA_ABAJO = 8.f;
    const float TOLERANCIA_ARRIBA = 30.f;
    bool gatoApoyadoSobreTaza = false;

    float gatoIzquierdaHit = areaGato.position.x;
    float gatoDerechaHit = areaGato.position.x + areaGato.size.x;
    float gatoArribaHit = areaGato.position.y + areaGato.size.y; 
    float baseGato = _gato.getBaseY();

    float tazaIzquierdaHit = areaTaza.position.x;
    float tazaDerechaHit = areaTaza.position.x + areaTaza.size.x;
    float tazaArribaHit = areaTaza.position.y;
    float tazaAbajoHit = tazaArribaHit + areaTaza.size.y;

    bool seCruzanEnX = gatoDerechaHit > tazaIzquierdaHit && gatoIzquierdaHit < tazaDerechaHit;
    bool gatoCercaDeArriba = baseGato >= tazaArribaHit - TOLERANCIA_ABAJO && baseGato <= tazaArribaHit + TOLERANCIA_ARRIBA;
    
    bool gatoGolpeaTecho = gatoArribaHit <= tazaAbajoHit + TOLERANCIA_ARRIBA && gatoArribaHit >= tazaAbajoHit - TOLERANCIA_ABAJO;

    if (areaGato.findIntersection(areaTaza))
    {
        if (!_tocandoTaza)
        {
            std::cout << "TIRAR TAZA" << std::endl;
            _tocandoTaza = true;
        }
        // si se cruzan en X y el gato cae sobre la parte superior de la taza -> Apoyado obre taza
        if (seCruzanEnX && gatoCercaDeArriba)
        {
            _gato.apoyarEn(tazaArribaHit);
            gatoApoyadoSobreTaza = true;
        }
        // si se cruzan en X y la cabeza pega con la parte inferior de la taza -> chocar techo
        else if (seCruzanEnX && gatoGolpeaTecho)
        {
            _gato.chocarTecho(tazaAbajoHit);
            _tocandoTaza = false;
            
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
