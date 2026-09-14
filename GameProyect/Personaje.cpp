#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include <cstdlib>
#include <iostream>

sf::Texture Personaje::cargarTextura()
{
    sf::Texture textura;

    if (!textura.loadFromFile("images/frames_gato_original.png"))
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

    _enElPiso = true;
    _espacioPresionadoAntes = false;
    _alturaVertical = 0.f;
    _velocidadVertical = 0.f;
    _posicionPisoY = 720.f - (360.f * _escala) / 2.f;

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
        _posicionPisoY - margenY
    });

    actualizarSprite();
}

void Personaje::update()
{
    bool seMueve = procesarEntrada();

    aplicarGravedad();
    actualizarEstado(seMueve);
    actualizarAnimacion(seMueve);
    aplicarMovimiento();
    actualizarSprite();
    limitarMovimiento();
}

bool Personaje::procesarEntrada()
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        _velocity.x = -velocidadActual;
        _sprite.setScale({ -_escala, _escala });
        seMueve = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        _velocity.x = velocidadActual;
        _sprite.setScale({ _escala, _escala });
        seMueve = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        _velocity.y = -velocidadActual;
        seMueve = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        _velocity.y = velocidadActual;
        seMueve = true;
    }

    bool espacioPresionado = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

    if (espacioPresionado && !_espacioPresionadoAntes)
    {
        saltar();
    }

    _espacioPresionadoAntes = espacioPresionado;

    return seMueve;
}

void Personaje::actualizarEstado(bool seMueve)
{
    if (seMueve || !_enElPiso || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
    {
        _contandoQuieto = false;
    }

    if (!_enElPiso)
    {
        _estado = EstadoGato::Saltando;
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
}

void Personaje::aplicarGravedad()
{
    if (!_enElPiso)
    {
        _alturaVertical += _velocidadVertical;
        _velocidadVertical += 0.55f;

        if (_sprite.getPosition().y + _alturaVertical >= _posicionPisoY)
        {
            _sprite.setPosition({ _sprite.getPosition().x, _posicionPisoY });
            _alturaVertical = 0.f;
            _velocidadVertical = 0.f;
            _enElPiso = true;
        }
    }
}

void Personaje::actualizarAnimacion(bool seMueve)
{
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
}

void Personaje::aplicarMovimiento()
{
    _sprite.move(_velocity);
}

void Personaje::limitarMovimiento()
{
    sf::FloatRect hitbox = getGlobalBounds();
    sf::Vector2f ajuste = { 0.f, 0.f };

    if (hitbox.position.x < 0.f)
    {
        ajuste.x = -hitbox.position.x;
    }

    if (hitbox.position.x + hitbox.size.x > 1280.f)
    {
        ajuste.x = 1280.f - (hitbox.position.x + hitbox.size.x);
    }

    if (hitbox.position.y < 0.f)
    {
        ajuste.y = -hitbox.position.y;
    }

    if (hitbox.position.y + hitbox.size.y > 720.f)
    {
        ajuste.y = 720.f - (hitbox.position.y + hitbox.size.y);
    }

    _sprite.move(ajuste);
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
    if (_enElPiso)
    {
        _enElPiso = false;
        _alturaVertical = 0.f;
        _velocidadVertical = -17.f;
    }
}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite spriteDibujo = _sprite;
    spriteDibujo.setPosition(obtenerPosicionDibujo());

    target.draw(spriteDibujo, states);
}

float Personaje::getPosx() {
    return _sprite.getPosition().x;
}

float Personaje::getPosy() {
    return _sprite.getPosition().y;
}

float Personaje::getBaseY() const
{
    float escalaY = _sprite.getScale().y < 0.f ? -_sprite.getScale().y : _sprite.getScale().y;
    return obtenerPosicionDibujo().y + (360.f * escalaY) / 2.f;
}


//esto es para cambiar el hitbox del gato depende el sprite, el de saltando se necesita refactorizar y probablemente todo este bloque se necesite sacar
//TODO: se esta volviendo muy cargado este metodo
sf::FloatRect Personaje::getGlobalBounds() const
{
    float escalaX = _sprite.getScale().x < 0.f ? -_sprite.getScale().x : _sprite.getScale().x;
    float escalaY = _sprite.getScale().y < 0.f ? -_sprite.getScale().y : _sprite.getScale().y;
    sf::Vector2f posicionDibujo = obtenerPosicionDibujo();

    if (_estado == EstadoGato::Saltando)
    {
        float ancho = 220.f * escalaX;
        float alto = 140.f * escalaY;
        float offsetX = 20.f * (_sprite.getScale().x < 0.f ? -escalaX : escalaX);
        float offsetY = 95.f * escalaY;

        return sf::FloatRect(
            {
                posicionDibujo.x - ancho / 2.f + offsetX,
                posicionDibujo.y - alto / 2.f + offsetY
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

    float baseY = posicionDibujo.y + (360.f * escalaY) / 2.f;

    return sf::FloatRect(
        {
            posicionDibujo.x - ancho / 2.f,
            baseY - alto
        },
        { ancho, alto }
    );
}

void Personaje::mover(const sf::Vector2f& desplazamiento)
{
    _sprite.move(desplazamiento);
}

void Personaje::apoyarEn(float superficieY)
{
    float escalaY = _sprite.getScale().y < 0.f ? -_sprite.getScale().y : _sprite.getScale().y;
    float nuevaPosicionY = superficieY - (360.f * escalaY) / 2.f;

    _sprite.setPosition({ _sprite.getPosition().x, nuevaPosicionY });
    _alturaVertical = 0.f;
    _velocidadVertical = 0.f;
    _enElPiso = true;
}

void Personaje::iniciarCaidaSiEstaElevado()
{
    if (_enElPiso && _sprite.getPosition().y < _posicionPisoY - 1.f)
    {
        _enElPiso = false;
        _alturaVertical = 0.f;
        _velocidadVertical = 0.f;
    }
}

sf::Vector2f Personaje::obtenerPosicionDibujo() const
{
    return {
        _sprite.getPosition().x,
        _sprite.getPosition().y + _alturaVertical
    };
}

// Metodo para colisionar la parte superior de la hitbox del gato,
// contra la parte inferior de la hitbox del objeto

void Personaje::chocarTecho(float yTecho)
{
    sf::FloatRect hitbox = getGlobalBounds();
    float alto = hitbox.size.y;

    float nuevaPosicionDibujoY = yTecho + alto / 2.f;

    _alturaVertical = 0.f;
    _sprite.setPosition({ _sprite.getPosition().x, nuevaPosicionDibujoY });

    _velocidadVertical = 2.f;
    _enElPiso = false;
}
