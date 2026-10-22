#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Enemigo.h"
#include "Mueble.h"
#include "Objeto.h"
#include "Personaje.h"
#include "Constantes.h"
#include <SFML/Audio.hpp>
#include <algorithm>

class Nivel
{
public:
    virtual ~Nivel();
    void pausarMusica();
    void continuarMusica();
    void actualizar(Personaje& gato);
    void actualizarVisibilidadEnemigos(const sf::View& camara);
    void setPausado(bool pausado);
    void reiniciarObjetos();
    void dibujar(sf::RenderWindow& ventana,
        const Personaje& gato) const;
    void setVolumenMusica(float volumen);
    void ocultarHitboxes();
    void alternarHitboxes();

    bool gatoFueDetectado(
        const Personaje& gato,
        const sf::View& camara);

    bool todosLosObjetosEnElPiso() const;

    float getAnchoNivel() const;

protected:
    Nivel();

    void cargarFondo(const std::string& rutaTextura);
    void setAnchoNivel(float ancho);

    Enemigo* agregarEnemigo(
        const std::string& rutaTextura,
        const sf::Vector2f& posicion,
        int frameAncho,
        int frameAlto,
        const sf::Vector2f& escala,
        const std::string& rutaSonidoAlerta,
        float volumenAlerta,
        bool seAsomaPorPuerta = false);
    void agregarMueble(const std::string& rutaTextura,
        const sf::Vector2f& posicion,
        const sf::Vector2f& escala,
        const sf::FloatRect& hitboxLocal);
    void agregarObjeto(const std::string& rutaTextura,
        const sf::Vector2f& posicion,
        float escala,
        int golpesNecesarios,
        const std::string& rutaTexturaCaida,
        const std::string& rutaSonidoCaida);

    void agregarSuperficie(const sf::FloatRect& superficie);
    void agregarZonaEscondite(const sf::FloatRect& zona);

    bool cargarMusicaFondo(const std::string& rutaMusica, float volumen);
    bool cargarSonido(const std::string& rutaSonido, float volumen);
    void configurarLoopMusica(sf::Time inicioLoop, sf::Time duracionLoop);
    void reproducirMusicaFondo(sf::Time inicioReproduccion);
    void agregarBarreraLateral(const sf::FloatRect& barrera,
        bool bloqueaDescenso = false);

private:
    static constexpr int RADIO_HALO_ESCONDITE = 12;
    static sf::FloatRect obtenerAreaVisible(const sf::View& camara);

    sf::Texture _texturaFondo;
    sf::Sprite _spriteFondo;
    sf::Music _musicaFondo;
    sf::Sound _sonido;

    std::vector<Enemigo*> _enemigos;
    std::vector<Mueble*> _muebles;
    std::vector<Objeto*> _objetos;
    std::vector<sf::FloatRect> _superficiesFijas;
    std::vector<sf::FloatRect> _superficiesSolidas;
    std::vector<sf::FloatRect> _zonasEscondite;
    std::vector<sf::Texture> _halosEscondite;
    std::vector<sf::FloatRect> _barrerasLaterales;

    void resolverBarrerasLaterales(Personaje& gato);
    float _anchoNivel = ANCHO_VENTANA;

    void limitarMovimientoGato(Personaje& gato);

    bool _mostrarHitboxes;

    void resolverColisiones(Personaje& gato);
    void resolverColisionGatoObjeto(Personaje& gato, Objeto& objeto);
    void actualizarEscondite(Personaje& gato);
    bool gatoPuedeApoyarseEn(Personaje& gato,
        const sf::FloatRect& superficie) const;

    void dibujarZonasEscondite(sf::RenderWindow& ventana) const;
    void dibujarHitboxes(sf::RenderWindow& ventana,
        const Personaje& gato) const;
    static void dibujarHitbox(sf::RenderWindow& ventana,
        const sf::FloatRect& hitbox,
        const sf::Color& color);
};
