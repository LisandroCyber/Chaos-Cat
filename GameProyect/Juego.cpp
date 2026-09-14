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
    _taza.update();
    resolverColisionGatoTaza();
    procesarLanzamientoTaza();

    // R permite volver a colocar la taza para probar el lanzamiento otra vez.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
    {
        _taza.reiniciar();
    }

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
    // Una vez lanzada, la taza se mueve libremente y deja de funcionar
    // como superficie de colision para el gato.
    if (_taza.estaTirado())
    {
        _gato.iniciarCaidaSiEstaElevado();
        return;
    }

    const sf::FloatRect areaTaza = _taza.getGlobalBounds();
    const sf::FloatRect areaGato = _gato.getGlobalBounds();
    // tolerancias (en px) para considerar que el gato alcanza a la taza.
    const float TOLERANCIA_ABAJO = 8.f;
    const float TOLERANCIA_ARRIBA = 30.f;
    bool gatoApoyadoSobreTaza = false;

    const float gatoIzquierdaHit = areaGato.position.x;
    const float gatoDerechaHit = areaGato.position.x + areaGato.size.x;
    const float gatoSuperiorHit = areaGato.position.y;
    const float gatoInferiorHit = areaGato.position.y + areaGato.size.y;
    const float baseGato = _gato.getBaseY();

    const float tazaIzquierdaHit = areaTaza.position.x;
    const float tazaDerechaHit = areaTaza.position.x + areaTaza.size.x;
    const float tazaArribaHit = areaTaza.position.y;
    const float tazaAbajoHit = tazaArribaHit + areaTaza.size.y;

    const bool seCruzanEnX = gatoDerechaHit > tazaIzquierdaHit && gatoIzquierdaHit < tazaDerechaHit;

    const bool gatoCercaDeArriba =
        baseGato >= tazaArribaHit - TOLERANCIA_ABAJO && baseGato <= tazaArribaHit + TOLERANCIA_ARRIBA;

    const bool gatoGolpeaTecho =
        gatoInferiorHit <= tazaAbajoHit + TOLERANCIA_ARRIBA && gatoInferiorHit >= tazaAbajoHit - TOLERANCIA_ABAJO;

    const bool gatoTocaTaza = areaGato.findIntersection(areaTaza).has_value();
    const bool gatoArribaDeTaza = seCruzanEnX && gatoCercaDeArriba;

    // el gato puede apoyarse sobre la taza o chocar con su parte inferior.
    if (gatoTocaTaza)
    {
        if (gatoArribaDeTaza)
        {
            _gato.apoyarEn(tazaArribaHit);
            gatoApoyadoSobreTaza = true;
        }
        else if (seCruzanEnX && gatoGolpeaTecho)
        {
            _gato.chocarTecho(tazaAbajoHit);
        }
    }
    else
    {
        if (gatoArribaDeTaza)
        {
            gatoApoyadoSobreTaza = true;
        }
    }

    if (!gatoApoyadoSobreTaza)
    {
        _gato.iniciarCaidaSiEstaElevado();
    }
}

void Juego::procesarLanzamientoTaza()
{
    if (_taza.estaTirado())
    {
        _tocandoTaza = false;
        return;
    }

    const sf::FloatRect areaTaza = _taza.getGlobalBounds();
    const sf::FloatRect areaGato = _gato.getGlobalBounds();
    // tolerancias (en px) para considerar que el gato alcanza a la taza.
    const float TOLERANCIA_ABAJO = 8.f;
    const float TOLERANCIA_ARRIBA = 30.f;
    const float TOLERANCIA_COSTADO = 10.f;

    const float gatoArribaHit = areaGato.position.y;
    const float gatoAbajoHit = areaGato.position.y + areaGato.size.y;
    const float gatoIzquierdaHit = areaGato.position.x;
    const float gatoDerechaHit = areaGato.position.x + areaGato.size.x;
    const float baseGato = _gato.getBaseY();

    const float tazaArribaHit = areaTaza.position.y;
    const float tazaAbajoHit = tazaArribaHit + areaTaza.size.y;
    const float tazaIzquierdaHit = areaTaza.position.x;
    const float tazaDerechaHit = areaTaza.position.x + areaTaza.size.x;

    const bool seCruzanEnX = gatoDerechaHit > tazaIzquierdaHit && gatoIzquierdaHit < tazaDerechaHit;
    const bool seCruzanEnY = gatoAbajoHit > tazaArribaHit && gatoArribaHit < tazaAbajoHit;

    const bool gatoCercaDeArriba = baseGato >= tazaArribaHit - TOLERANCIA_ABAJO && baseGato <= tazaArribaHit + TOLERANCIA_ARRIBA;

    // el gato puede tirar la taza si la toca, si la alcanza por un costado o si esta arriba de ella.
    const bool gatoTocaTaza = areaGato.findIntersection(areaTaza).has_value();
    const bool gatoEnCostadoIzquierdo =
        seCruzanEnY && gatoDerechaHit >= tazaIzquierdaHit - TOLERANCIA_COSTADO
        && gatoDerechaHit <= tazaIzquierdaHit + TOLERANCIA_COSTADO;

    const bool gatoEnCostadoDerecho =
        seCruzanEnY && gatoIzquierdaHit >= tazaDerechaHit - TOLERANCIA_COSTADO
        && gatoIzquierdaHit <= tazaDerechaHit + TOLERANCIA_COSTADO;

    const bool gatoArribaDeTaza = seCruzanEnX && gatoCercaDeArriba;

    const bool puedeTirar =
        gatoTocaTaza || gatoEnCostadoIzquierdo || gatoEnCostadoDerecho || gatoArribaDeTaza;

    if (puedeTirar && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        // Espacio lanza la taza hacia el lado en el que se encuentra respecto del gato.
        const float centroGato = areaGato.position.x + areaGato.size.x / 2.f;
        const float centroTaza = areaTaza.position.x + areaTaza.size.x / 2.f;
        const float direccion = centroTaza >= centroGato ? 1.f : -1.f;

        _taza.tirar(direccion);
        _tocandoTaza = false;
        _gato.iniciarCaidaSiEstaElevado();
        return;
    }

    if (puedeTirar)
    {
        if (!_tocandoTaza)
        {
            std::cout << "Toca ESPACIO para tirar la taza" << std::endl;
            _tocandoTaza = true;
        }
    }
    else
    {
        _tocandoTaza = false;
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
