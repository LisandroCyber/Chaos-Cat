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

    bool _saltando;
    float _alturaSalto;
    float _velocidadSalto;

    sf::Clock _relojQuieto;
    sf::Clock _relojCaminar;
    sf::Clock _relojAgachado;
    bool _contandoQuieto;
    int _frameCaminar;
    int _frameAgachado;

    static sf::Texture cargarTextura();

    bool procesarEntrada();
    void actualizarEstado(bool seMueve);
    void actualizarSalto();
    void actualizarAnimacion(bool seMueve);
    void aplicarMovimiento();
    void limitarMovimiento();
    void actualizarSprite();

public:
    Personaje();

    void update();
    void saltar();

    float getPosx();
    float getPosy();

    sf::FloatRect getGlobalBounds() const;
    void mover(const sf::Vector2f& desplazamiento);

    void draw(sf::RenderTarget& target,
        sf::RenderStates states) const override;
};
