#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Humano.h"
#include "Mueble.h"
#include "Objeto.h"
#include "Personaje.h"
#include <SFML/Audio.hpp>

class Nivel
{
private:
    sf::Texture _texturaFondo;
    sf::Sprite _spriteFondo;
    sf::Music _musicaFondo;

    std::vector<Humano*> _humanos;
    std::vector<Mueble*> _muebles;
    std::vector<Objeto*> _objetos;
    std::vector<sf::FloatRect> _superficiesFijas;

    bool _mostrarHitboxes;

    void resolverColisiones(Personaje& gato);
    bool resolverColisionGatoObjeto(Personaje& gato, Objeto& objeto);
    bool gatoPuedeApoyarseEn(Personaje& gato,
        const sf::FloatRect& superficie) const;
    void dibujarHitboxes(sf::RenderWindow& ventana,
        const Personaje& gato) const;
    static void dibujarHitbox(sf::RenderWindow& ventana,
        const sf::FloatRect& hitbox,
        const sf::Color& color);

protected:
    Nivel();

    void cargarFondo(const std::string& rutaTextura);

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

    bool cargarMusicaFondo(const std::string& rutaMusica, float volumen);
    void configurarLoopMusica(sf::Time inicioLoop, sf::Time duracionLoop);
    void reproducirMusicaFondo(sf::Time inicioReproduccion);

public:
    virtual ~Nivel();

    void actualizar(Personaje& gato);
    void reiniciarObjetos();
    void dibujar(sf::RenderWindow& ventana,
        const Personaje& gato) const;
};
