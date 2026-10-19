#include "Enemigo.h"
#include "Constantes.h"
#include "Personaje.h"

#include <cstdlib>
#include <iostream>

sf::Texture Enemigo::cargarTextura(const std::string& rutaTextura)
{
    sf::Texture textura;

    if (!textura.loadFromFile(rutaTextura))
    {
        std::cout << "ERROR: NO SE PUDO CARGAR EL ENEMIGO " << rutaTextura << '\n';
        exit(-1);
    }

    return textura;
}

//sirve para tomar el sprite sheet entero, darle valores a una sola de las imagenes y mantenerlo en el mismo eje que las
// otras. De esta forma da el efecto correcto que el enemigo se da vuelta sobre su propio eje
sf::Vector2f Enemigo::obtenerOrigenVisible(const sf::Texture& textura,
    int frameAncho,
    int frameAlto)
{
    const sf::Image imagen = textura.copyToImage();
    unsigned int izquierda = static_cast<unsigned int>(frameAncho);
    unsigned int derecha = 0;
    unsigned int abajo = 0;
    bool encontroPixelVisible = false;

    //recorre como una matriz el area para detectar la posicion del sprite (sus medidas)
    for (unsigned int y = 0; y < static_cast<unsigned int>(frameAlto); y++)
    {
        for (unsigned int x = 0; x < static_cast<unsigned int>(frameAncho); x++)
        {
            //el a es alpha y es el gradiente de color, si es 0 no hay color por ende es transparente
            if (imagen.getPixel(x, y).a > 0)
            {
                if (x < izquierda)
                {
                    izquierda = x;
                }

                if (x > derecha)
                {
                    derecha = x;
                }

                if (y > abajo)
                {
                    abajo = y;
                }

                encontroPixelVisible = true;
            }
        }
    }

    //si el frame es completamente transparente devuelve un numero fijo asi no explota todo
    if (!encontroPixelVisible)
    {
        return {
            frameAncho / 2.f,
            static_cast<float>(frameAlto)
        };
    }

    return {
        (izquierda + derecha) / 2.f,
        static_cast<float>(abajo)
    };
}

Enemigo::Enemigo(const std::string& rutaTextura,
    const sf::Vector2f& posicion,
    int frameAncho,
    int frameAlto,
    const sf::Vector2f& escala)
    : _textura(cargarTextura(rutaTextura)),
      _sprite(_textura),
      _frameAncho(frameAncho),
      _frameAlto(frameAlto)
{
    _sprite.setTextureRect(sf::IntRect(0, 0, _frameAncho, _frameAlto));
    _sprite.setOrigin(obtenerOrigenVisible(_textura, _frameAncho, _frameAlto));
    _sprite.setPosition(posicion);
    _sprite.setScale(escala);

    if (!_bufferAlerta.loadFromFile("sound effects/enemigos/huu_duenio.wav"))
    {
        std::cout << "ERROR: NO SE PUDO CARGAR EL SONIDO DE ALERTA DEL ENEMIGO\n";
    }
    else
    {
        _sonidoAlerta.setBuffer(_bufferAlerta);
        _sonidoAlerta.setVolume(5.f);
    }

    cambiarEstado(EstadoEnemigo::DeEspalda);
}

void Enemigo::actualizar()
{
    const float tiempoTranscurrido =
        _relojEstado.getElapsedTime().asSeconds();
    if (_entraPorRuido)
    {
        actualizarEntrada();
        return;
    }

    if (_estado == EstadoEnemigo::DeEspalda &&
        tiempoTranscurrido >= _tiempoDeEspalda)
    {
        cambiarEstado(EstadoEnemigo::Alerta);
    }
    else if (_estado == EstadoEnemigo::Alerta &&
        tiempoTranscurrido >= TIEMPO_ENEMIGO_ALERTA)
    {
        cambiarEstado(EstadoEnemigo::DadoVuelta);
    }
    else if (_estado == EstadoEnemigo::DeEspaldaEnojado &&
        tiempoTranscurrido >= TIEMPO_ENEMIGO_REACCION_CAIDA)
    {
        cambiarEstado(EstadoEnemigo::DadoVueltaEnojado);
    }
    else if ((_estado == EstadoEnemigo::DadoVuelta ||
        _estado == EstadoEnemigo::DadoVueltaEnojado) &&
        tiempoTranscurrido >= TIEMPO_ENEMIGO_DADO_VUELTA)
    {
        cambiarEstado(EstadoEnemigo::DeEspalda);
    }
}

void Enemigo::reaccionarACaida()
{
    if (_entraPorRuido)
    {
        if (_estadoEntrada == EstadoEntrada::Fuera)
        {
            _estadoEntrada = EstadoEntrada::Esperando;
            _relojEstado.restart();
        }

        return;
    }
    // Otra caida no reinicia una reaccion que ya esta en curso.
    if (_estado == EstadoEnemigo::DeEspaldaEnojado ||
        _estado == EstadoEnemigo::DadoVueltaEnojado)
    {
        return;
    }

    if (_estado == EstadoEnemigo::DadoVuelta)
    {
        cambiarEstado(EstadoEnemigo::DadoVueltaEnojado);
    }
    else
    {
        cambiarEstado(EstadoEnemigo::DeEspaldaEnojado);
    }
}

void Enemigo::setPausado(bool pausado)
{
    _relojEstado.setPausado(pausado);

    if (pausado && _sonidoAlerta.getStatus() == sf::SoundSource::Playing)
    {
        _sonidoAlerta.pause();
    }
    else if (!pausado && _sonidoAlerta.getStatus() == sf::SoundSource::Paused)
    {
        _sonidoAlerta.play();
    }
}

void Enemigo::cambiarEstado(EstadoEnemigo nuevoEstado)
{
    _estado = nuevoEstado;

    if (_estado == EstadoEnemigo::DeEspalda)
    {
        const int cantidadDeTiempos =
            TIEMPO_ENEMIGO_DE_ESPALDA_MAX - TIEMPO_ENEMIGO_DE_ESPALDA_MIN + 1;

        _tiempoDeEspalda = static_cast<float>(
            TIEMPO_ENEMIGO_DE_ESPALDA_MIN + std::rand() % cantidadDeTiempos
        );
    }
    else if (_estado == EstadoEnemigo::Alerta)
    {
        _sonidoAlerta.play();
    }
    else if (_estado == EstadoEnemigo::DeEspaldaEnojado ||
        _estado == EstadoEnemigo::DadoVueltaEnojado)
    {
        _sonidoAlerta.stop();
    }

    _relojEstado.restart();
    actualizarSprite();
}

void Enemigo::actualizarSprite()
{
    int frame = 0;

    if (_estado == EstadoEnemigo::Alerta)
    {
        frame = 1;
    }
    else if (_estado == EstadoEnemigo::DadoVuelta)
    {
        frame = 2;
    }
    else if (_estado == EstadoEnemigo::DeEspaldaEnojado)
    {
        frame = 3;
    }
    else if (_estado == EstadoEnemigo::DadoVueltaEnojado)
    {
        frame = 4;
    }

    _sprite.setTextureRect(sf::IntRect(
        frame * _frameAncho,
        0,
        _frameAncho,
        _frameAlto
    ));
}

void Enemigo::dibujar(sf::RenderWindow& ventana) const
{
    if (_entraPorRuido &&
        (_estadoEntrada == EstadoEntrada::Fuera ||
            _estadoEntrada == EstadoEntrada::Esperando))
    {
        return;
    }

    ventana.draw(_sprite);
}

bool Enemigo::detectaAl(
    const Personaje& gato,
    const sf::FloatRect& areaVisible) const
{
    if (_entraPorRuido)
    {
        return _estadoEntrada == EstadoEntrada::Mirando &&
            !gato.estaEscondido();
    }
    // Si el sprite queda completamente fuera de pantalla,
    // este enemigo no puede descubrir al gato.
    if (!areaVisible.intersects(_sprite.getGlobalBounds()))
    {
        return false;
    }

    const bool estaMirando =
        _estado == EstadoEnemigo::DadoVuelta ||
        _estado == EstadoEnemigo::DadoVueltaEnojado;

    return estaMirando && !gato.estaEscondido();
}

void Enemigo::configurarEntrada(float recorrido)
{
    _entraPorRuido = true;
    _estadoEntrada = EstadoEntrada::Fuera;

    _posicionPuerta = _sprite.getPosition();
    _recorridoEntrada = recorrido;

    // Mismo origen para todos los cuadros.
    _sprite.setOrigin(
        _frameAncho / 2.f,
        static_cast<float>(_frameAlto)
    );

    _relojEstado.restart();
}

void Enemigo::actualizarEntrada()
{
    const float tiempo =
        _relojEstado.getElapsedTime().asSeconds();

    const float duracionCaminata = 1.f;

    switch (_estadoEntrada)
    {
    case EstadoEntrada::Fuera:
        break;

    case EstadoEntrada::Esperando:
        if (tiempo >= 2.f)
        {
            _sprite.setPosition(_posicionPuerta);
            _estadoEntrada = EstadoEntrada::Entrando;
            _relojEstado.restart();

            mostrarFrameEntrada(0);
        }
        break;

    case EstadoEntrada::Entrando:
    {
        float avance = tiempo / duracionCaminata;

        if (avance > 0.5f)
        {
            avance = 0.5;
        }

        _sprite.setPosition(
            _posicionPuerta.x + _recorridoEntrada * avance,
            _posicionPuerta.y
        );

        // Alterna los cuadros 0 y 1.
        const int frame =
            static_cast<int>(tiempo / 0.18f) % 2;
        _sonidoAlerta.play();

        mostrarFrameEntrada(frame);

        if (tiempo >= duracionCaminata)
        {
            _estadoEntrada = EstadoEntrada::Mirando;
            _relojEstado.restart();

            mostrarFrameEntrada(2);
        }
        break;
    }

    case EstadoEntrada::Mirando:
        if (tiempo >= 3.f)
        {
            _estadoEntrada = EstadoEntrada::Girando;
            _relojEstado.restart();

            mostrarFrameEntrada(3);
        }
        break;

    case EstadoEntrada::Girando:
        if (tiempo >= 0.3f)
        {
            _estadoEntrada = EstadoEntrada::Saliendo;
            _relojEstado.restart();

            mostrarFrameEntrada(4);
        }
        break;

    case EstadoEntrada::Saliendo:
    {
        float avance = tiempo / duracionCaminata;

        if (avance > 1.f)
        {
            avance = 1.f;
        }

        _sprite.setPosition(
            _posicionPuerta.x +
            _recorridoEntrada * (1.f - avance),
            _posicionPuerta.y
        );

        // Alterna los cuadros 4 y 5.
        const int frame =
            4 + static_cast<int>(tiempo / 0.18f) % 2;

        mostrarFrameEntrada(frame);

        if (tiempo >= duracionCaminata)
        {
            _sprite.setPosition(_posicionPuerta);
            _estadoEntrada = EstadoEntrada::Fuera;
            _relojEstado.restart();
        }
        break;
    }
    }
}

void Enemigo::mostrarFrameEntrada(int frame)
{
    const int columna = frame % 3;
    const int fila = frame / 3;

    _sprite.setTextureRect(sf::IntRect(
        columna * _frameAncho,
        fila * _frameAlto,
        _frameAncho,
        _frameAlto
    ));
}