#include "TablaPuntos.h"
#include "Constantes.h"
#include <cstdio>
#include <string>
#include <iostream>

TablaPuntos::TablaPuntos()
    : Menu(1)
{
    if (_texturaFondo.loadFromFile("images/UI/mejoresPuntajes.png"))
    {
        _fondo.setTexture(_texturaFondo, true);

        const sf::Vector2u tamano = _texturaFondo.getSize();
        _fondo.setScale(1280.f / tamano.x, 720.f / tamano.y);
    }
    _titulo.setString("MEJORES PUNTAJES");
    _titulo.setCharacterSize(48);
    _titulo.setPosition(390.f, 100.f);

    _opciones[0].setString("Volver");
    _opciones[0].setPosition(550.f, 580.f);

    FILE* archivo = std::fopen("puntajes.dat", "rb");

    if (archivo != nullptr)
    {
        int guardados[PUNTAJES]{};

        if (std::fread(guardados, sizeof(int), PUNTAJES, archivo) == PUNTAJES)
        {
            for (int i = 0; i < PUNTAJES; i++)
            {
                _mejores[i] = guardados[i];
            }
        }

        std::fclose(archivo);
    }
}

void TablaPuntos::registrar(int puntos)
{
    if (puntos <= _mejores[PUNTAJES - 1])
    {
        return;
    }

    _mejores[PUNTAJES - 1] = puntos;

    // Ordenamiento burbuja, de mayor a menor.
    for (int i = 0; i < PUNTAJES - 1; i++)
    {
        for (int j = 0; j < PUNTAJES - 1 - i; j++)
        {
            if (_mejores[j] < _mejores[j + 1])
            {
                int auxiliar = _mejores[j];
                _mejores[j] = _mejores[j + 1];
                _mejores[j + 1] = auxiliar;
            }
        }
    }

    FILE* archivo = std::fopen("puntajes.dat", "wb");

    if (archivo != nullptr)
    {
        std::fwrite(_mejores, sizeof(int), PUNTAJES, archivo);
        std::fclose(archivo);
    }
}

void TablaPuntos::draw(sf::RenderTarget& destino,
    sf::RenderStates estados) const
{
    destino.draw(_fondo, estados);
    Menu::draw(destino, estados);

    std::string contenido;

    for (int i = 0; i < CANTIDAD; i++)
    {
        contenido += std::to_string(i + 1) + ". ";

        if (_mejores[i] > 0)
        {
            contenido += std::to_string(_mejores[i]);
        }
        else
        {
            contenido += "-";
        }

        contenido += '\n';
    }

    sf::Text texto(contenido, _fuente, 32);
    texto.setPosition(550.f, 220.f);
    destino.draw(texto, estados);
}