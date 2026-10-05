#pragma once

#include <SFML/Graphics.hpp>
#include <string>

enum class EstadoEnemigo
{
    DeEspalda,
    Alerta,
    DadoVuelta
};

class Enemigo
{
private:
    sf::Texture _textura;
    sf::Sprite _sprite;
    int _frameAncho;
    int _frameAlto;
    EstadoEnemigo _estado = EstadoEnemigo::DeEspalda;
    sf::Clock _relojEstado;

    static sf::Texture cargarTextura(const std::string& rutaTextura);
    static sf::Vector2f obtenerOrigenVisible(const sf::Texture& textura,
        int frameAncho,
        int frameAlto);
    void cambiarEstado(EstadoEnemigo nuevoEstado);
    void actualizarSprite();

public:
    Enemigo(const std::string& rutaTextura,
        const sf::Vector2f& posicion,
        int frameAncho,
        int frameAlto,
        const sf::Vector2f& escala);

    void actualizar();
    void dibujar(sf::RenderWindow& ventana) const;
};
