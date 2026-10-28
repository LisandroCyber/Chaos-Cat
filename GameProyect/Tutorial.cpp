#include "Tutorial.h"
#include <algorithm>
#include <iostream>
#include <string>

Tutorial::Tutorial()
{
    _fuente.loadFromFile("fonts/Starcatcher.ttf");
    abrir();
}

void Tutorial::abrir()
{
    _pagina = 0;
    cargarImagen();
}

void Tutorial::cargarImagen()
{
    std::string ruta = "images/Tutorial/tutorial" +
        std::to_string(_pagina + 1) + ".png";

    if (!_textura.loadFromFile(ruta))
    {
        std::cout << "No se pudo cargar: " << ruta << '\n';
        return;
    }

    _imagen.setTexture(_textura, true);

    const sf::Vector2u tamano = _textura.getSize();

    float escala = std::min(
        1280.f / tamano.x,
        630.f / tamano.y
    );

    _imagen.setScale(escala, escala);
    _imagen.setPosition(
        (1280.f - tamano.x * escala) / 2.f,
        (630.f - tamano.y * escala) / 2.f
    );
}

int Tutorial::procesarEvento(
    const sf::Event& evento,
    const sf::RenderWindow& ventana)
{
    int cambio = 0;

    if (evento.type == sf::Event::KeyPressed)
    {
        if (evento.key.code == sf::Keyboard::Escape)
            return 0;

        if (evento.key.code == sf::Keyboard::Left)
            cambio = -1;

        if (evento.key.code == sf::Keyboard::Right ||
            evento.key.code == sf::Keyboard::Enter)
            cambio = 1;
    }

    if (evento.type == sf::Event::MouseButtonPressed &&
        evento.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mouse = ventana.mapPixelToCoords(
            { evento.mouseButton.x, evento.mouseButton.y },
            ventana.getDefaultView()
        );

        if (sf::FloatRect(80, 650, 220, 45).contains(mouse))
            cambio = -1;

        if (sf::FloatRect(1000, 650, 250, 45).contains(mouse))
            cambio = 1;
    }

    // En la ultima pagina, avanzar significa volver al Menu Principal.
    if (cambio == 1 && _pagina == 3)
        return 1;

    if (cambio != 0 && _pagina + cambio >= 0)
    {
        _pagina += cambio;
        cargarImagen();
    }

    return -1;
}

void Tutorial::draw(
    sf::RenderTarget& destino,
    sf::RenderStates estados) const
{
    sf::RectangleShape fondo({ 1280.f, 720.f });
    fondo.setFillColor(sf::Color(20, 20, 30));

    destino.draw(fondo, estados);
    destino.draw(_imagen, estados);

    sf::Text texto("", _fuente, 28);

    texto.setString("Anterior");
    texto.setFillColor(_pagina == 0
        ? sf::Color(120, 120, 120)
        : sf::Color::White);
    texto.setPosition(80.f, 650.f);
    destino.draw(texto, estados);

    texto.setFillColor(sf::Color::White);
    texto.setString(std::to_string(_pagina + 1) + " / 4");
    texto.setPosition(600.f, 650.f);
    destino.draw(texto, estados);

    texto.setFillColor(sf::Color::Yellow);
    texto.setString(_pagina == 3 ? "Volver al menu" : "Siguiente");
    texto.setPosition(1000.f, 650.f);
    destino.draw(texto, estados);
}