#pragma once
#include <SFML/Graphics.hpp>
#include "Constantes.h"

class MenuSeleccionNivel : public sf::Drawable
{
private:
    sf::Texture _texturaFondo;
    sf::Texture _texturaMapa;
    sf::Texture _texturaMarcador;
    sf::Sprite _fondo;
    sf::Sprite _mapa;
    sf::Sprite _marcador;

    sf::Font _fuente;
    sf::Text _titulo;
    sf::Text _nombres[CANTIDAD_NIVELES];
    sf::Text _volver;
    sf::FloatRect _zonas[CANTIDAD_NIVELES];

    bool _disponibles[CANTIDAD_NIVELES] =
    { true, true, false, true, false, false };
    int _ultimoNivelDesbloqueado = 3;
    int _seleccion = 0;

    bool estaHabilitado(int indice) const;
    int obtenerNivelEn(const sf::Vector2f& posicionMouse) const;
    void moverSeleccion(int direccion);
    static void centrarTexto(sf::Text& texto, float x, float y);
    void draw(sf::RenderTarget& destino,
        sf::RenderStates estados) const override;

public:
    MenuSeleccionNivel();
    void abrir(int ultimoNivelDesbloqueado);
    int procesarEvento(const sf::Event& evento,
        const sf::RenderWindow& ventana);
};

