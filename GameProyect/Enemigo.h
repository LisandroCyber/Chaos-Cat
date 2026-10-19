#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "RelojJuego.h"

class Personaje;

enum class EstadoEnemigo
{
    DeEspalda,
    Alerta,
    DadoVuelta,
    DeEspaldaEnojado,
    DadoVueltaEnojado
};

enum class EstadoEnemigoHabitacion
{
    Fuera,
    Asomando,
    Mirando,
    Retirandose
};

class Enemigo
{
public:
    Enemigo(const std::string& rutaTextura,
        const sf::Vector2f& posicion,
        int frameAncho,
        int frameAlto,
        const sf::Vector2f& escala);

    bool detectaAl(
        const Personaje& gato,
        const sf::FloatRect& areaVisible
    ) const;

    void actualizar();
    void reaccionarACaida();
    void setPausado(bool pausado);
    void dibujar(sf::RenderWindow& ventana) const;
    void configurarAsomada();

private:
    sf::Texture _textura;
    sf::Sprite _sprite;
    int _frameAncho;
    int _frameAlto;
    EstadoEnemigo _estado = EstadoEnemigo::DeEspalda;
    RelojJuego _relojEstado;
    float _tiempoDeEspalda = 0.f;

    sf::SoundBuffer _bufferAlerta;
    sf::Sound _sonidoAlerta;

    static sf::Texture cargarTextura(const std::string& rutaTextura);
    static sf::Vector2f obtenerOrigenVisible(const sf::Texture& textura,
        int frameAncho,
        int frameAlto);
    void cambiarEstado(EstadoEnemigo nuevoEstado);
    void actualizarSprite();
    bool _seAsomaPorPuerta = false;
    bool _asomadaEnojada = false;
    EstadoEnemigoHabitacion _estadoAsomada = EstadoEnemigoHabitacion::Fuera;

    void actualizarAsomada();
    void cambiarEstadoAsomada(EstadoEnemigoHabitacion nuevoEstado);
    void actualizarSpriteAsomada();
};
