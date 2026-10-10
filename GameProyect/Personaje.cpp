#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include "Constantes.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

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
    : _texture(cargarTextura()), _sprite(_texture), _sonidoSalto(_bufferSalto)
{
    //frame del gato
    _frameAncho = 600;
    _frameAlto = 724;
    _escala = 0.5f;

    //velocidad inicial, junto con otros atributos iniciados
    _sprite.setScale({ _escala, _escala });
    _velocity = { 0.f, 0.f };

    if (!_bufferSalto.loadFromFile("sound effects/PersonajeGato/SaltoGato.ogg"))
    {
        std::cout << "No se pudo cargar el sonido del salto\n";
    }

    _sonidoSalto.setVolume(35.f);

    if (!_bufferGolpe.loadFromFile("sound effects/PersonajeGato/GolpeGato.wav"))
    {
        std::cout << "No se pude cargar el sonido del golpe del gato\n";
    }
    else {
        _sonidoGolpe.setBuffer(_bufferGolpe);
    }

    _sonidoGolpe.setVolume(20.f);

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
    _sprite.setTextureRect(sf::IntRect(0, 0, _frameAncho, _frameAlto));

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
    _areaAnterior = getGlobalBounds();
    _baseAnterior = getBaseY();
}

//para ver el comportamiento del gato en cada frame, lee el teclado y aplica la "gravedad" para el gato
void Personaje::update()
{
    _areaAnterior = getGlobalBounds();
    _baseAnterior = getBaseY();

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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        velocidadActual = VELOCIDAD_CORRER;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        velocidadActual = VELOCIDAD_AGACHADO;
    }

    _velocity = { 0.f, 0.f };
    bool seMueve = false;

    const bool ePresionada = sf::Keyboard::isKeyPressed(sf::Keyboard::E);

    if (ePresionada && !_ePresionadaAntes && _enElPiso && _estado != EstadoGato::Golpeando)
    {
        _sonidoGolpe.setPlayingOffset(sf::seconds(0.5f));
        _sonidoGolpe.play();
        golpear();
    }

    _ePresionadaAntes = ePresionada;

    if (_estado == EstadoGato::Golpeando)
    {
        return false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        _velocity.x = -velocidadActual;
        _sprite.setScale({ -_escala, _escala });
        seMueve = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        _velocity.x = velocidadActual;
        _sprite.setScale({ _escala, _escala });
        seMueve = true;
    }

    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        _velocity.y = -velocidadActual;
        seMueve = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        _velocity.y = velocidadActual;
        seMueve = true;
    }*/

    bool espacioPresionado = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

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

    if (seMueve || !_enElPiso || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        _contandoQuieto = false;
    }

    if (!_enElPiso)
    {
        _estado = EstadoGato::Saltando;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
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

    if (hitbox.left < 0.f)
    {
        ajuste.x = -hitbox.left;
    }

    if (hitbox.left + hitbox.width > ANCHO_VENTANA)
    {
        ajuste.x = ANCHO_VENTANA - (hitbox.left + hitbox.width);
    }

    if (hitbox.top < 0.f)
    {
        ajuste.y = -hitbox.top;
    }

    if (hitbox.top + hitbox.height > ALTO_VENTANA)
    {
        ajuste.y = ALTO_VENTANA - (hitbox.top + hitbox.height);
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
        frame * _frameAncho,
        0,
        _frameAncho,
        _frameAlto
    ));
}

void Personaje::saltar()
{
    if (_enElPiso)
    {
        _enElPiso = false;
        _alturaVertical = 0.f;
        _velocidadVertical = VELOCIDAD_INICIAL_SALTO;

        _sonidoSalto.play();
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

bool Personaje::estaAgachado() const
{
    return _estado == EstadoGato::Agachado;
}

bool Personaje::estaEscondido() const
{
    return _escondido;
}

void Personaje::setEscondido(bool escondido)
{
    if (_escondido == escondido)
    {
        return;
    }

    _escondido = escondido;

    if (_escondido)
    {
        std::cout << "El gato esta escondido\n";
    }
    else
    {
        std::cout << "El gato ya no esta escondido\n";
    }
}

void Personaje::dibujar(sf::RenderWindow& ventana) const
{
    sf::Sprite spriteDibujo = _sprite;
    spriteDibujo.setPosition(obtenerPosicionDibujo());

    ventana.draw(spriteDibujo);
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
    const sf::Vector2f posicion = obtenerPosicionDibujo();

    // Equivalen a la hitbox del gato sentado con escala 0.5.
    const float ancho = 74.f;
    const float alto = 110.f;

    return sf::FloatRect(
        posicion.x - ancho / 2.f,
        getBaseY() - alto,
        ancho,
        alto
    );
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

    return sf::FloatRect(x, getBaseY() - alto, ancho, alto);
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

sf::FloatRect Personaje::getAreaAnterior() const
{
    return _areaAnterior;
}

float Personaje::getBaseAnterior() const
{
    return _baseAnterior;
}

bool Personaje::seEstaMoviendo() const
{
    const sf::FloatRect actual = getGlobalBounds();

    const bool movimientoHorizontal =
        std::abs(actual.left - _areaAnterior.left) > 0.1f;

    const bool movimientoVertical =
        std::abs(getBaseY() - _baseAnterior) > 0.1f;

    return movimientoHorizontal || movimientoVertical;
}

void Personaje::reiniciar()
{
    _sonidoSalto.stop();
    _sonidoGolpe.stop();

    _velocity = sf::Vector2f(0.f, 0.f);
    _alturaVertical = 0.f;
    _velocidadVertical = 0.f;

    _enElPiso = true;
    _escondido = false;

    // Evita que una tecla mantenida se tome como una pulsación nueva.
    _espacioPresionadoAntes =
        sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    _ePresionadaAntes =
        sf::Keyboard::isKeyPressed(sf::Keyboard::E);

    _estado = EstadoGato::Quieto;

    _contandoQuieto = false;
    _frameCaminar = 0;
    _frameAgachado = 0;
    _frameGolpe = 0;

    _relojQuieto.restart();
    _relojCaminar.restart();
    _relojAgachado.restart();
    _relojGolpe.restart();

    _sprite.setScale(_escala, _escala);

    // Usá acá la misma posición inicial que tenés en el constructor.
    _sprite.setPosition(200.f, _posicionPisoY);

    actualizarSprite();

    _areaAnterior = getGlobalBounds();
    _baseAnterior = getBaseY();
}
