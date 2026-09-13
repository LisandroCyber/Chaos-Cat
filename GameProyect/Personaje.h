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
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Vector2f _velocity;

    EstadoGato _estado;
    int _frameAncho;
    int _frameAlto;

    bool _saltando;
    float _alturaSalto;
    float _velocidadSalto;

    sf::Clock _relojQuieto;
    bool _contandoQuieto;

    static sf::Texture cargarTextura();

public:
    Personaje();

    void update();
    void actualizarSprite();
    void saltar();

    float getPosx();
    float getPosy();

    sf::FloatRect getGlobalBounds() const;
    void mover(const sf::Vector2f& desplazamiento);

    void draw(sf::RenderTarget& target,
        sf::RenderStates states) const override;


};