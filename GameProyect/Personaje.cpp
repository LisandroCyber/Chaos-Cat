#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include "Constantes.h"
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
    _frameGolpe = 0;

    _enElPiso = true;
    _espacioPresionadoAntes = false;
    _ePresionadaAntes = false;
    _alturaVertical = 0.f;
    _velocidadVertical = 0.f;
    _posicionPisoY = ALTO_VENTANA - (ALTO_BASE_HITBOX * _escala) / 2.f;

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
    float anchoHitboxInicial = ANCHO_BASE_HITBOX * _escala;
    float altoHitboxInicial = ALTO_BASE_HITBOX * _escala;

    _sprite.setPosition({
        anchoHitboxInicial / 2.f + margenX,
        _posicionPisoY - margenY
    });

    actualizarSprite();
}

//para ver el comportamiento del gato en cada frame, lee el teclado y aplica la "gravedad" para el gato
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
    float velocidadActual = VELOCIDAD_CAMINAR;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
    {
        velocidadActual = VELOCIDAD_CORRER;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
    {
        velocidadActual = VELOCIDAD_AGACHADO;
    }

    _velocity = { 0.f, 0.f };
    bool seMueve = false;

    const bool ePresionada = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);

    if (ePresionada && !_ePresionadaAntes && _enElPiso && _estado != EstadoGato::Golpeando)
    {
        golpear();
    }

    _ePresionadaAntes = ePresionada;

    if (_estado == EstadoGato::Golpeando)
    {
        return false;
    }

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

    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        _velocity.y = -velocidadActual;
        seMueve = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        _velocity.y = velocidadActual;
        seMueve = true;
    }*/

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
    if (_estado == EstadoGato::Golpeando)
    {
        if (_relojGolpe.getElapsedTime().asSeconds() < DURACION_GOLPE)
        {
            return;
        }

        _contandoQuieto = false;
    }

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
        // El tiempo quieto determina cuando el gato vuelve a sentarse.
        if (!_contandoQuieto)
        {
            _relojQuieto.restart();
            _contandoQuieto = true;
            _estado = EstadoGato::Quieto;
        }
        else if (_relojQuieto.getElapsedTime().asSeconds() >= TIEMPO_PARA_SENTARSE)
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
        _velocidadVertical += GRAVEDAD;

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
    if (_estado == EstadoGato::Golpeando)
    {
        _frameGolpe = _relojGolpe.getElapsedTime().asSeconds() < DURACION_FRAME_GOLPE ? 0 : 1;
        return;
    }

    if (_estado == EstadoGato::Caminando)
    {
        if (_relojCaminar.getElapsedTime().asSeconds() >= DURACION_FRAME_CAMINAR)
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
        if (_relojAgachado.getElapsedTime().asSeconds() >= DURACION_FRAME_AGACHADO)
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

    if (hitbox.position.x + hitbox.size.x > ANCHO_VENTANA)
    {
        ajuste.x = ANCHO_VENTANA - (hitbox.position.x + hitbox.size.x);
    }

    if (hitbox.position.y < 0.f)
    {
        ajuste.y = -hitbox.position.y;
    }

    if (hitbox.position.y + hitbox.size.y > ALTO_VENTANA)
    {
        ajuste.y = ALTO_VENTANA - (hitbox.position.y + hitbox.size.y);
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
    else if (_estado == EstadoGato::Golpeando)
        frame = 7 + _frameGolpe;

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
        _velocidadVertical = VELOCIDAD_INICIAL_SALTO;
    }
}

void Personaje::golpear()
{
    _estado = EstadoGato::Golpeando;
    _frameGolpe = 0;
    _relojGolpe.restart();
    _contandoQuieto = false;
}

bool Personaje::estaGolpeando() const
{
    return _estado == EstadoGato::Golpeando;
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
    return obtenerPosicionDibujo().y + (ALTO_BASE_HITBOX * escalaY) / 2.f;
}


sf::Vector2f Personaje::obtenerTamanoHitbox() const
{
    // Medidas originales, antes de aplicar la escala del sprite.
    switch (_estado)
    {
    case EstadoGato::Saltando:
        return { 220.f, 140.f };
    case EstadoGato::Agachado:
        return { 300.f, 130.f };
    case EstadoGato::Golpeando:
        return { 210.f, 140.f };
    case EstadoGato::Sentado:
        return { 170.f, 220.f };
    case EstadoGato::Caminando:
        return { 220.f, 220.f };
    case EstadoGato::Quieto:
        return { 200.f, 220.f };
    default:
        return { ANCHO_BASE_HITBOX, ALTO_BASE_HITBOX };
    }
}

sf::FloatRect Personaje::getGlobalBounds() const
{
    float escalaX = _sprite.getScale().x < 0.f ? -_sprite.getScale().x : _sprite.getScale().x;
    float escalaY = _sprite.getScale().y < 0.f ? -_sprite.getScale().y : _sprite.getScale().y;
    sf::Vector2f tamano = obtenerTamanoHitbox();
    float ancho = tamano.x * escalaX;
    float alto = tamano.y * escalaY;
    sf::Vector2f posicionDibujo = obtenerPosicionDibujo();
    sf::Vector2f posicionHitbox = {
        posicionDibujo.x - ancho / 2.f,
        getBaseY() - alto
    };

    if (_estado == EstadoGato::Saltando)
    {
        float offsetX = 20.f * (_sprite.getScale().x < 0.f ? -escalaX : escalaX);
        float offsetY = 95.f * escalaY;
        posicionHitbox.x += offsetX;
        posicionHitbox.y = posicionDibujo.y - alto / 2.f + offsetY;
    }

    return sf::FloatRect(posicionHitbox, { ancho, alto });
}

sf::FloatRect Personaje::getHitboxGolpe() const
{
    const float escalaX = _sprite.getScale().x < 0.f ? -_sprite.getScale().x : _sprite.getScale().x;
    const float escalaY = _sprite.getScale().y < 0.f ? -_sprite.getScale().y : _sprite.getScale().y;
    const float ancho = 100.f * escalaX;
    const float alto = 100.f * escalaY;
    const float desplazamientoPata = 35.f * escalaX;
    const bool miraDerecha = _sprite.getScale().x > 0.f;
    const float x = miraDerecha
        ? obtenerPosicionDibujo().x + desplazamientoPata
        : obtenerPosicionDibujo().x - desplazamientoPata - ancho;

    return { { x, getBaseY() - alto }, { ancho, alto } };
}

void Personaje::mover(const sf::Vector2f& desplazamiento)
{
    _sprite.move(desplazamiento);
}

void Personaje::apoyarEn(float superficieY)
{
    float escalaY = _sprite.getScale().y < 0.f ? -_sprite.getScale().y : _sprite.getScale().y;
    float nuevaPosicionY = superficieY - (ALTO_BASE_HITBOX * escalaY) / 2.f;

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
