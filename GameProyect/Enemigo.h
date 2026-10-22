#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "RelojJuego.h"
#include "Constantes.h"

class Personaje;

enum class EstadoEnemigo
{
    DeEspalda,
    Alerta,
    DadoVuelta,
    DeEspaldaEnojado,
    DadoVueltaEnojado,
    Detectado
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
        const sf::Vector2f& escala,
        const std::string& rutaSonidoAlerta,
        float volumenAlerta);

    bool detectaAl(
        const Personaje& gato,
        const sf::FloatRect& areaVisible);

    void actualizar();
    void reaccionarACaida();
    void setPausado(bool pausado);
    void setRelojCongelado(bool congelado);
    void dibujar(sf::RenderWindow& ventana) const;
    void configurarAsomada();

    void configurarTiempos(int reposoMinimo, int reposoMaximo,
        float alerta, float vigilancia);
    void configurarRuido(bool reaccionaAlRuido, bool usaReaccionEspecial);
    void configurarPresentacion(int frameDeteccion,
        bool usarOrigenVisible);
    void configurarReinicioFueraDeCamara();
    void actualizarVisibilidad(const sf::FloatRect& areaVisible);

private:
    sf::Texture _textura;
    sf::Sprite _sprite;
    int _frameAncho;
    int _frameAlto;
    sf::Vector2f _posicionInicial;
    sf::FloatRect _limitesVisibles;
    EstadoEnemigo _estado = EstadoEnemigo::DeEspalda;
    RelojJuego _relojEstado;
    float _tiempoDeEspalda = 0.f;

    int _reposoMinimo = TIEMPO_ENEMIGO_DE_ESPALDA_MIN;
    int _reposoMaximo = TIEMPO_ENEMIGO_DE_ESPALDA_MAX;
    float _duracionAlerta = TIEMPO_ENEMIGO_ALERTA;
    float _duracionVigilancia = TIEMPO_ENEMIGO_DADO_VUELTA;
    bool _reaccionaAlRuido = true;
    bool _usaReaccionEspecial = true;
    int _frameDeteccion = FRAME_ENEMIGO_SIN_CAMBIO;
    bool _reiniciarFueraDeCamara = false;
    bool _fueraDeCamara = false;
    bool _pausado = true;
    bool _relojCongelado = false;

    sf::SoundBuffer _bufferAlerta;
    sf::Sound _sonidoAlerta;
    bool _tieneSonidoAlerta = false;

    static sf::Texture cargarTextura(const std::string& rutaTextura);
    static sf::Vector2f obtenerOrigenVisible(const sf::Texture& textura,
        int frameAncho,
        int frameAlto,
        sf::FloatRect& limitesVisibles);
    void reiniciarCiclo();
    void cambiarEstado(EstadoEnemigo nuevoEstado);
    void actualizarSprite();
    void validarMedidasFrame() const;
    void mostrarFrame(int frame);

    bool _seAsomaPorPuerta = false;
    bool _asomadaEnojada = false;
    EstadoEnemigoHabitacion _estadoAsomada = EstadoEnemigoHabitacion::Fuera;

    void actualizarAsomada();
    void cambiarEstadoAsomada(EstadoEnemigoHabitacion nuevoEstado);
    void actualizarSpriteAsomada();
};
