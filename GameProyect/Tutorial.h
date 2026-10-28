#pragma once
#include <SFML/Graphics.hpp>

class Tutorial : public sf::Drawable
{
public:
    Tutorial();
    void abrir();

    int procesarEvento(const sf::Event& evento,
        const sf::RenderWindow& ventana);
private:
    sf::Texture _textura;
    sf::Sprite _imagen;
    sf::Font _fuente;
    int _pagina = 0;

    void cargarImagen();

    void draw(sf::RenderTarget& destino,
        sf::RenderStates estados) const override;
};
