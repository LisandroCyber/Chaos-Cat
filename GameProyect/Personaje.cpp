#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include <iostream>

sf::Texture Personaje::cargarTextura()
{
    sf::Texture textura;

    if (!textura.loadFromFile("images/GatoNaranja_spritesheet_7frames_fixed.png"))
    {
        std::cout << "ERROR: NO SE PUDO CARGAR EL GATO\n";
        exit(-1);
    }

    return textura;
}

Personaje::Personaje()
    : _texture(cargarTextura()), _sprite(_texture)
{
    //frame del gato
    _frameAncho = 600;
    _frameAlto = 724;
    _escala = 0.5f;

    //velocidad inicial, junto con otros atributos iniciados
    _sprite.setScale({ _escala, _escala });
    _velocity = { 0.f, 0.f };

    _estado = EstadoGato::Sentado;
    _contandoQuieto = true;
    _frameCaminar = 0;
    _frameAgachado = 0;

    _saltando = false;
    _alturaSalto = 0.f;
    _velocidadSalto = 0.f;

    //punto de origen del sprite en el frame (aca estaria en el centro)
    _sprite.setOrigin({
        _frameAncho / 2.f,
        _frameAlto / 2.f
    });

    //al ser un sprite con multiples imagenes, este dice donde pararse para la primer imagen
    _sprite.setTextureRect(sf::IntRect(
        { 0, 0 },
        { _frameAncho, _frameAlto }
    ));

    //con esto la posicion inicial siempre va a ser al costado inferior izquierdo de la pantalla
    float margenX = 0.f;
    float margenY = 0.f;
    float anchoHitboxInicial = 360.f * _escala;
    float altoHitboxInicial = 360.f * _escala;

    _sprite.setPosition({
        anchoHitboxInicial / 2.f + margenX,
        720.f - altoHitboxInicial / 2.f - margenY
    });

    actualizarSprite();
}

void Personaje::update()
{
    float velocidadActual = 2.2f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
    {
        velocidadActual = 5.f; // CORRER
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
    {
        velocidadActual = 0.75f; // AGACHADO
    }

    _velocity = { 0.f, 0.f };
    bool seMueve = false;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        _velocity.x = -velocidadActual;
        _sprite.setScale({ -_escala, _escala });
        seMueve = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        _velocity.x = velocidadActual;
        _sprite.setScale({ _escala, _escala });
        seMueve = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        saltar();
    }

    if (seMueve || _saltando || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
    {
        _contandoQuieto = false;
    }

    //configuracion del salto
    if (_saltando)
    {
        _estado = EstadoGato::Saltando;

        _alturaSalto += _velocidadSalto;
        _velocidadSalto += 0.5f;

        if (_alturaSalto >= 0.f)
        {
            _alturaSalto = 0.f;
            _velocidadSalto = 0.f;
            _saltando = false;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
    {
        _estado = EstadoGato::Agachado;
    }
    else if (seMueve)
    {
        _estado = EstadoGato::Caminando;
    }
    else
    {
        //contandoQuieto es un reloj interno en el que, pasado 0.5 segundos, el gato vuelve a la posicion sentado
        if (!_contandoQuieto)
        {
            _relojQuieto.restart();
            _contandoQuieto = true;
            _estado = EstadoGato::Quieto;
        }
        else if (_relojQuieto.getElapsedTime().asSeconds() >= 0.5f)
        {
            _estado = EstadoGato::Sentado;
        }
        else
        {
            _estado = EstadoGato::Quieto;
        }
    }

    if (_estado == EstadoGato::Caminando)
    {
        if (_relojCaminar.getElapsedTime().asSeconds() >= 0.18f)
        {
            _frameCaminar = (_frameCaminar + 1) % 2;
            _relojCaminar.restart();
        }
    }
    else
    {
        _frameCaminar = 0;
        _relojCaminar.restart();
    }

    if (_estado == EstadoGato::Agachado && seMueve)
    {
        if (_relojAgachado.getElapsedTime().asSeconds() >= 0.22f)
        {
            _frameAgachado = (_frameAgachado + 1) % 2;
            _relojAgachado.restart();
        }
    }
    else
    {
        _frameAgachado = 0;
        _relojAgachado.restart();
    }

    _sprite.move(_velocity);
    actualizarSprite();

    sf::FloatRect hitbox = getGlobalBounds();
    float ancho = hitbox.size.x;
    float alto = hitbox.size.y;

    float mitadAncho = ancho / 2.f;
    float mitadAlto = alto / 2.f;

    if (_sprite.getPosition().x - mitadAncho < 0)
    {
        _sprite.setPosition({
            mitadAncho,
            _sprite.getPosition().y
            });
    }

    if (_sprite.getPosition().x + mitadAncho > 1280)
    {
        _sprite.setPosition({
            1280.f - mitadAncho,
            _sprite.getPosition().y
            });
    }

    if (_sprite.getPosition().y - mitadAlto < 0)
    {
        _sprite.setPosition({
            _sprite.getPosition().x,
            mitadAlto
            });
    }

    if (_sprite.getPosition().y + mitadAlto > 720)
    {
        _sprite.setPosition({
            _sprite.getPosition().x,
            720.f - mitadAlto
            });
    }

}

void Personaje::actualizarSprite()
{
    int frame = 0;

    if (_estado == EstadoGato::Quieto)
        frame = 0;
    else if (_estado == EstadoGato::Caminando)
        frame = 1 + _frameCaminar;
    else if (_estado == EstadoGato::Agachado)
        frame = 3 + _frameAgachado;
    else if (_estado == EstadoGato::Saltando)
        frame = 5;
    else if (_estado == EstadoGato::Sentado)
        frame = 6;

    _sprite.setTextureRect(sf::IntRect(
        { frame * _frameAncho, 0 },
        { _frameAncho, _frameAlto }
    ));
}

void Personaje::saltar()
{
    if (!_saltando)
    {
        _saltando = true;
        _velocidadSalto = -8.f;
    }
}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

float Personaje::getPosx() {
    return _sprite.getPosition().x;
}

float Personaje::getPosy() {
    return _sprite.getPosition().y;
}


//esto es para cambiar el hitbox del gato depende el sprite, el de saltando se necesita refactorizar y probablemente todo este bloque se necesite sacar
//TODO: se esta volviendo muy cargado este metodo
sf::FloatRect Personaje::getGlobalBounds() const
{
    float escalaX = _sprite.getScale().x < 0.f ? -_sprite.getScale().x : _sprite.getScale().x;
    float escalaY = _sprite.getScale().y < 0.f ? -_sprite.getScale().y : _sprite.getScale().y;

    if (_estado == EstadoGato::Saltando)
    {
        float ancho = 360.f * escalaX;
        float alto = 140.f * escalaY;
        float offsetX = 20.f * (_sprite.getScale().x < 0.f ? -escalaX : escalaX);
        float offsetY = 95.f * escalaY;

        return sf::FloatRect(
            {
                _sprite.getPosition().x - ancho / 2.f + offsetX,
                _sprite.getPosition().y - alto / 2.f + offsetY
            },
            { ancho, alto }
        );
    }

    float ancho = 360.f * escalaX;
    float alto = 360.f * escalaY;

    if (_estado == EstadoGato::Agachado)
    {
        ancho = 300.f * escalaX;
        alto = 130.f * escalaY;
    }
    else if (_estado == EstadoGato::Sentado)
    {
        ancho = 170.f * escalaX;
        alto = 220.f * escalaY;
    }
    else if (_estado == EstadoGato::Caminando)
    {
        ancho = 220.f * escalaX;
        alto = 220.f * escalaY;
    }
    else if (_estado == EstadoGato::Quieto)
    {
        ancho = 200.f * escalaX;
        alto = 220.f * escalaY;
    }

    float baseY = _sprite.getPosition().y + (360.f * escalaY) / 2.f;

    return sf::FloatRect(
        {
            _sprite.getPosition().x - ancho / 2.f,
            baseY - alto
        },
        { ancho, alto }
    );
}

void Personaje::mover(const sf::Vector2f& desplazamiento)
{
    _sprite.move(desplazamiento);
}
