#pragma once
#include <SFML/Graphics.hpp>

enum class EstadoGato {
    Quieto,
    Caminando,
    Agachado,
    Saltando,
    Sentado
};

class Personaje : public sf::Drawable
{
private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Vector2f _velocity;

    EstadoGato _estado;
    int _frameAncho;
    int _frameAlto;
    float _escala;

    bool _enElPiso;
    bool _espacioPresionadoAntes;
    float _alturaVertical;
    float _velocidadVertical;
    float _posicionPisoY;

    sf::Clock _relojQuieto;
    sf::Clock _relojCaminar;
    sf::Clock _relojAgachado;
    bool _contandoQuieto;
    int _frameCaminar;
    int _frameAgachado;

    static sf::Texture cargarTextura();

    bool procesarEntrada();
    void actualizarEstado(bool seMueve);
    void aplicarGravedad();
    void actualizarAnimacion(bool seMueve);
    void aplicarMovimiento();
    void limitarMovimiento();
    void actualizarSprite();
    sf::Vector2f obtenerPosicionDibujo() const;
    sf::Vector2f obtenerTamanoHitbox() const;

public:
    Personaje();

    void update();
    void saltar();

    float getPosx();
    float getPosy();
    float getBaseY() const;

    sf::FloatRect getGlobalBounds() const;
    void mover(const sf::Vector2f& desplazamiento);
    void apoyarEn(float superficieY);
    void iniciarCaidaSiEstaElevado();

    void draw(sf::RenderTarget& target,
        sf::RenderStates states) const override;
};
