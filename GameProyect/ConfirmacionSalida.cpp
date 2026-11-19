#include "ConfirmacionSalida.h"

ConfirmacionSalida::ConfirmacionSalida()
{
    _titulo.setString("Salir del juego?");
    _titulo.setCharacterSize(32);

    _opciones[0].setString("Si");
    _opciones[1].setString("No");

    for (int i = 0; i < 2; i++)
    {
        _opciones[i].setCharacterSize(30);
    }

    reiniciarSeleccion();
}

void ConfirmacionSalida::reiniciarSeleccion()
{
    _seleccion = 1;
}

void ConfirmacionSalida::acomodarTextos(
    sf::Text& titulo,
    sf::Text* opciones,
    const sf::RenderTarget& destino) const
{
    const sf::Vector2f centro = destino.getView().getCenter();

    sf::FloatRect area = titulo.getLocalBounds();

    titulo.setOrigin(
        area.left + area.width / 2.f,
        area.top
    );

    titulo.setPosition(centro.x, centro.y - 65.f);

    for (int i = 0; i < 2; i++)
    {
        area = opciones[i].getLocalBounds();

        opciones[i].setOrigin(
            area.left + area.width / 2.f,
            area.top
        );

        opciones[i].setPosition(
            centro.x + (i == 0 ? -100.f : 100.f),
            centro.y + 30.f
        );
    }
}

int ConfirmacionSalida::procesarEvento(
    const sf::Event& evento,
    const sf::RenderWindow& ventana)
{
    acomodarTextos(_titulo, _opciones, ventana);

    if (evento.type == sf::Event::KeyPressed)
    {
        if (evento.key.code == sf::Keyboard::Escape)
        {
            return 1;
        }

        if (evento.key.code == sf::Keyboard::Left ||
            evento.key.code == sf::Keyboard::Right)
        {
            _seleccion = 1 - _seleccion;
            return -1;
        }
    }

    return Menu::procesarEvento(evento, ventana);
}

void ConfirmacionSalida::draw(
    sf::RenderTarget& destino,
    sf::RenderStates estados) const
{
    // El dibujo y el mouse usan las coordenadas de la vista, no los pixeles.
    const sf::View& vista = destino.getView();
    const sf::Vector2f centro = vista.getCenter();
    const sf::Vector2f tamano = vista.getSize();

    sf::RectangleShape fondo(tamano);
    fondo.setPosition(centro.x - tamano.x / 2.f, centro.y - tamano.y / 2.f);
    fondo.setFillColor(sf::Color(0, 0, 0, 180));
    destino.draw(fondo, estados);

    sf::RectangleShape cuadro(sf::Vector2f(500.f, 220.f));
    cuadro.setPosition(centro.x - 250.f, centro.y - 110.f);
    cuadro.setFillColor(sf::Color(40, 40, 55));
    cuadro.setOutlineThickness(2.f);
    cuadro.setOutlineColor(sf::Color::White);
    destino.draw(cuadro, estados);

    // El dibujo trabaja con copias porque este metodo es const.
    sf::Text titulo = _titulo;
    sf::Text opciones[2] = { _opciones[0], _opciones[1] };

    acomodarTextos(titulo, opciones, destino);

    destino.draw(titulo, estados);

    for (int i = 0; i < 2; i++)
    {
        opciones[i].setFillColor(
            i == _seleccion ? sf::Color::Yellow : sf::Color::White
        );

        destino.draw(opciones[i], estados);
    }
}
