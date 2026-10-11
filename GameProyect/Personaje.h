#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "RelojJuego.h"

enum class EstadoGato {
    Quieto,
    Caminando,
    Agachado,
    Saltando,
    Sentado,
    Golpeando
};

class Personaje
{
private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Vector2f _velocity;

    sf::SoundBuffer _bufferSalto;
    sf::Sound _sonidoSalto;

    EstadoGato _estado;
    int _frameAncho;
    int _frameAlto;
    float _escala;

    bool _enElPiso;
    bool _escondido = false;
    bool _espacioPresionadoAntes;
    bool _ePresionadaAntes;
    float _alturaVertical;
    float _velocidadVertical;
    float _posicionPisoY;

    RelojJuego _relojQuieto;
    RelojJuego _relojCaminar;
    RelojJuego _relojAgachado;
    RelojJuego _relojGolpe;

    bool _contandoQuieto;
    int _frameCaminar;
    int _frameAgachado;
    int _frameGolpe;
    int _numeroGolpe = 0;

    static sf::Texture cargarTextura();

    bool procesarEntrada();
    void actualizarEstado(bool seMueve);
    void aplicarGravedad();
    void actualizarAnimacion(bool seMueve);
    void aplicarMovimiento();
    void limitarMovimiento();
    void actualizarSprite();
    void golpear();
    sf::Vector2f obtenerPosicionDibujo() const;
    sf::Vector2f obtenerTamanoHitbox() const;

    sf::FloatRect _areaAnterior;
    float _baseAnterior = 0.f;

    sf::SoundBuffer _bufferGolpe;
    sf::Sound _sonidoGolpe;


public:
    Personaje();

    void update();
    void setPausado(bool pausado);
    void saltar();
    bool estaGolpeando() const;
    int getNumeroGolpe() const;
    bool estaAgachado() const;
    bool estaEscondido() const;
    void setEscondido(bool escondido);
    void reiniciar();

    float getPosx();
    float getPosy();
    float getBaseY() const;

    sf::FloatRect getGlobalBounds() const;
    sf::FloatRect getHitboxGolpe() const;
    void mover(const sf::Vector2f& desplazamiento);
    void apoyarEn(float superficieY);
    void iniciarCaidaSiEstaElevado();
    bool seEstaMoviendo() const;

    sf::FloatRect getAreaAnterior() const;
    float getBaseAnterior() const;

    void dibujar(sf::RenderWindow& ventana) const;
};
