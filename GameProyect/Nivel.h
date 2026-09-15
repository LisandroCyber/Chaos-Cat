#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

#include "Humano.h"
#include "Mueble.h"
#include "Objeto.h"
#include "Personaje.h"

enum class TipoNivel
{
    Cocina
};

class Nivel
{
private:
    sf::Texture _texturaFondo;
    sf::Sprite _spriteFondo;

    std::vector<std::unique_ptr<Humano>> _humanos;
    std::vector<std::unique_ptr<Mueble>> _muebles;
    std::vector<std::unique_ptr<Objeto>> _objetos;
    std::vector<sf::FloatRect> _superficiesFijas;

    bool _mostrarHitboxes;

    void cargarCocina();
    void cargarFondo(const std::string& rutaTextura);
    void resolverColisiones(Personaje& gato);
    bool resolverColisionGatoObjeto(Personaje& gato, Objeto& objeto);
    bool gatoPuedeApoyarseEn(Personaje& gato,
        const sf::FloatRect& superficie) const;
    void dibujarHitboxes(sf::RenderWindow& ventana,
        const Personaje& gato) const;
    static void dibujarHitbox(sf::RenderWindow& ventana,
        const sf::FloatRect& hitbox,
        const sf::Color& color);

public:
    explicit Nivel(TipoNivel tipo);

    void agregarHumano(const std::string& rutaTextura,
        const sf::Vector2f& posicion,
        int frameAncho,
        int frameAlto,
        const sf::Vector2f& escala);
    void agregarMueble(const std::string& rutaTextura,
        const sf::Vector2f& posicion,
        const sf::Vector2f& escala,
        const sf::FloatRect& hitboxLocal);
    void agregarObjeto(const std::string& rutaTextura,
        const sf::Vector2f& posicion,
        float escala);
    void agregarSuperficie(const sf::FloatRect& superficie);

    void actualizar(Personaje& gato);
    void reiniciarObjetos();
    void dibujar(sf::RenderWindow& ventana,
        const Personaje& gato) const;
};
